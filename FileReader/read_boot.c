#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

// This is Task 2 - Reading boot information of disk image "fat16.img"

typedef struct {
   // uint8_t jump_boot[3];
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



int main() {
    FILE * fPointer; //File pointer
    int i;
    Fat16BootSector bs; 

    //Open disk image "fat16.img" and read binary 
    //If statement, when there is error opening the file, it will show Error!

     if ((fPointer = fopen("fat16.img","rb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

    //Setting Offset starting from Sector Size 0X0B
    fseek(fPointer, 0X0B, SEEK_SET); //Setting the starting file position 
    fread(&bs, sizeof(Fat16BootSector),1,fPointer); //return to bs(FAT16BootSector)

    //Print out the information
    
    printf("  Sector_size: %d\n", bs.sector_size);
    printf("  Sectors_per_cluster: %d\n", bs.sectors_per_cluster);
    printf("  Reserved_sectors: %d\n", bs.reserved_sectors);
    printf("  Number_of_fats: %d\n", bs.number_of_fats);
    printf("  Root_dir_entries: %d\n", bs.root_dir_entries);
    printf("  Total_sectors_short: %d\n", bs.total_sectors_16);
    printf("  Media_descriptor: 0x%02X\n", bs.media_descriptor);
    printf("  Fat_size_sectors: %d\n", bs.fat_size_sectors);
    printf("  Sectors_per_track: %d\n", bs.sectors_per_track);
    printf("  Number_of_heads: %d\n", bs.number_of_heads);
    printf("  Hidden_sectors: %d\n", bs.hidden_sectors);
    printf("  Total_sectors_long: %d\n", bs.total_sectors_32);
    printf("  Drive_number: 0x%02X\n", bs.drive_number);
    printf("  Current_head: 0x%02X\n", bs.current_head);
    printf("  Boot_signature: 0x%02X\n", bs.boot_signature);
    printf("  Volume_id: 0x%08X\n", bs.volume_id);
    printf("  Volume label: [%.11s]\n", bs.volume_label);
    printf("  Filesystem type: [%s]\n", bs.fs_type);
  
    fclose(fPointer); //Close the file
    return 0;
}


