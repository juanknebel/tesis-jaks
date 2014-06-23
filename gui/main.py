__author__ = 'zero'

import sys
from configuratorController import ConfiguratorController
from PyQt4 import QtGui

app = QtGui.QApplication(sys.argv)
myWindow = ConfiguratorController(None)
myWindow.show()
app.exec_()