# -*- coding: utf-8 -*-
import sys
from comparator import Ui_mainWindow
from PyQt4 import QtCore, QtGui, uic
from solution import Solution, Author

_numberOfBundles = 10
_listOfBundles = [1,2,3,4,5,6,7,8,9,10]
_separator = '\t'


class Principal(QtGui.QMainWindow, Ui_mainWindow):
    def __init__(self, parent=None):
        QtGui.QMainWindow.__init__(self, parent)
        self.setupUi(self)
        self.compareButton.clicked.connect(self.compareButton_clicked)
        self.searchFileButtonA.clicked.connect(self.openFile_clicked)
        self.searchFileButtonB.clicked.connect(self.openFile_clickedB)

    def compareButton_clicked(self):
        solution = Solution(self.fileNameA.text(), _separator, _numberOfBundles)
        solution2 = Solution(self.fileNameB.text(), _separator, _numberOfBundles)
        similarAuthors = calculateTotalSimilarElements(solution, solution2)
        result = 'Comparacion entre: ' + self.fileNameA.text() + ' - ' + self.fileNameB.text() + '\n'
        result = result + 'Cantidad de autores similares en total: ' + str(similarAuthors) + '\n'
        for bundle in _listOfBundles:
            similarAuthorsInBundle = calculateSimilarElementsInBundle(solution, solution2, bundle)
            result = result + 'Cantidad de autores en el bundle ' + str(bundle) + ': ' + str(similarAuthorsInBundle) + '\n'
        self.resultText.setPlainText(result)

    def openFile_clicked(self):
        fileName = QtGui.QFileDialog.getOpenFileName()
        self.fileNameA.setText(fileName)

    def openFile_clickedB(self):
        fileName = QtGui.QFileDialog.getOpenFileName()
        self.fileNameB.setText(fileName)


def calculateTotalSimilarElements(aSolution, anotherSolution):
    similarAuthors = 0
    for aBundle, aListOfAuthors in aSolution.bundles.iteritems():
        for anAuthor in aListOfAuthors:
            if anotherSolution.hasAuthor(anAuthor):
                similarAuthors = similarAuthors + 1
    return similarAuthors


def calculateSimilarElementsInBundle(aSolution, anotherSolution, bundle):
    similarAuthors = 0
    aListOfAuthors = aSolution.bundles[bundle]
    for anAuthor in aListOfAuthors:
        if anotherSolution.hasAuthorInBundle(anAuthor, bundle):
            similarAuthors = similarAuthors + 1
    return similarAuthors


app = QtGui.QApplication(sys.argv)
myWindow = Principal(None)
myWindow.show()
app.exec_()