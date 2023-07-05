#!/bin/bash

vasm.vasmm68k-mot Lesson1.asm -chklabels -nocase -Dvasm=1 -L Listing.txt -DBuildGEN=1 \
   -Fbin -o Cart.GEN


