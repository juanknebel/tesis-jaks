# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'comparator.ui'
#
# Created by: PyQt4 UI code generator 4.10.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_mainWindow(object):
    def setupUi(self, mainWindow):
        mainWindow.setObjectName(_fromUtf8("mainWindow"))
        mainWindow.resize(536, 403)
        mainWindow.setLocale(QtCore.QLocale(QtCore.QLocale.Spanish, QtCore.QLocale.Argentina))
        self.centralwidget = QtGui.QWidget(mainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.gridLayoutWidget = QtGui.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(0, 0, 531, 381))
        self.gridLayoutWidget.setObjectName(_fromUtf8("gridLayoutWidget"))
        self.gridLayout = QtGui.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setMargin(0)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.horizontalLayout_4 = QtGui.QHBoxLayout()
        self.horizontalLayout_4.setObjectName(_fromUtf8("horizontalLayout_4"))
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_4.addItem(spacerItem)
        self.compareButton = QtGui.QPushButton(self.gridLayoutWidget)
        self.compareButton.setObjectName(_fromUtf8("compareButton"))
        self.horizontalLayout_4.addWidget(self.compareButton)
        self.gridLayout.addLayout(self.horizontalLayout_4, 4, 0, 1, 1)
        self.labelResult = QtGui.QLabel(self.gridLayoutWidget)
        self.labelResult.setObjectName(_fromUtf8("labelResult"))
        self.gridLayout.addWidget(self.labelResult, 2, 0, 1, 1)
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.labelFileNameA = QtGui.QLabel(self.gridLayoutWidget)
        self.labelFileNameA.setObjectName(_fromUtf8("labelFileNameA"))
        self.horizontalLayout_2.addWidget(self.labelFileNameA)
        self.fileNameA = QtGui.QLineEdit(self.gridLayoutWidget)
        self.fileNameA.setObjectName(_fromUtf8("fileNameA"))
        self.horizontalLayout_2.addWidget(self.fileNameA)
        self.searchFileButtonA = QtGui.QPushButton(self.gridLayoutWidget)
        self.searchFileButtonA.setObjectName(_fromUtf8("searchFileButtonA"))
        self.horizontalLayout_2.addWidget(self.searchFileButtonA)
        self.gridLayout.addLayout(self.horizontalLayout_2, 0, 0, 1, 1)
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.labelFileNameA_2 = QtGui.QLabel(self.gridLayoutWidget)
        self.labelFileNameA_2.setObjectName(_fromUtf8("labelFileNameA_2"))
        self.horizontalLayout_3.addWidget(self.labelFileNameA_2)
        self.fileNameB = QtGui.QLineEdit(self.gridLayoutWidget)
        self.fileNameB.setObjectName(_fromUtf8("fileNameB"))
        self.horizontalLayout_3.addWidget(self.fileNameB)
        self.searchFileButtonB = QtGui.QPushButton(self.gridLayoutWidget)
        self.searchFileButtonB.setObjectName(_fromUtf8("searchFileButtonB"))
        self.horizontalLayout_3.addWidget(self.searchFileButtonB)
        self.gridLayout.addLayout(self.horizontalLayout_3, 1, 0, 1, 1)
        self.resultText = QtGui.QPlainTextEdit(self.gridLayoutWidget)
        self.resultText.setEnabled(True)
        self.resultText.setReadOnly(True)
        self.resultText.setObjectName(_fromUtf8("resultText"))
        self.gridLayout.addWidget(self.resultText, 3, 0, 1, 1)
        mainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtGui.QStatusBar(mainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        mainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(mainWindow)
        QtCore.QMetaObject.connectSlotsByName(mainWindow)

    def retranslateUi(self, mainWindow):
        mainWindow.setWindowTitle(_translate("mainWindow", "Comparador de Bundles", None))
        self.compareButton.setText(_translate("mainWindow", "Comparar", None))
        self.labelResult.setText(_translate("mainWindow", "Resultado", None))
        self.labelFileNameA.setText(_translate("mainWindow", "Solución 1", None))
        self.searchFileButtonA.setText(_translate("mainWindow", "...", None))
        self.labelFileNameA_2.setText(_translate("mainWindow", "Solución 2", None))
        self.searchFileButtonB.setText(_translate("mainWindow", "...", None))

