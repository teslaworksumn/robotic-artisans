"""Translate a file from ptg format to paint instruction format.

arguments:

"""

import sys

# default input/output files
iFileName = "../../ptg_pictures/lisa.ptg"
oFileName = "lisa.py.txt"
debug = False

def USAGE_STATEMENT():
	print("Oops!")

def set_flags(args):
	global iFileName
	global oFileName
	global debug
	print args
	changedOf = False
	args = args[1:]
	for arg in args:
		if arg == "-h":
			USAGE_STATEMENT()
			return False
		elif arg[0:3] == "-ci":
			iFileName = arg[3:]
			if not changedOf:
				# make input file have same encoding as output file, but replace ptg with txt
				assert iFileName[-4:] == ".ptg"
				oFileName = iFileName[-4:] + ".txt"
		elif arg[0:3] == "-co":
			changedOf = True
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