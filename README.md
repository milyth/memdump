# memdump
Dump memory of a process.

## Requirements
- A C compiler(e.g: GCC)
- Make
- A GNU Libc based system

## Usage
- Compile using `make memdump.so`
- Preload library using `LD_PRELOAD=<PATH TO memdump.so> <program>`
