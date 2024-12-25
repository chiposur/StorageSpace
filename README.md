
# StorageSpace

Native GUI for finding large files and cleaning up storage space. Allows for recursively searching directories for files that match the specified search criteria, opening up results in folder and deleting from disk.

This program can also be run as a CLI, providing the file search parameters as command line arguments and outputing a list of formatted file results.

Launch as GUI by double clicking or running on the command line without arguments:

`StorageSpace`

Run as CLI by specifying one or more arguments:

`StorageSpace --dir /path/to/dir --sort-by size --desc`

## File Search Parameters

| Parameters  | Description                                               |
|------------:| ----------------------------------------------------------|
| **Search text** | Contains search on file names                         |
| **Search regular expression** | Regular expression search on file names |
| **Min** | Min file size in bytes                                        |
| **Max** | Max file size in bytes                                        |
| **Depth** | Folder depth to recursively search into                     |
| **Recursive** | Recursive search on nested folders                      |
| **Search directory** | Search directory to start from                   |

## Command Line Arguments

| Arguments   | Description                                               |
|------------:| ----------------------------------------------------------|
| **-d, --dir** | Search directory to start from                          |
| **--search-text** | Contains search on file names                       |
| **--search-regex** | Regular expression search on file names            |
| **-r** | Recursive search on nested folders                             |
| **--min** | Min file size in bytes                                      |
| **--max** | Max file size in bytes                                      |
| **--depth** | Folder depth to recursively search into                   |
| **--sort-by** | Sort by [path, size]                                    |
| **--asc** | If sort-by is specified, sort ascending (default)           |
| **--desc** | If sort-by is specified, sort descending                   |

## Build

Tested on Qt >= 5.15.2 and compiled with MSVC 2019 64 bit (Windows) and Clang (Mac)

Distribution can be handled with the [windeployqt tool](https://doc.qt.io/qt-6/windows-deployment.html#the-windows-deployment-tool) on Windows, [macdeployqt](https://doc.qt.io/qt-6/macos-deployment.html) on Mac, or [manually](https://doc.qt.io/qt-6/linux-deployment.html) on Linux/X11.
