# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'result.ui'
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

class Ui_DialogResult(object):
    def setupUi(self, DialogResult):
        DialogResult.setObjectName(_fromUtf8("DialogResult"))
        DialogResult.setWindowModality(QtCore.Qt.WindowModal)
        DialogResult.resize(602, 445)
        DialogResult.setMinimumSize(QtCore.QSize(602, 445))
        DialogResult.setMaximumSize(QtCore.QSize(602, 445))
        self.layoutWidget = QtGui.QWidget(DialogResult)
        self.layoutWidget.setGeometry(QtCore.QRect(0, 0, 601, 441))
        self.layoutWidget.setObjectName(_fromUtf8("layoutWidget"))
        self.gridLayout_2 = QtGui.QGridLayout(self.layoutWidget)
        self.gridLayout_2.setMargin(0)
        self.gridLayout_2.setObjectName(_fromUtf8("gridLayout_2"))
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.comboConfig = QtGui.QComboBox(self.layoutWidget)
        self.comboConfig.setObjectName(_fromUtf8("comboConfig"))
        self.comboConfig.addItem(_fromUtf8(""))
        self.comboConfig.addItem(_fromUtf8(""))
        self.comboConfig.addItem(_fromUtf8(""))
        self.comboConfig.addItem(_fromUtf8(""))
        self.gridLayout.addWidget(self.comboConfig, 1, 1, 1, 1)
        self.label_3 = QtGui.QLabel(self.layoutWidget)
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.gridLayout.addWidget(self.label_3, 2, 0, 1, 1)
        self.checkBoxLog = QtGui.QCheckBox(self.layoutWidget)
        self.checkBoxLog.setObjectName(_fromUtf8("checkBoxLog"))
        self.gridLayout.addWidget(self.checkBoxLog, 3, 0, 1, 1)
        self.label = QtGui.QLabel(self.layoutWidget)
        self.label.setObjectName(_fromUtf8("label"))
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.fieldBinary = QtGui.QLineEdit(self.layoutWidget)
        self.fieldBinary.setObjectName(_fromUtf8("fieldBinary"))
        self.gridLayout.addWidget(self.fieldBinary, 0, 1, 1, 1)
        self.label_2 = QtGui.QLabel(self.layoutWidget)
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.fieldConfigFile = QtGui.QLineEdit(self.layoutWidget)
        self.fieldConfigFile.setObjectName(_fromUtf8("fieldConfigFile"))
        self.gridLayout.addWidget(self.fieldConfigFile, 2, 1, 1, 1)
        self.btnConfig = QtGui.QToolButton(self.layoutWidget)
        self.btnConfig.setObjectName(_fromUtf8("btnConfig"))
        self.gridLayout.addWidget(self.btnConfig, 2, 2, 1, 1)
        self.btnBinary = QtGui.QToolButton(self.layoutWidget)
        self.btnBinary.setObjectName(_fromUtf8("btnBinary"))
        self.gridLayout.addWidget(self.btnBinary, 0, 2, 1, 1)
        self.gridLayout_2.addLayout(self.gridLayout, 0, 0, 1, 2)
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.label_4 = QtGui.QLabel(self.layoutWidget)
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.verticalLayout.addWidget(self.label_4)
        self.textResult = QtGui.QTextEdit(self.layoutWidget)
        self.textResult.setReadOnly(True)
        self.textResult.setObjectName(_fromUtf8("textResult"))
        self.verticalLayout.addWidget(self.textResult)
        self.gridLayout_2.addLayout(self.verticalLayout, 1, 0, 1, 2)
        spacerItem = QtGui.QSpacerItem(328, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout_2.addItem(spacerItem, 2, 0, 1, 1)
        self.btnExecute = QtGui.QPushButton(self.layoutWidget)
        self.btnExecute.setObjectName(_fromUtf8("btnExecute"))
        self.gridLayout_2.addWidget(self.btnExecute, 2, 1, 1, 1)

        self.retranslateUi(DialogResult)
        QtCore.QMetaObject.connectSlotsByName(DialogResult)

    def retranslateUi(self, DialogResult):
        DialogResult.setWindowTitle(_translate("DialogResult", "Dialog", None))
        self.comboConfig.setItemText(0, _translate("DialogResult", "Ayuda", None))
        self.comboConfig.setItemText(1, _translate("DialogResult", "Calculo de similitud", None))
        self.comboConfig.setItemText(2, _translate("DialogResult", "Ejecutar con archivo de configuracion", None))
        self.comboConfig.setItemText(3, _translate("DialogResult", "Ejutar tests internos", None))
        self.label_3.setText(_translate("DialogResult", "Archivo configuracion", None))
        self.checkBoxLog.setText(_translate("DialogResult", "Activar el log", None))
        self.label.setText(_translate("DialogResult", "Nombre del binario", None))
        self.label_2.setText(_translate("DialogResult", "Argumentos", None))
        self.btnConfig.setText(_translate("DialogResult", "...", None))
        self.btnBinary.setText(_translate("DialogResult", "...", None))
        self.label_4.setText(_translate("DialogResult", "Resultado", None))
        self.btnExecute.setText(_translate("DialogResult", "Ok", None))

