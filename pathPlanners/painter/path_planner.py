"""Translate a file from ptg format to paint instruction format.

arguments:

"""

import sys

# default input/output files
iFileName = "../../ptg_pictures/lisa.ptg"
oFileName = "lisa.py.txt"


def USAGE_STATEMENT():
	print("Oops!")

def set_flags(args):
	changedOf = False
	for arg in args:
		if arg == "-h":
			USAGE_STATEMENT()
			return false
		elif arg[0:3] == "-ci":
			iFileName = arg[3:]
			if not changedOf:
				# make input file have same encoding as output file, but replace ptg with txt
				assert iFileName[:3] == "ptg"
				oFileName = iFileName[:3] + "txt"




def main():
	set_flags(sys.argv)


if __name__ == "__main__":
	main()