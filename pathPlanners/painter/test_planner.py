import path_planner
import planner

import pytest

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


def test_sample_file_exists():
	""" this file needs to not move """
	open("../../ptg_pictures/lisa.ptg").close()

@pytest.fixture
def sample_input():
	""" sample contents of input file """
	file = open("../../ptg_pictures/lisa.ptg")
	yield file
	# teardown
	file.close()

@pytest.fixture
def bad_input():
	""" non-ptg format file """
	file = open("test_planner.py")
	yield file
	# teardown
	file.close()

def test_read_numbers(sample_input):
	matrix = path_planner.read_numbers(sample_input)
	assert matrix == [
		[3, 4],
		[1, 2, 3, 1],
		[3, 1, 1, 2],
		[2, 2, 1, 3]
	]	

def test_read_numbers(bad_input):
	""" should exit on invalid file name """
	try:
		matrix = path_planner.try_to_read_numbers(bad_input)
	except SystemExit:
		pass
	else:
		assert False

#### Pixel Tests ####

def test_pixel():
	pixel = planner.Pixel(3,4)
	assert pixel.x == 3
	assert pixel.y == 4







	

