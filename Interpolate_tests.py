import unittest
import Interpolate
import os


class Interpolate_test(unittest.TestCase):

    def test_abs(self):
        self.assertEqual(Interpolate.abs(-3), 3)
        self.assertEqual(abs(0), 0)
        self.assertEqual(abs(10), 10)

    def test_make_gcode(self):
        self.assertEqual(Interpolate.make_gcode((1, 2, 3)), "G1 X 1 Y 2 Z 3")

    def test_generate_points_number_of_points(self):
        number_of_new_points = len(Interpolate.generate_points((0, 0, 0),
                                                               (10, 0, 0)))
        self.assertEqual(number_of_new_points, 1999)

    def test_generate_points_correctness(self):
        self.assertEqual(Interpolate.generate_points((0, 0, 0),
                                                     (0.01, 0, 0))[0],
                         (0.005, 0, 0))

    def test_interpolate(self):
        file_in = open("test_in.txt", 'w+')
        file_in.write("G1 X 0 Y 0 Z 0\n")
        file_in.write("G1 X 1 Y 0 Z 0\n")
        file_in.close()
        Interpolate.read_file("test_in.txt", "test_out.txt")
        file_out = open("test_out.txt", 'r')
        lines = 0
        for line in file_out:
            lines = lines + 1
        self.assertEqual(lines, 201)
        file_out.close()
        os.remove("test_in.txt")
        os.remove("test_out.txt")


if __name__ == '__main__':
    unittest.main()
