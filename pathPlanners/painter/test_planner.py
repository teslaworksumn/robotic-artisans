import path_planner

def test_open_file():
	"check how python throws exceptiosn when opening files"
	try:
		with open("non_existant_file") as foo:
			assert False
	except:
		assert True

