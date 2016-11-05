import path_planner

def test_open_file_test():
	"""test how python works"""
	try:
		with open("__non_existent_file__") as foo:
			assert False
	except IOError:
		assert True

def test_debug():
	options = "_ -d".split()
	_, _, debug = path_planner.set_flags(options)
	assert debug
	options = "_"
	_, _, debug = path_planner.set_flags(options)
	assert not debug

def test_input_file():
	options = "_ -ci=EXAMPLE".split()
	input_file, _, _ = path_planner.set_flags(options)
	assert input_file == "EXAMPLE"

def test_output_file():
	options = "_ -co=EXAMPLE".split()
	_, output_file, _ = path_planner.set_flags(options)
	assert output_file == "EXAMPLE"





	

