#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdbool.h>

//Task 3 - Printing out cluster of the disk image 

typedef struct{ 
    uint8_t jump_boot[3];
    uint8_t oem_name[8];
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

int reader(char* file, void* bs, int offset, int readingByte){
    int fpointer = open(file, O_RDONLY);

    lseek(fpointer, offset, SEEK_SET);
    read(fpointer, bs, readingByte);
    close(fpointer);
    return fpointer;
}

int main(){
    Fat16BootSector bs;
    
    int fpointer = reader("fat16.img",&bs, 0, sizeof(Fat16BootSector));

    int reserved_sectors =bs.reserved_sectors;
    int sector_size = bs.sector_size;
    int sizesector = reserved_sectors * sector_size;
    int fat_size = bs.fat_size_sectors;

    uint16_t cache[fat_size]; 
    reader("fat16.img",cache, sizesector, sizeof(uint16_t)*fat_size);
    
    for (int i=2; i<fat_size; i++)
    { 
        printf("%d: %d\n", i, cache[i]);
    } 

    return 0;
}