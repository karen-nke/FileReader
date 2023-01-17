#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

//Task 4 - Reading Root Directory

typedef struct {
    // uint8_t jump_boot[3];
    // uint8_t oem_name[8];
    uint16_t sector_size;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t number_of_fats;
    uint16_t root_dir_entries;
    uint16_t total_sectors_short; 
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

//Output of each file

void print_file_info(Fat16Entry *entry) {

    //Date and Time Variable

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    //Setting data

    year = (entry->modify_date >> 9 & 127) + 1980;
    month =  (entry->modify_date >> 5) & 15;
    day = entry->modify_date & 31;

    hour =  (entry ->modify_time >>11) &31;
    minute = (entry ->modify_time >>5)&63;
    second = (entry ->modify_time &31) *2;
   
    //Data Allocation
    printf("File: [%.8s.%.3s]\n", entry->filename, entry->ext);
    printf("Starting Cluster: %04X\n", entry->starting_cluster);
    printf("Modified Date: %04d-%02d-%02d\n" , year, month, day);
    printf("Modified Time: %02d:%02d.%02d\n\n" , hour, minute,second);
    
    
}

int main() {
    FILE * fPointer;
    int i;
    Fat16BootSector bs;
    Fat16Entry entry;

     if ((fPointer = fopen("fat16.img","rb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }
    
    fseek(fPointer, 0X0B, SEEK_SET);
    fread(&bs, sizeof(Fat16BootSector), 1, fPointer);
    
    printf("Now at 0x%X, sector size %d, FAT size %d sectors, %d FATs\n\n", 
           ftell(fPointer), bs.sector_size, bs.fat_size_sectors, bs.number_of_fats);
           
    fseek(fPointer, (bs.reserved_sectors-1 + bs.fat_size_sectors * bs.number_of_fats) *
          bs.sector_size, SEEK_CUR);

    //Print out the output of the file 
        
    for(i=0; i<bs.root_dir_entries; i++) {
        fread(&entry, sizeof(entry), 1, fPointer);
        print_file_info(&entry);
    }
    
    printf("\nRoot directory read, now at 0x%X\n", ftell(fPointer));
    fclose(fPointer);
    return 0;
}