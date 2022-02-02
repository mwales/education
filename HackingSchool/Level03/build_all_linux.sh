#!/bin/bash

# This will cause script to quit if any program returns an error
set -e

# Build the Hello World application
gcc helloworld.c -o helloworld

# Build the hello World application and keep intermediate files
gcc --save-temps helloworld.c -o helloworld

# Build int_sizes for 32-bit Linux (on a 64-bit host)
gcc -m32 int_sizes.c -o l32sizes

# Build int_sizes for 64-bit (on a 64-bit host)
gcc int_sizes.c -o l64sizes

# You get the idea, here is the rest
gcc repeat.c -o repeat
gcc tmnt_facts.c -o tmnt
gcc dowhile.c -o do_loop
gcc while.c -o while_loop
gcc factorial.c -o fact


