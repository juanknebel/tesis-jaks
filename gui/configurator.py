# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'configurator.ui'
#
# Created: Sat Nov 22 17:25:31 2014
#      by: PyQt4 UI code generator 4.10.4
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

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.setWindowModality(QtCore.Qt.NonModal)
        MainWindow.resize(1049, 740)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        MainWindow.setMinimumSize(QtCore.QSize(1049, 740))
        MainWindow.setMaximumSize(QtCore.QSize(1049, 740))
        MainWindow.setLocale(QtCore.QLocale(QtCore.QLocale.Spanish, QtCore.QLocale.Argentina))
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.layoutWidget = QtGui.QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QtCore.QRect(0, 0, 1046, 695))
        self.layoutWidget.setObjectName(_fromUtf8("layoutWidget"))
        self.gridLayout_8 = QtGui.QGridLayout(self.layoutWidget)
        self.gridLayout_8.setMargin(0)
        self.gridLayout_8.setObjectName(_fromUtf8("gridLayout_8"))
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.grSourceData = QtGui.QGroupBox(self.layoutWidget)
        self.grSourceData.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.grSourceData.setFlat(False)
        self.grSourceData.setCheckable(False)
        self.grSourceData.setChecked(False)
        self.grSourceData.setObjectName(_fromUtf8("grSourceData"))
        self.gridLayout_2 = QtGui.QGridLayout(self.grSourceData)
        self.gridLayout_2.setObjectName(_fromUtf8("gridLayout_2"))
        self.gridLayout_5 = QtGui.QGridLayout()
        self.gridLayout_5.setObjectName(_fromUtf8("gridLayout_5"))
        self.rbDatabase = QtGui.QRadioButton(self.grSourceData)
        self.rbDatabase.setChecked(True)
        self.rbDatabase.setObjectName(_fromUtf8("rbDatabase"))
        self.gridLayout_5.addWidget(self.rbDatabase, 0, 0, 1, 1)
        self.grDataBase = QtGui.QGroupBox(self.grSourceData)
        self.grDataBase.setObjectName(_fromUtf8("grDataBase"))
        self.gridLayout = QtGui.QGridLayout(self.grDataBase)
        self.gridLayout.setObjectName(_fromUtf8("gridLayout"))
        self.label = QtGui.QLabel(self.grDataBase)
        self.label.setObjectName(_fromUtf8("label"))
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.fieldServer = QtGui.QLineEdit(self.grDataBase)
        self.fieldServer.setObjectName(_fromUtf8("fieldServer"))
        self.gridLayout.addWidget(self.fieldServer, 0, 1, 1, 1)
        self.label_2 = QtGui.QLabel(self.grDataBase)
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.fieldUser = QtGui.QLineEdit(self.grDataBase)
        self.fieldUser.setObjectName(_fromUtf8("fieldUser"))
        self.gridLayout.addWidget(self.fieldUser, 1, 1, 1, 1)
        self.label_3 = QtGui.QLabel(self.grDataBase)
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.gridLayout.addWidget(self.label_3, 2, 0, 1, 1)
        self.fieldPassword = QtGui.QLineEdit(self.grDataBase)
        font = QtGui.QFont()
        font.setStrikeOut(False)
        self.fieldPassword.setFont(font)
        self.fieldPassword.setInputMethodHints(QtCore.Qt.ImhNone)
        self.fieldPassword.setObjectName(_fromUtf8("fieldPassword"))
        self.gridLayout.addWidget(self.fieldPassword, 2, 1, 1, 1)
        self.label_4 = QtGui.QLabel(self.grDataBase)
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.gridLayout.addWidget(self.label_4, 3, 0, 1, 1)
        self.fieldDatabase = QtGui.QLineEdit(self.grDataBase)
        self.fieldDatabase.setObjectName(_fromUtf8("fieldDatabase"))
        self.gridLayout.addWidget(self.fieldDatabase, 3, 1, 1, 1)
        self.gridLayout_5.addWidget(self.grDataBase, 0, 1, 1, 1)
        self.rbFile = QtGui.QRadioButton(self.grSourceData)
        self.rbFile.setEnabled(True)
        self.rbFile.setObjectName(_fromUtf8("rbFile"))
        self.gridLayout_5.addWidget(self.rbFile, 1, 0, 1, 1)
        spacerItem = QtGui.QSpacerItem(368, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout_5.addItem(spacerItem, 1, 1, 1, 1)
        self.gridLayout_2.addLayout(self.gridLayout_5, 0, 0, 1, 1)
        self.verticalLayout.addWidget(self.grSourceData)
        self.groupBox = QtGui.QGroupBox(self.layoutWidget)
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.gridLayout_6 = QtGui.QGridLayout(self.groupBox)
        self.gridLayout_6.setObjectName(_fromUtf8("gridLayout_6"))
        self.label_30 = QtGui.QLabel(self.groupBox)
        self.label_30.setObjectName(_fromUtf8("label_30"))
        self.gridLayout_6.addWidget(self.label_30, 0, 0, 1, 1)
        self.label_24 = QtGui.QLabel(self.groupBox)
        self.label_24.setObjectName(_fromUtf8("label_24"))
        self.gridLayout_6.addWidget(self.label_24, 7, 0, 1, 1)
        self.fieldBudget = QtGui.QLineEdit(self.groupBox)
        self.fieldBudget.setObjectName(_fromUtf8("fieldBudget"))
        self.gridLayout_6.addWidget(self.fieldBudget, 3, 1, 1, 1)
        self.fieldSpecificItem = QtGui.QLineEdit(self.groupBox)
        self.fieldSpecificItem.setEnabled(False)
        self.fieldSpecificItem.setObjectName(_fromUtf8("fieldSpecificItem"))
        self.gridLayout_6.addWidget(self.fieldSpecificItem, 8, 1, 1, 1)
        self.checkWriteFile = QtGui.QCheckBox(self.groupBox)
        self.checkWriteFile.setObjectName(_fromUtf8("checkWriteFile"))
        self.gridLayout_6.addWidget(self.checkWriteFile, 9, 0, 1, 1)
        self.label_20 = QtGui.QLabel(self.groupBox)
        self.label_20.setObjectName(_fromUtf8("label_20"))
        self.gridLayout_6.addWidget(self.label_20, 3, 0, 1, 1)
        self.label_22 = QtGui.QLabel(self.groupBox)
        self.label_22.setObjectName(_fromUtf8("label_22"))
        self.gridLayout_6.addWidget(self.label_22, 5, 0, 1, 1)
        self.label_23 = QtGui.QLabel(self.groupBox)
        self.label_23.setObjectName(_fromUtf8("label_23"))
        self.gridLayout_6.addWidget(self.label_23, 6, 0, 1, 1)
        self.comboRankingStrategy = QtGui.QComboBox(self.groupBox)
        self.comboRankingStrategy.setObjectName(_fromUtf8("comboRankingStrategy"))
        self.comboRankingStrategy.addItem(_fromUtf8(""))
        self.comboRankingStrategy.addItem(_fromUtf8(""))
        self.comboRankingStrategy.addItem(_fromUtf8(""))
        self.comboRankingStrategy.addItem(_fromUtf8(""))
        self.comboRankingStrategy.addItem(_fromUtf8(""))
        self.gridLayout_6.addWidget(self.comboRankingStrategy, 7, 1, 1, 1)
        self.label_18 = QtGui.QLabel(self.groupBox)
        self.label_18.setObjectName(_fromUtf8("label_18"))
        self.gridLayout_6.addWidget(self.label_18, 1, 0, 1, 1)
        self.checkShowSolution = QtGui.QCheckBox(self.groupBox)
        self.checkShowSolution.setObjectName(_fromUtf8("checkShowSolution"))
        self.gridLayout_6.addWidget(self.checkShowSolution, 10, 0, 1, 1)
        self.checkSpecific = QtGui.QCheckBox(self.groupBox)
        self.checkSpecific.setObjectName(_fromUtf8("checkSpecific"))
        self.gridLayout_6.addWidget(self.checkSpecific, 8, 0, 1, 1)
        self.fieldNumFlakes = QtGui.QLineEdit(self.groupBox)
        self.fieldNumFlakes.setObjectName(_fromUtf8("fieldNumFlakes"))
        self.gridLayout_6.addWidget(self.fieldNumFlakes, 1, 1, 1, 1)
        self.comboSolver = QtGui.QComboBox(self.groupBox)
        self.comboSolver.setObjectName(_fromUtf8("comboSolver"))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.comboSolver.addItem(_fromUtf8(""))
        self.gridLayout_6.addWidget(self.comboSolver, 5, 1, 1, 1)
        self.fieldMaxTrials = QtGui.QLineEdit(self.groupBox)
        self.fieldMaxTrials.setObjectName(_fromUtf8("fieldMaxTrials"))
        self.gridLayout_6.addWidget(self.fieldMaxTrials, 2, 1, 1, 1)
        self.label_21 = QtGui.QLabel(self.groupBox)
        self.label_21.setObjectName(_fromUtf8("label_21"))
        self.gridLayout_6.addWidget(self.label_21, 4, 0, 1, 1)
        self.fieldToProduce = QtGui.QLineEdit(self.groupBox)
        self.fieldToProduce.setObjectName(_fromUtf8("fieldToProduce"))
        self.gridLayout_6.addWidget(self.fieldToProduce, 4, 1, 1, 1)
        self.fieldGamma = QtGui.QLineEdit(self.groupBox)
        self.fieldGamma.setObjectName(_fromUtf8("fieldGamma"))
        self.gridLayout_6.addWidget(self.fieldGamma, 6, 1, 1, 1)
        self.label_19 = QtGui.QLabel(self.groupBox)
        self.label_19.setObjectName(_fromUtf8("label_19"))
        self.gridLayout_6.addWidget(self.label_19, 2, 0, 1, 1)
        self.fieldDirectory = QtGui.QLineEdit(self.groupBox)
        self.fieldDirectory.setObjectName(_fromUtf8("fieldDirectory"))
        self.gridLayout_6.addWidget(self.fieldDirectory, 0, 1, 1, 1)
        self.btnDirectoryWork = QtGui.QToolButton(self.groupBox)
        self.btnDirectoryWork.setObjectName(_fromUtf8("btnDirectoryWork"))
        self.gridLayout_6.addWidget(self.btnDirectoryWork, 0, 2, 1, 1)
        self.verticalLayout.addWidget(self.groupBox)
        self.textEditResult = QtGui.QTextEdit(self.layoutWidget)
        self.textEditResult.setReadOnly(True)
        self.textEditResult.setObjectName(_fromUtf8("textEditResult"))
        self.verticalLayout.addWidget(self.textEditResult)
        self.gridLayout_8.addLayout(self.verticalLayout, 0, 0, 2, 1)
        self.btnExecute = QtGui.QPushButton(self.layoutWidget)
        self.btnExecute.setCheckable(False)
        self.btnExecute.setAutoDefault(False)
        self.btnExecute.setDefault(False)
        self.btnExecute.setFlat(False)
        self.btnExecute.setObjectName(_fromUtf8("btnExecute"))
        self.gridLayout_8.addWidget(self.btnExecute, 1, 3, 1, 1)
        self.verticalLayout_2 = QtGui.QVBoxLayout()
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.grFiles = QtGui.QGroupBox(self.layoutWidget)
        self.grFiles.setObjectName(_fromUtf8("grFiles"))
        self.gridLayout_7 = QtGui.QGridLayout(self.grFiles)
        self.gridLayout_7.setObjectName(_fromUtf8("gridLayout_7"))
        self.label_27 = QtGui.QLabel(self.grFiles)
        self.label_27.setObjectName(_fromUtf8("label_27"))
        self.gridLayout_7.addWidget(self.label_27, 2, 0, 1, 1)
        self.label_25 = QtGui.QLabel(self.grFiles)
        self.label_25.setObjectName(_fromUtf8("label_25"))
        self.gridLayout_7.addWidget(self.label_25, 0, 0, 1, 1)
        self.fileCosts = QtGui.QLineEdit(self.grFiles)
        self.fileCosts.setEnabled(False)
        self.fileCosts.setObjectName(_fromUtf8("fileCosts"))
        self.gridLayout_7.addWidget(self.fileCosts, 0, 1, 1, 1)
        self.label_26 = QtGui.QLabel(self.grFiles)
        self.label_26.setObjectName(_fromUtf8("label_26"))
        self.gridLayout_7.addWidget(self.label_26, 1, 0, 1, 1)
        self.fileCompat = QtGui.QLineEdit(self.grFiles)
        self.fileCompat.setEnabled(False)
        self.fileCompat.setObjectName(_fromUtf8("fileCompat"))
        self.gridLayout_7.addWidget(self.fileCompat, 1, 1, 1, 1)
        self.fileCover = QtGui.QLineEdit(self.grFiles)
        self.fileCover.setEnabled(False)
        self.fileCover.setObjectName(_fromUtf8("fileCover"))
        self.gridLayout_7.addWidget(self.fileCover, 2, 1, 1, 1)
        self.label_28 = QtGui.QLabel(self.grFiles)
        self.label_28.setObjectName(_fromUtf8("label_28"))
        self.gridLayout_7.addWidget(self.label_28, 3, 0, 1, 1)
        self.fileName = QtGui.QLineEdit(self.grFiles)
        self.fileName.setEnabled(False)
        self.fileName.setObjectName(_fromUtf8("fileName"))
        self.gridLayout_7.addWidget(self.fileName, 3, 1, 1, 1)
        self.label_29 = QtGui.QLabel(self.grFiles)
        self.label_29.setObjectName(_fromUtf8("label_29"))
        self.gridLayout_7.addWidget(self.label_29, 4, 0, 1, 1)
        self.fileType = QtGui.QLineEdit(self.grFiles)
        self.fileType.setEnabled(False)
        self.fileType.setObjectName(_fromUtf8("fileType"))
        self.gridLayout_7.addWidget(self.fileType, 4, 1, 1, 1)
        self.toolButton = QtGui.QToolButton(self.grFiles)
        self.toolButton.setObjectName(_fromUtf8("toolButton"))
        self.gridLayout_7.addWidget(self.toolButton, 0, 2, 1, 1)
        self.toolButton_2 = QtGui.QToolButton(self.grFiles)
        self.toolButton_2.setObjectName(_fromUtf8("toolButton_2"))
        self.gridLayout_7.addWidget(self.toolButton_2, 1, 2, 1, 1)
        self.toolButton_3 = QtGui.QToolButton(self.grFiles)
        self.toolButton_3.setObjectName(_fromUtf8("toolButton_3"))
        self.gridLayout_7.addWidget(self.toolButton_3, 2, 2, 1, 1)
        self.toolButton_4 = QtGui.QToolButton(self.grFiles)
        self.toolButton_4.setObjectName(_fromUtf8("toolButton_4"))
        self.gridLayout_7.addWidget(self.toolButton_4, 3, 2, 1, 1)
        self.toolButton_5 = QtGui.QToolButton(self.grFiles)
        self.toolButton_5.setObjectName(_fromUtf8("toolButton_5"))
        self.gridLayout_7.addWidget(self.toolButton_5, 4, 2, 1, 1)
        self.verticalLayout_2.addWidget(self.grFiles)
        self.grTable = QtGui.QGroupBox(self.layoutWidget)
        self.grTable.setObjectName(_fromUtf8("grTable"))
        self.gridLayout_3 = QtGui.QGridLayout(self.grTable)
        self.gridLayout_3.setObjectName(_fromUtf8("gridLayout_3"))
        self.label_5 = QtGui.QLabel(self.grTable)
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.gridLayout_3.addWidget(self.label_5, 0, 0, 1, 1)
        self.fieldCosts = QtGui.QLineEdit(self.grTable)
        self.fieldCosts.setObjectName(_fromUtf8("fieldCosts"))
        self.gridLayout_3.addWidget(self.fieldCosts, 0, 1, 1, 1)
        self.fieldCover = QtGui.QLineEdit(self.grTable)
        self.fieldCover.setObjectName(_fromUtf8("fieldCover"))
        self.gridLayout_3.addWidget(self.fieldCover, 2, 1, 1, 1)
        self.label_7 = QtGui.QLabel(self.grTable)
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.gridLayout_3.addWidget(self.label_7, 2, 0, 1, 1)
        self.fieldCovertion = QtGui.QLineEdit(self.grTable)
        self.fieldCovertion.setObjectName(_fromUtf8("fieldCovertion"))
        self.gridLayout_3.addWidget(self.fieldCovertion, 3, 1, 1, 1)
        self.label_6 = QtGui.QLabel(self.grTable)
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.gridLayout_3.addWidget(self.label_6, 1, 0, 1, 1)
        self.label_8 = QtGui.QLabel(self.grTable)
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.gridLayout_3.addWidget(self.label_8, 3, 0, 1, 1)
        self.fieldCompatibility = QtGui.QLineEdit(self.grTable)
        self.fieldCompatibility.setObjectName(_fromUtf8("fieldCompatibility"))
        self.gridLayout_3.addWidget(self.fieldCompatibility, 1, 1, 1, 1)
        self.verticalLayout_2.addWidget(self.grTable)
        self.grFields = QtGui.QGroupBox(self.layoutWidget)
        self.grFields.setObjectName(_fromUtf8("grFields"))
        self.gridLayout_4 = QtGui.QGridLayout(self.grFields)
        self.gridLayout_4.setObjectName(_fromUtf8("gridLayout_4"))
        self.label_9 = QtGui.QLabel(self.grFields)
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.gridLayout_4.addWidget(self.label_9, 0, 0, 1, 1)
        self.fieldCost = QtGui.QLineEdit(self.grFields)
        self.fieldCost.setObjectName(_fromUtf8("fieldCost"))
        self.gridLayout_4.addWidget(self.fieldCost, 0, 1, 1, 1)
        self.label_10 = QtGui.QLabel(self.grFields)
        self.label_10.setObjectName(_fromUtf8("label_10"))
        self.gridLayout_4.addWidget(self.label_10, 1, 0, 1, 1)
        self.fieldCover_2 = QtGui.QLineEdit(self.grFields)
        self.fieldCover_2.setObjectName(_fromUtf8("fieldCover_2"))
        self.gridLayout_4.addWidget(self.fieldCover_2, 1, 1, 1, 1)
        self.label_11 = QtGui.QLabel(self.grFields)
        self.label_11.setObjectName(_fromUtf8("label_11"))
        self.gridLayout_4.addWidget(self.label_11, 2, 0, 1, 1)
        self.fieldPrimary = QtGui.QLineEdit(self.grFields)
        self.fieldPrimary.setObjectName(_fromUtf8("fieldPrimary"))
        self.gridLayout_4.addWidget(self.fieldPrimary, 2, 1, 1, 1)
        self.label_12 = QtGui.QLabel(self.grFields)
        self.label_12.setObjectName(_fromUtf8("label_12"))
        self.gridLayout_4.addWidget(self.label_12, 3, 0, 1, 1)
        self.fieldIDescription = QtGui.QLineEdit(self.grFields)
        self.fieldIDescription.setObjectName(_fromUtf8("fieldIDescription"))
        self.gridLayout_4.addWidget(self.fieldIDescription, 3, 1, 1, 1)
        self.label_13 = QtGui.QLabel(self.grFields)
        self.label_13.setObjectName(_fromUtf8("label_13"))
        self.gridLayout_4.addWidget(self.label_13, 4, 0, 1, 1)
        self.fieldElement = QtGui.QLineEdit(self.grFields)
        self.fieldElement.setObjectName(_fromUtf8("fieldElement"))
        self.gridLayout_4.addWidget(self.fieldElement, 4, 1, 1, 1)
        self.label_14 = QtGui.QLabel(self.grFields)
        self.label_14.setObjectName(_fromUtf8("label_14"))
        self.gridLayout_4.addWidget(self.label_14, 5, 0, 1, 1)
        self.fieldItem = QtGui.QLineEdit(self.grFields)
        self.fieldItem.setObjectName(_fromUtf8("fieldItem"))
        self.gridLayout_4.addWidget(self.fieldItem, 5, 1, 1, 1)
        self.label_15 = QtGui.QLabel(self.grFields)
        self.label_15.setObjectName(_fromUtf8("label_15"))
        self.gridLayout_4.addWidget(self.label_15, 6, 0, 1, 1)
        self.fieldItem1 = QtGui.QLineEdit(self.grFields)
        self.fieldItem1.setObjectName(_fromUtf8("fieldItem1"))
        self.gridLayout_4.addWidget(self.fieldItem1, 6, 1, 1, 1)
        self.label_16 = QtGui.QLabel(self.grFields)
        self.label_16.setObjectName(_fromUtf8("label_16"))
        self.gridLayout_4.addWidget(self.label_16, 7, 0, 1, 1)
        self.fieldItem2 = QtGui.QLineEdit(self.grFields)
        self.fieldItem2.setObjectName(_fromUtf8("fieldItem2"))
        self.gridLayout_4.addWidget(self.fieldItem2, 7, 1, 1, 1)
        self.label_17 = QtGui.QLabel(self.grFields)
        self.label_17.setObjectName(_fromUtf8("label_17"))
        self.gridLayout_4.addWidget(self.label_17, 8, 0, 1, 1)
        self.fieldSimilarity = QtGui.QLineEdit(self.grFields)
        self.fieldSimilarity.setObjectName(_fromUtf8("fieldSimilarity"))
        self.gridLayout_4.addWidget(self.fieldSimilarity, 8, 1, 1, 1)
        self.verticalLayout_2.addWidget(self.grFields)
        self.gridLayout_8.addLayout(self.verticalLayout_2, 0, 1, 1, 3)
        spacerItem1 = QtGui.QSpacerItem(398, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.gridLayout_8.addItem(spacerItem1, 1, 1, 1, 1)
        self.btnPreview = QtGui.QPushButton(self.layoutWidget)
        self.btnPreview.setObjectName(_fromUtf8("btnPreview"))
        self.gridLayout_8.addWidget(self.btnPreview, 1, 2, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1049, 20))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName(_fromUtf8("menuFile"))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        MainWindow.setStatusBar(self.statusbar)
        self.actionLoadFile = QtGui.QAction(MainWindow)
        self.actionLoadFile.setObjectName(_fromUtf8("actionLoadFile"))
        self.actionSaveFile = QtGui.QAction(MainWindow)
        self.actionSaveFile.setObjectName(_fromUtf8("actionSaveFile"))
        self.actionExit = QtGui.QAction(MainWindow)
        self.actionExit.setObjectName(_fromUtf8("actionExit"))
        self.actionWorkDirectory = QtGui.QAction(MainWindow)
        self.actionWorkDirectory.setCheckable(False)
        self.actionWorkDirectory.setObjectName(_fromUtf8("actionWorkDirectory"))
        self.menuFile.addAction(self.actionLoadFile)
        self.menuFile.addAction(self.actionSaveFile)
        self.menuFile.addAction(self.actionExit)
        self.menubar.addAction(self.menuFile.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "Configurador", None))
        self.grSourceData.setTitle(_translate("MainWindow", "Fuente de datos", None))
        self.rbDatabase.setText(_translate("MainWindow", "Usar base de datos", None))
        self.grDataBase.setTitle(_translate("MainWindow", "Base de Datos", None))
        self.label.setText(_translate("MainWindow", "Server", None))
        self.label_2.setText(_translate("MainWindow", "Usuario", None))
        self.label_3.setText(_translate("MainWindow", "Password", None))
        self.label_4.setText(_translate("MainWindow", "Base de dato", None))
        self.rbFile.setText(_translate("MainWindow", "Usar archivos de datos", None))
        self.groupBox.setTitle(_translate("MainWindow", "Configuración Algoritmo", None))
        self.label_30.setText(_translate("MainWindow", "Directorio de trabajo", None))
        self.label_24.setText(_translate("MainWindow", "Estrategía del algoritmo", None))
        self.checkWriteFile.setText(_translate("MainWindow", "Escribir archivo", None))
        self.label_20.setText(_translate("MainWindow", "Presupuesto", None))
        self.label_22.setText(_translate("MainWindow", "Algoritmo a ejecutar", None))
        self.label_23.setText(_translate("MainWindow", "Gamma", None))
        self.comboRankingStrategy.setItemText(0, _translate("MainWindow", "RANK_BY_INTRA", None))
        self.comboRankingStrategy.setItemText(1, _translate("MainWindow", "RANK_BY_INTRA_INTER", None))
        self.comboRankingStrategy.setItemText(2, _translate("MainWindow", "RANK_BY_DENSEST_SUBGRAPH", None))
        self.comboRankingStrategy.setItemText(3, _translate("MainWindow", "RANK_BY_INTRA_INTER_TUPLE", None))
        self.comboRankingStrategy.setItemText(4, _translate("MainWindow", "RANK_BY_INTRA_INTER_PROPORTIONAL", None))
        self.label_18.setText(_translate("MainWindow", "Cantidad de bundles", None))
        self.checkShowSolution.setText(_translate("MainWindow", "Mostrar resultado en pantalla", None))
        self.checkSpecific.setText(_translate("MainWindow", "Item específico", None))
        self.comboSolver.setItemText(0, _translate("MainWindow", "ClusterAndPickSolver", None))
        self.comboSolver.setItemText(1, _translate("MainWindow", "RestrictedHACSolver", None))
        self.comboSolver.setItemText(2, _translate("MainWindow", "RestrictedHACSpecificSolver", None))
        self.comboSolver.setItemText(3, _translate("MainWindow", "RandomBOBOSolver", None))
        self.comboSolver.setItemText(4, _translate("MainWindow", "RandomSOBOSolver", None))
        self.comboSolver.setItemText(5, _translate("MainWindow", "ExhaustiveGreedyAnySimSolver", None))
        self.comboSolver.setItemText(6, _translate("MainWindow", "ExhaustiveGreedySumSimSolver", None))
        self.comboSolver.setItemText(7, _translate("MainWindow", "SequentialScanSolver", None))
        self.comboSolver.setItemText(8, _translate("MainWindow", "LocalSearch", None))
        self.label_21.setText(_translate("MainWindow", "Cantidad de bundles antes de elegir", None))
        self.label_19.setText(_translate("MainWindow", "Cantidad de iteraciones", None))
        self.btnDirectoryWork.setText(_translate("MainWindow", "...", None))
        self.btnExecute.setText(_translate("MainWindow", "Ejecutar", None))
        self.grFiles.setTitle(_translate("MainWindow", "Archivos", None))
        self.label_27.setText(_translate("MainWindow", "Covertura", None))
        self.label_25.setText(_translate("MainWindow", "Costos", None))
        self.label_26.setText(_translate("MainWindow", "Compatibilidad", None))
        self.label_28.setText(_translate("MainWindow", "Nombre", None))
        self.label_29.setText(_translate("MainWindow", "Tipo", None))
        self.toolButton.setText(_translate("MainWindow", "...", None))
        self.toolButton_2.setText(_translate("MainWindow", "...", None))
        self.toolButton_3.setText(_translate("MainWindow", "...", None))
        self.toolButton_4.setText(_translate("MainWindow", "...", None))
        self.toolButton_5.setText(_translate("MainWindow", "...", None))
        self.grTable.setTitle(_translate("MainWindow", "Tablas", None))
        self.label_5.setText(_translate("MainWindow", "Costos", None))
        self.label_7.setText(_translate("MainWindow", "Covertura", None))
        self.label_6.setText(_translate("MainWindow", "Compatibilidad", None))
        self.label_8.setText(_translate("MainWindow", "Mapeo", None))
        self.grFields.setTitle(_translate("MainWindow", "Campos", None))
        self.label_9.setText(_translate("MainWindow", "Costo", None))
        self.label_10.setText(_translate("MainWindow", "Covertura", None))
        self.label_11.setText(_translate("MainWindow", "Primario", None))
        self.label_12.setText(_translate("MainWindow", "Descripción", None))
        self.label_13.setText(_translate("MainWindow", "Elemento", None))
        self.label_14.setText(_translate("MainWindow", "Item", None))
        self.label_15.setText(_translate("MainWindow", "Item compatibilidad", None))
        self.label_16.setText(_translate("MainWindow", "Item compatibilidad2", None))
        self.label_17.setText(_translate("MainWindow", "Similaridad", None))
        self.btnPreview.setText(_translate("MainWindow", "Previsualizar", None))
        self.menuFile.setTitle(_translate("MainWindow", "Archivo", None))
        self.actionLoadFile.setText(_translate("MainWindow", "Cargar Archivo", None))
        self.actionSaveFile.setText(_translate("MainWindow", "Guardar Archivo", None))
        self.actionExit.setText(_translate("MainWindow", "Salir", None))
        self.actionWorkDirectory.setText(_translate("MainWindow", "Directorio del binario", None))

