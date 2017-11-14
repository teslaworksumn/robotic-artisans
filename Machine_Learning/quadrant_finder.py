from PIL import Image
import numpy as np

# split an image up into x quadrants, then check for a shape in that quadrant
def blockshaped(imgPath, nrows, ncols):
    """
    Return an array of shape (n, nrows, ncols) where
    n * nrows * ncols = arr.size

    If arr is a 2D array, the returned array should look like n subblocks with
    each subblock preserving the "physical" layout of arr.
    """
    img = Image.open(imgPath)
    img = img.convert('L')
    imgArr = np.array(img)
    width, height = img.size
    imgArr.reshape((height, width))

    h, w = imgArr.shape
    return (imgArr.reshape(h//nrows, nrows, -1, ncols)
               .swapaxes(1,2)
               .reshape(-1, nrows, ncols))

if __name__ == '__main__':
    imgPath = 'pictures/quadrant_test.png'
    r = blockshaped(imgPath, int(height/2), int(width/2))
    for i in r:
        imgPart = Image.fromarray(i, 'L')
        imgPart.show()
