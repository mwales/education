#!/usr/bin/env python3

import sys
import os

def rot13(pt):
	ct = ""
	lowerCase = "abcdefghijklmnopqrstuvwxyz"
	upperCase = lowerCase.upper()
	
	for singleChar in pt:
		if singleChar in lowerCase:
			ct += lowerCase[ (lowerCase.index(singleChar) + 13) % len(lowerCase) ]
		elif singleChar in upperCase:
			ct += upperCase[ (upperCase.index(singleChar) + 13) % len(upperCase) ]
		else:
			ct += singleChar
		
	return ct
	
def stringPatch(binData, origString, newSubString):
	if not (origString in binData):
		print("Can't find source string for stringPatch")
		return false
		
	patchLen = len(newSubString) + 1
	patchData = bytes(newSubString + "\0", "utf-8") 
	
	patchLoc = binData.index(origString)
	
	retData = binData[:patchLoc] + patchData + binData[patchLoc + patchLen:]
	return retData
	
	
	
def main(argv):
	if len(argv) < 2:
		print("Please provide flag to encode")
		return
	
	print("Flag = {}".format(argv[1]))
	
	# Compile the binary application
	os.system("gcc challenge2_source.cpp -o chal2_flag")
	
	ct = rot13(argv[1])
	
	print("Rot13 = {}".format(ct))
	
	# open the binary
	f = open("chal2_flag", 'rb')
	binData = f.read()
	f.close()
	
	orig_flag = b"REPLACE_ME_WITH_FLAG_!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
	
	newBinData = stringPatch(binData, orig_flag, ct)
	
	f = open("chal2","wb")
	f.write(newBinData)
	f.close()
	
	os.system("chmod a+x chal2")
	os.system("rm chal2_flag")	
	
	print("Done")


if __name__ == "__main__":
	main(sys.argv)
