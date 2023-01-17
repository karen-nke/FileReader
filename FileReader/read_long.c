#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

//Task 6 - Read long file directory

typedef struct {
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

typedef struct {
    unsigned char filename[8];
    unsigned char ext[3];
    unsigned char attributes;
    unsigned char reserved[10];
    unsigned short modify_time;
    unsigned short modify_date;
    unsigned short starting_cluster;
    unsigned long file_size;
} __attribute((packed)) Fat16Entry;

typedef struct {
    uint8_t LDIR_Ord; 
    uint8_t LDIR_Name1[ 10 ]; 
    uint8_t LDIR_Attr; 
    uint8_t LDIR_Type;
    uint8_t LDIR_Chksum;
    uint8_t LDIR_Name2[ 12 ]; 
    uint16_t LDIR_FstClusLO; 
    uint8_t LDIR_Name3[ 4 ]; 
} __attribute((packed)) LongContent;

