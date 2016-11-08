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

@pytest.fixture
def sample_matrix():
	""" sample image to be processed """
	return [
		[3, 4],
		[1, 2, 3, 1],
		[3, 1, 1, 2],
		[2, 2, 1, 3]
	]	

@pytest.fixture
def stroke_stack():
	start = planner.Pixel(0,0)
	current = planner.Stroke(
			action=planner.INIT, # I think this is a garbage value that will be overwritten
			end=start, 
			oldcolor=0,
			newcolor=0	 
		)
	return planner.StrokeStack(current)

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

def test_stroke_move_output():
	end = planner.Pixel(0,1)
	oldcolor = 10
	newcolor = 20
	stroke = planner.Stroke(
		action=planner.MOVE,
		end=end,
		oldcolor=oldcolor,
		newcolor=newcolor
	)
	assert stroke.output() == "-1 0 1\n"

def test_stroke_switch_brush_output():
	end = planner.Pixel(0,1)
	oldcolor = 10
	newcolor = 20
	stroke = planner.Stroke(
		action=planner.SWITCH_BRUSH,
		end=end,
		oldcolor=oldcolor,
		newcolor=newcolor
	)
	assert stroke.output() == "-5 0 1 10 20\n"

def test_find_left_right_patch_single_pixel(sample_matrix):
	patch = []
	color = 1
	success =  planner.find_left_right_patch(
		image=sample_matrix,
		patch=patch,
		color=color,
		debug=False
		)
	assert success
	assert len(patch) == 1
	# this still seems like x should be 0 and y should be 1, but we are wrong and in reverse!
	assert patch[0] == planner.Pixel(1,0)

def test_find_left_right_patch_multiple_pixels(sample_matrix):
	patch = []
	color = 1
	planner.find_left_right_patch(
		image=sample_matrix[2:],
		patch=patch,
		color=color,
		debug=False
		)
	assert len(patch) == 2
	assert patch == [ planner.Pixel(0,1), planner.Pixel(0,2)]

def test_stroke_stack():
	start = planner.Pixel(0,0)
	current = planner.Stroke(
			action=planner.INIT, # I think this is a garbage value that will be overwritten
			end=start, 
			oldcolor=0,
			newcolor=0	 
		)
	strokes = planner.StrokeStack(current)
	top_before = strokes.peek()
	strokes.push_instruction(
		action=planner.LIFT
		)
	top_after = strokes.peek()
	assert top_before.action == planner.INIT
	assert top_after.action == planner.LIFT

def test_left_right_stroke_empty(stroke_stack):
	""" Should return false when the patch was empty. """
	patch = []
	tank = planner.MAX_TANK
	newpatch = False
	assert not planner.left_right_stroke(patch, stroke_stack, tank, newpatch)

def test_left_right_stroke(stroke_stack):
	""" Should create a stroke going across the patch. """
	init_stroke = stroke_stack.peek()
	tank = planner.MAX_TANK
	patch = [ planner.Pixel(0,0), planner.Pixel(0,1), planner.Pixel(0,2) ]
	planner.left_right_stroke(patch, stroke_stack, tank, newpatch=False)
	assert stroke_stack.strokes == [
		init_stroke,
		planner.Stroke(action=planner.MOVE,
			end=planner.Pixel(0,2),
			oldcolor=0,
			newcolor=0
		)
	]

def test_stroke_equality():
	stroke1 = planner.Stroke(
		action = planner.MOVE,
		end=planner.Pixel(0,0),
		oldcolor=0,
		newcolor=0
		)
	stroke2 = planner.Stroke(
		action=planner.MOVE,
		end=planner.Pixel(0,0),
		oldcolor=0,
		newcolor=0
	)
	assert stroke1 == stroke2

def test_stroke_inequality():
	stroke1 = planner.Stroke(
		action = planner.MOVE,
		end=planner.Pixel(0,0),
		oldcolor=0,
		newcolor=0
		)
	stroke2 = planner.Stroke(
		action=planner.MOVE,
		end=planner.Pixel(1,1),
		oldcolor=0,
		newcolor=0
	)
	assert stroke1 != stroke2












	

