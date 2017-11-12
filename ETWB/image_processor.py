"""
From a jpg or png file, generate the ptg file that will be passed
to pathPlanner. A PTG file compresses the png file to using only 8 colors.
"""

import math
from PIL import Image

COLORS = [(255, 255, 255), (255, 255, 0), (255, 20, 147), (50, 60, 150),
          (0, 255, 0), (0, 0, 255), (0, 128, 0), (0, 0, 0)]
# WHITE, BLACK, skyblue, RED, GREEN, BLUE, YELLOW, DARK_GREEN
# 1      8       3     4     5       6       2          7


def get_pixel_array(image):
    """
    Return list of rgb values for each pixel in the image
    """
    pixels = []
    img = image.load()
    for i in range(image.size[1]):
        for j in range(image.size[0]):
            pixels.append(img[j, i])
    return pixels


def write_to_file(digits, file_path, rows, cols):
    """
    Writes a list of single digits to a txt file in .ptg format
    """
    output = open(file_path, 'a')
    output.write(str(rows)+" "+str(cols)+"\n")
    index = 0
    for _ in range(rows):
        for _ in range(cols):
            output.write(str(digits[index]) + " ")
            index += 1
        output.write("\n")
    output.close()


# from https://stackoverflow.com/
# questions/13405956/convert-an-image-rgb-lab-with-python
def rgb2lab(inputColor):
    # pylint: disable=C0103,C0111
    # Only use first three attributes of the color.

    # This makes the function compatible with png files,
    # which apparently have a 4th opacity attribute.
    inputColor  # = inputColor[:3]

    num = 0
    RGB = [0, 0, 0]

    for value in inputColor:
        value = float(value) / 255

        if value > 0.04045:
            value = ((value + 0.055) / 1.055) ** 2.4
        else:
            value = value / 12.92

        RGB[num] = value * 100
        num = num + 1

    XYZ = [0, 0, 0, ]

    X = RGB[0] * 0.4124 + RGB[1] * 0.3576 + RGB[2] * 0.1805
    Y = RGB[0] * 0.2126 + RGB[1] * 0.7152 + RGB[2] * 0.0722
    Z = RGB[0] * 0.0193 + RGB[1] * 0.1192 + RGB[2] * 0.9505
    XYZ[0] = round(X, 4)
    XYZ[1] = round(Y, 4)
    XYZ[2] = round(Z, 4)
    # ref_X =  95.047 Observer= 2 deg, Illuminant= D65
    XYZ[0] = float(XYZ[0]) / 95.047
    XYZ[1] = float(XYZ[1]) / 100.0          # ref_Y = 100.000
    XYZ[2] = float(XYZ[2]) / 108.883        # ref_Z = 108.883

    num = 0
    for value in XYZ:

        if value > 0.008856:
            value = value ** (0.3333333333333333)
        else:
            value = (7.787 * value) + (16 / 116)

        XYZ[num] = value
        num = num + 1

    Lab = [0, 0, 0]

    L = (116 * XYZ[1]) - 16
    a = 500 * (XYZ[0] - XYZ[1])
    b = 200 * (XYZ[1] - XYZ[2])

    Lab[0] = round(L, 4)
    Lab[1] = round(a, 4)
    Lab[2] = round(b, 4)

    return Lab


COLORS_LAB = [rgb2lab(color) for color in COLORS]


def distance(lab1, lab2):
    """
    return distance between 2 lab colors
    """
    # pylint: disable=C0103
    l1, a1, b1 = lab1
    l2, a2, b2 = lab2
    dl = l1 - l2
    da = a1-a2
    db = b1-b2
    return math.sqrt(da**2+db**2+dl**2)


def match_color(lab):
    """
    matches color to one of 8 paint colors
    """
    distances = [distance(lab, color_lab) for color_lab in COLORS_LAB]
    minimum = distances[0]
    pos = 0  # the color number is its position in the list COLORS
    count = 1
    for dist in distances:
        if dist <= minimum:
            minimum = dist
            pos = count
        count += 1
    return pos


def make_ptg(image_path, num_rows, num_cols):
    """
    Create a ptg file from the given path with ptg extension
    """
    image = Image.open(image_path).resize((num_cols, num_rows))
    pixels = get_pixel_array(image)
    output_path = image_path[:-4] + ".ptg"
    paints = [match_color(rgb2lab(px)) for px in pixels]
    write_to_file(paints, output_path, num_rows, num_cols)
    print('created ' + output_path)
    return output_path


def write_ratio(cols):
    """
    Write ratio to a file.
    """
    ratio_file = open("Ratio.txt", 'a')
    ratio_file.write(str(10.0 / cols))
    ratio_file.close()


if __name__ == "__main__":
    # pylint: disable=C0103
    # pylint: disable=C0330
    import argparse
    parser = argparse.ArgumentParser(
        description='Convert an image file to 8-color ptg')
    parser.add_argument('filename', help='input png/jpg file')
    parser.add_argument('rows', type=int,
                        help='number of rows in the output image')
    parser.add_argument('cols', type=int,
                        help='number of columns in the output image')
    args = parser.parse_args()
    write_ratio(args.cols)
    make_ptg(args.filename, args.rows, args.cols)
