
# StorageSpace

Native GUI for finding large files and cleaning up storage space. Allows for recursively searching directories for files that match the specified search criteria, opening up results in folder and deleting from disk.

This program can also be run as a CLI, providing the file search parameters as command line arguments and outputing a list of formatted file results.

## File Search Parameters

| Parameters  | Description                                               |
|------------:| ----------------------------------------------------------|
| **Search text** | Contains search on relative file names                |
| **Search regular expression** | Regular expression search on file names |
| **Min** | Min file size in bytes                                        |
| **Max** | Max file size in bytes                                        |
| **Recursive** | Recursive search on nested folders                      |
| **Search directory** | Search directory to start from                   |

## Command Line Arguments

| Arguments   | Description                                               |
|------------:| ----------------------------------------------------------|
| **-d, --dir** | Search directory to start from                          |
| **--search-text** | Contains search on relative file names              |
| **--search-regex** | Regular expression search on file names            |
| **-r** | Recursive search on nested folders                             |
| **--min** | Min file size in bytes                                      |
| **--max** | Max file size in bytes                                      |
| **--sort-by** | Sort by [path, size]                                    |
| **--asc** | If sort-by is specified, sort ascending (default).          |
| **--desc** | If sort-by is specified, sort descending.                  |

## Build

Tested on Qt >= 5.15.2 and compiled with MSVC 2019 64 bit