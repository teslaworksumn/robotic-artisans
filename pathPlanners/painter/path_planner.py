#! /usr/bin/env python3

"""Translate a file from ptg format to paint instruction format.

arguments:

"""

import sys

# default input/output files
iFileName = "../../ptg_pictures/lisa.ptg"
oFileName = "lisa.py.txt"
debug = False

def USAGE_STATEMENT(filename):
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
	global iFileName
	global oFileName
	global debug
	changeOFileName = False
	args = args[1:]
	for arg in args:
		if arg == "-h":
			USAGE_STATEMENT("foo")
			return False
		elif arg[0:3] == "-ci":
			iFileName = arg[3:]
			if not changeOFileName:
				# make input file have same encoding as output file, but replace ptg with txt
				assert iFileName[-4:] == ".ptg"
				oFileName = iFileName[-4:] + ".txt"
		elif arg[0:3] == "-co":
			changeOFileName = True
			oFileName = arg[2:]
		elif arg == "-d":
			debug = True
		else:
			print ("ERROR: UNKNOWN ARGUMENT")
			print (arg)
			USAGE_STATEMENT()
			return False
	return True


def main():
	set_flags(sys.argv)


if __name__ == "__main__":
	main()