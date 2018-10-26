
curves = {}

class Curve:

    currentStrokeCount = 0

    def __init__(self, points=[], color="black", weight = 1):
        self.POINTS = points
        self.color = color
        self.weight = weight

        self.STROKEID = Curve.currentStrokeCount
        Curve.currentStrokeCount += 1
    
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