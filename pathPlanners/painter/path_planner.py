#! /usr/bin/env python3

"""Translate a file from ptg format to paint instruction format.

arguments:

"""

import sys

# default input/output files
iFileName = "../../ptg_pictures/lisa.ptg"
oFileName = "lisa.py.txt"
debug = False

def USAGE_STATEMENT():
	"""print a usage statement"""
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
	"""parse command line arguments"""
	global iFileName
	global oFileName
	global debug
	changeOFileName = False
	args = args[1:]
	for arg in args:
		if arg == "-h":
			USAGE_STATEMENT()
			return False
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
			print ("ERROR: UNKNOWN ARGUMENT")
			print (arg)
			USAGE_STATEMENT()
			return False
	return True


def try_to_open(filename, mode):
	"""open a file with filename and mode, or, if opening fails, exit and print an error message"""
	try:
		result = open(filename, mode)
	except IOError:
		print ("%s: No such file or directory" % filename)
		exit(10)
	return result


def main():
	if set_flags(sys.argv):
		oFile = try_to_open(oFileName, 'w')
		iFile = try_to_open(iFileName, 'r')
		oFile.close()
		iFile.close()
		
if __name__ == "__main__":
	main()