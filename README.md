
# StorageSpace

Native GUI for finding large files and cleaning up storage space. Allows for recursively searching directories for files that match the specified search criteria, opening up results in folder and deleting from disk.

## File Search Parameters

| Parameter   s| Description                                              |
|------------:| ----------------------------------------------------------|
| **Search text** | Contains search on relative file names                |
| **Search regular expression** | Regular expression search on file names |
| **Min** | Min file size in bytes                                        |
| **Max** | Max file size in bytes                                        |
| **Recursive** | Recursive search on nested folders                      |
| **Search directory** | Search directory to start from                   |

## Build

Tested on Qt >= 5.15.2 and compiled with MSVC 2019 64 bit