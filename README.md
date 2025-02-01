# LF (List Files) - A Linux-Style File Explorer

LF (List Files) is a simple Linux-style file explorer written in C. This project aims to recreate the functionality of the `ls` command. Currently, it supports:

- **Basic file listing**: When run without arguments, it prints file names.
- **Long format listing (-l)**: When using the `-l` flag, it prints a detailed file listing similar to `ls -l`.

This is a work in progress, and more features will be added in the future.

## Features

- Lists files in a directory.
- Supports `-l` flag for detailed file information.
- Uses system calls to retrieve file details such as permissions, owner, group, size, and last modification time.

## Installation

To compile the project, use `gcc`:

```bash
gcc main.c -o lf
```

## Usage

Run the program without arguments to list file names:

```bash
./lf
```

Use the `-l` flag to print the long-formatted version:

```bash
./lf -l
```



## Additional Resources

For more details on how this works, check out this article:
[Building a Linux-Style File Explorer: Recreating the 'ls' Command in C](https://islamukheef.medium.com/building-a-linux-style-file-explorer-recreating-the-ls-command-in-c-71ecce6d79ad) 



