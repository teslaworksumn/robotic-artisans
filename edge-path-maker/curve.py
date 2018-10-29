
import matplotlib.pyplot as plt

curves = {}

class Curve:

    currentStrokeCount = 0

    def __init__(self, points=[], color="black", weight = 1):
        self.POINTS = points
        self.color = color
        self.weight = weight

        self.STROKEID = Curve.currentStrokeCount
        Curve.currentStrokeCount += 1

    # add a curve to the global collection of curves
    @staticmethod
    def addCurve(curve):
        curves.append(curve)
    @staticmethod
    def addCurves(curves):
        curves.extend(curves)
    @staticmethod
    def removeCurve(curve):
        curves.remove(curve)
    
    # provide only get accessor method. points should not be modified
    def getPoints(self):
        return self.POINTS

    def getColor(self):
        return self.color
    def setColor(self, newColor):
        self.color = newColor

    def getWeight(self):
        return self.weight
    def setWeight(self, newWeight):
        self.weight = newWeight
    
    # Convert a list of control points into a list of points along the curve
    def stroke2Coordinates(self, stepSize):
        pointsOnCurve = []
        for i in range(0, 100 + stepSize, stepSize):
            coord = self.bezierCurveRecurse(self.POINTS, i/100)
            pointsOnCurve.append(coord)
        return pointsOnCurve

    # Helper function for stroke2Coordinates.
    # Define a Bezier Curve as a Bernstein Polynomial recursively
    def bezierCurveRecurse(self, stroke, pos):
        if (len(stroke) > 2):
            funx1, funy1 = self.bezierCurveRecurse(stroke[:-1], pos)
            funx2, funy2 = self.bezierCurveRecurse(stroke[1:], pos)
            Bx = (1 - pos)*(funx1) + (pos)*(funx2)
            By = (1 - pos)*(funy1) + (pos)*(funy2)
            return (Bx, By)
        else:
            return ((1 - pos)*stroke[0][0] + (pos)*stroke[1][0], (1 - pos)*stroke[0][1] + (pos)*stroke[1][1])

    def visualizeCurve(self, stepSize=10):
        pointsOnCurve = self.stroke2Coordinates(stepSize)
        arr = list(map(list, zip(*pointsOnCurve)))
        plt.plot(arr[0], arr[1])
        plt.show()