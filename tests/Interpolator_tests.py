import unittest
import Interpolator


class Interpolator_test(unittest.TestCase):

    def test_abs(self):
        self.assertEqual(abs(-3), 3)
        self.assertEqual(abs(0), 0)
        self.assertEqual(abs(10), 10)

    def test_make_gcode(self):
        self.assertEquals(make_gcode(1, 2, 3), "G1 X 1 Y 2 Z 3")

    def test_generate_points_10in(self):
        number_of_new_points = len(generate_points((0, 0, 0), (10, 0, 0)))
        self.assertEquals(number_of_new_points, 1999)


if __name__ == '__main__':
    unittest.main()
