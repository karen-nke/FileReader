# FAT16.img Filesystem Reader

## Overview
This project is a simple FAT16 filesystem reader implemented in C. It provides functions to open a file, read the boot sector, read clusters, read files, read long file directories, and read the root directory of the FAT16.img filesystem.

## Project Structure
- **read_boot.c**: Source code for reading the boot sector.
- **read_cluster.c**: Source code for reading clusters.
- **read_file.c**: Source code for reading files.
- **read_long_file_directory.c**: Source code for reading long file directories.
- **read_root.c**: Source code for reading the root directory.

Each C file has a corresponding executable (.exe) file for execution.

## Functions
1. **Open File**: Open a file in the FAT16.img filesystem.
2. **Read Boot**: Read the boot sector of the filesystem.
3. **Read Cluster**: Read clusters from the filesystem.
4. **Read File**: Read a specific file from the filesystem.
5. **Read Long File Directory**: Read long file directories.
6. **Read Root**: Read the root directory of the filesystem.

## Usage
1. **Compile**: Compile the C files using a C compiler (e.g., GCC).
    ```bash
    gcc read_boot.c -o read_boot.exe
    ```

2. **Execute**: Execute the compiled executable for the desired functionality.
    ```bash
    ./read_boot.exe
    ```

## License
This project is licensed under the [MIT License](LICENSE).

