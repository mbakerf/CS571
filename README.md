# os161
cs 571 - os161 

OS161 is a minimal operating system for educational purposes. It runs on a machine simulator called sys161.

## Build

`cd os161-1.11/kern/conf`
`./config ASSTx # where x is the assignment number`

## Compile

`cd os161-1.11/kern/compile/ASSTx # where x is the assignment number`
`make depend`
`make`
`make install`


## Adding a File to the Kernel

When adding a source file, update the `os161-1.11/kern/conf/conf.kern` with the file.

## Changelog per Assignment

ASST1: Update `root/sys161.conf` with `31 busctl ramsize=2097152`
