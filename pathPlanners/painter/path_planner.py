#! /usr/bin/env python3

"""Translate a file from ptg format to paint instruction format.

arguments:

"""

import sys

DefaultInputFileName = "../../ptg_pictures/lisa.ptg"
DefaultOutputFileName = "lisa.txt"
debug = False

def USAGE_STATEMENT():
	""" Print a usage statement. """
	message = """
	Usage:\t\tpython path_planner.py [options]
	Options:
	-h \t\tPrint this message and exit
	-ci\t\tWill ask for input file other than default
	-co\t\tWill ask for output file other than default
	-d \t\tWill turn on debug mode
	"""
	print (message)

	
def set_flags(args):
	""" Parse command line arguments. """
	changeOFileName = False
	debug = False
	iFileName = DefaultInputFileName
	oFileName = DefaultOutputFileName
	# drop script name from arguments
	args = args[1:]
	for arg in args:
		if arg == "-h":
			USAGE_STATEMENT()
			exit()
		elif arg[0:3] == "-ci":
			iFileName = arg[4:]
			if not changeOFileName:
				# make input file have same encoding as output file, but replace ptg with txt
				# assert iFileName[-4:] == ".ptg"
				oFileName = iFileName[:-4] + ".txt"
		elif arg[0:3] == "-co":
			changeOFileName = True
			oFileName = arg[4:]
		elif arg == "-d":
			debug = True
		else:
			print ("ERROR: UNKNOWN ARGUMENT: %s" % arg)
			USAGE_STATEMENT()
			exit(10)
	return (iFileName, oFileName, debug)


def try_to_open(filename, mode):
	""" Open a file with filename and mode, or, if opening fails, exit and print an error message. """
	try:
		result = open(filename, mode)
	except IOError:
		print ("%s: could not open file" % filename)
		exit(10)
	return result

def read_numbers(file):
	""" Take an open ptg file and transform it into a 2D integer array. """
	return [ map(int, line.split()) for line in file ]

def try_to_read_numbers(file):
	try:
		read_numbers(file)
	except ValueError as e:
		print("invalid ptg file:")
		print(e)
		exit(10)
		
def main():
	iFileName, oFileName, debug	= set_flags(sys.argv)
	oFile = try_to_open(oFileName, 'w')
	iFile = try_to_open(iFileName, 'r')
	matrix = try_to_read_numbers(iFile)
	
	oFile.close()
	iFile.close()
		
if __name__ == "__main__":
	main()