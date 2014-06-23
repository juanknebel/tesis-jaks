__author__ = 'zero'

import sys
from resultController import ResultController
from PyQt4 import QtGui

app = QtGui.QApplication(sys.argv)
myWindow = ResultController(None)
myWindow.show()
app.exec_()