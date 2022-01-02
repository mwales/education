#!/usr/bin/env python3

import sys
import os

def main(argv):
	if len(argv) < 2:
		print("Please provide flag to encode")
		return
	
	print("Flag = {}".format(argv[1]))
	
	f = open("flag.txt","w")
	f.write("{}".format(argv[1] + "\n"))
	f.close()
	
	print("Crafting gzip file flag1")
	os.system("tar -czvf flag1 flag.txt")
	
	print("Crafting bzip file flag2")
	os.system("tar -cjvf flag2 flag1")
	
	print("Crafting b64 file flag3")
	os.system("cat flag2 | base64 > flag3")
	
	f = open("flag3", "r")
	data = f.read()
	f.close()
	
	print("Writing a file with a bunch of garbage date flag4")
	
	f = open("flag4", "w")
	
	for i in range(13337):
		f.write("Blah blah blah, I am so important.  Please keep reading\n")
	f.write(data)
	for i in range(44420):
		f.write("Oh noessssss, did you miss the important message...  :sad trombone:\n")
	f.close()
	
	print("Writing zip file flag5")
	
	os.system("zip flag5 flag4")
	os.system("mv flag5.zip chal1")
	os.system("rm f*")
	
	print("Done")
	


if __name__ == "__main__":
	main(sys.argv)
