#!/usr/bin/python3

import sys

def process_data(p_data, p_file):
	
	p_file.write("R\"(" + p_data + ")\"\n")
	return


def main(t_fileName):

	t_chunkSize = 2000
	
	t_fileOut = open(t_fileName + "out", "wt")

	t_fileIn = open(t_fileName, 'r')
	while True:
		t_data = t_fileIn.read(t_chunkSize)  
		if not t_data:
			print("BREAK..")
			break
		process_data(t_data, t_fileOut)
	
	t_fileIn.close()
	t_fileOut.close()
	
	
	
if __name__ == "__main__":
	main(sys.argv[1])
