"""
Some rather incomplete unit tests for planner.py
Execute with py.test <filename>
"""
import pytest

import main
import planner


### Test Main ###

PTG_FILE = "lisa.ptg"

def test_debug():
    options = "_ -d".split()
    _, _, debug = main.set_flags(options)
    assert debug
    options = "_"
    _, _, debug = main.set_flags(options)
    assert not debug

def test_input_file():
    options = "_ -ci=EXAMPLE".split()
    input_file, _, _ = main.set_flags(options)
    assert input_file == "EXAMPLE"

def test_output_file():
    options = "_ -co=EXAMPLE".split()
    _, output_file, _ = main.set_flags(options)
    assert output_file == "EXAMPLE"


def test_sample_file_exists():
    """ This file needs to not move. """
    # This test may also fail if pytest is exected from the wrong directory.
    open(PTG_FILE).close()


## Test Planner ###

@pytest.fixture
def sample_input():
    """ Return contents of sample input file. """
    ptg_file = open(PTG_FILE)
    yield ptg_file
    # teardown
    ptg_file.close()

@pytest.fixture
def bad_input():
    """ Non-ptg format file. """
    random_file = open("test_planner.py")
    yield random_file
    # teardown
    random_file.close()

@pytest.fixture
def sample_matrix():
    """ Sample image to be processed. """
    return [
        [3, 4],
        [1, 2, 3, 1],
        [3, 1, 1, 2],
        [2, 2, 1, 3]
    ]

@pytest.fixture()
def all_ones():
    """ Simple, easy-to-understand matrix """
    return [
    [1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1]
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
    matrix = main.read_numbers(sample_input)
    assert matrix == [
        [3, 4],
        [1, 2, 3, 1],
        [3, 1, 1, 2],
        [2, 2, 1, 3]
    ]

def test_read_numbers(bad_input):
    """ should exit on invalid file name """
    try:
        matrix = main.try_to_read_numbers(bad_input)
    except SystemExit:
        pass
    else:
        assert False


def test_pixel():
    pixel = planner.Pixel(3,4)
    assert pixel.y == 3
    assert pixel.x == 4

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
    assert stroke.output() == "-1 1 0\n"

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
    assert stroke.output() == "-5 1 0 10 20\n"


def test_find_left_right_patch_single_pixel(sample_matrix):
    patch = []
    color = 1
    success =  planner.find_left_right_patch(
        image=sample_matrix,
        patch=patch,
        color=color,
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

def test_stroke_stack_color():
    start = planner.Pixel(0,0)
    current = planner.Stroke(
            action=planner.INIT, # I think this is a garbage value that will be overwritten
            end=start,
            oldcolor=0,
            newcolor=0
        )
    strokes = planner.StrokeStack(current)
    strokes.push_instruction(
        action=planner.SWITCH_BRUSH, newcolor=1
        )
    strokes.push_instruction(action=planner.MOVE)
    assert strokes.peek().oldcolor == 1

def test_left_right_stroke_empty(stroke_stack):
    """ Should return false when the patch was empty. """
    patch = []
    tank = planner.Tank()
    newpatch = False
    assert not planner.left_right_stroke(patch, stroke_stack, tank, newpatch)

def test_left_right_stroke(stroke_stack):
    """ Should create a stroke going across the patch. """
    init_stroke = stroke_stack.peek()
    tank = planner.Tank()
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
    assert tank.amount == planner.MAX_TANK - 3

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


def test_stroke_string(all_ones):
    strokes = planner.left_right(all_ones)
    print strokes
    assert str(strokes).index(
    "-5 -1 -1 0 1\n"
    "-1 0 0\n"
    "-3\n"
    "-1 4 0\n"
    "-2\n"
    "-1 0 1\n"
    "-4 0 1 1\n"
    ) == 0


def test_tank():
    tank = planner.Tank()
    assert tank.amount == planner.MAX_TANK

def test_tank_decrement():
    tank = planner.Tank()
    tank.decrement()
    assert tank.amount == planner.MAX_TANK - 1

def test_tank_empty():
    tank = planner.Tank()
    assert not tank.empty()
    tank.amount = 0
    assert tank.empty()
    tank.refill()
    assert not tank.empty()
