import sys

iFileName = "../../ptg_pictures/lisa.ptg"
oFileName = "lisa.py.txt"


def arg_parse(args):
	set_flags(args)

def main():
	set_flags(sys.argv)


if __name__ == "__main__":
	main()