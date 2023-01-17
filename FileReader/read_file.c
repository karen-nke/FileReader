#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

//Task 5 - Open file in disk image 

typedef struct {
    //uint8_t jump_boot[3];
   // uint8_t oem_name[8];
    uint16_t sector_size;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t number_of_fats;
    uint16_t root_dir_entries;
    uint16_t total_sectors_16; 
    uint8_t media_descriptor;
    uint16_t fat_size_sectors;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_32;
    uint8_t drive_number;
    uint8_t current_head;
    uint8_t boot_signature;
    uint32_t volume_id;
    uint8_t volume_label[11];
    uint8_t fs_type[8];
} __attribute((packed)) Fat16BootSector;

typedef struct {
    unsigned char filename[8];
    unsigned char ext[3];
    uint8_t attributes;
    unsigned char reserved[10];
    uint16_t modify_time;
    uint16_t modify_date;
    uint16_t starting_cluster;
    uint32_t file_size;
} __attribute((packed)) Fat16Entry;

void fat_read_file(FILE * in, FILE * out,
                   unsigned long fat_start, 
                   unsigned long data_start, 
                   unsigned long cluster_size, 
                   unsigned short cluster, 
                   unsigned long file_size) {
    unsigned char buffer[4096];
    size_t bytes_read, bytes_to_read,
           file_left = file_size, cluster_left = cluster_size;

    // Go to first data cluster
    fseek(in, data_start + cluster_size * (cluster-2), SEEK_SET);
    
    // Read until we run out of file or clusters
    while(file_left > 0 && cluster != 0xFFFF) {
        bytes_to_read = sizeof(buffer);
        
        // don't read past the file or cluster end
        if(bytes_to_read > file_left)
            bytes_to_read = file_left;
        if(bytes_to_read > cluster_left)
            bytes_to_read = cluster_left;
        
        // read data from cluster, write to file
        bytes_read = fread(buffer, 1, bytes_to_read, in);
        fwrite(buffer, 1, bytes_read, out);
        printf("Copied %d bytes\n", bytes_read);
        
        // decrease byte counters for current cluster and whole file
        cluster_left -= bytes_read;
        file_left -= bytes_read;
        
        // if we have read the whole cluster, read next cluster # from FAT
        if(cluster_left == 0) {
            fseek(in, fat_start + cluster*2, SEEK_SET);
            fread(&cluster, 2, 1, in);
            
            printf("End of cluster reached, next cluster %d\n", cluster);
            
            fseek(in, data_start + cluster_size * (cluster-2), SEEK_SET);
            cluster_left = cluster_size; // reset cluster byte counter
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *in ;
    int i, j;
    unsigned long fat_start, root_start, data_start;
    Fat16BootSector bs;
    Fat16Entry entry;
	char filename[9] = "        ", file_ext[4] = "   "; // initially pad with spaces
    
	if(argc < 3) {
		printf("Usage: read_file <fs_image> <FILE.EXT>\n");
		return 0;
	}
	
	if((in = fopen(argv[1], "rb")) == NULL) {
		printf("Filesystem image file %s not found!\n", argv[1]);
		return -1;
	}
	
    // Copy filename and extension to space-padded search strings
	for(i=0; i<8 && argv[2][i] != '.' && argv[2][i] != 0; i++)
		filename[i] = argv[2][i];
	for(j=1; j<=3 && argv[2][i+j] != 0; j++)
		file_ext[j-1] = argv[2][i+j];
		
	printf("Opened %s, looking for [%s.%s]\n", argv[1], filename, file_ext);
	
    fseek(in, 0X0B, SEEK_SET);
    fread(&bs, sizeof(Fat16BootSector), 1, in);
    
    // Calculate start offsets of FAT, root directory and data
    fat_start = ftell(in) + (bs.reserved_sectors-1) * bs.sector_size;
    root_start = fat_start + bs.fat_size_sectors * bs.number_of_fats *
        bs.sector_size;
    data_start = root_start + bs.root_dir_entries * sizeof(Fat16Entry);
    
    printf("FAT start at %08X, root dir at %08X, data at %08X\n", 
           fat_start, root_start, data_start);
           
    fseek(in, root_start, SEEK_SET);
		  
    for(i=0; i<bs.root_dir_entries; i++) {
        fread(&entry, sizeof(entry), 1, in);
		
		if(memcmp(entry.filename, filename, 8) == 0 && 
		   memcmp(entry.ext, file_ext, 3) == 0) {
            printf("File found!\n");
            break;
        }
    }
    
    if(i == bs.root_dir_entries) {
        printf("File not found!");
        return -1;
    }
    

    fclose(in);
    
    return 0;
}
