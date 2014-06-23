__author__ = 'zero'
from PyQt4 import QtCore, QtGui
from result import Ui_DialogResult
import commands
from configurationJaks import ConfigurationJaks


class ResultController(QtGui.QDialog, Ui_DialogResult):
    def __init__(self, parent=None):
        QtGui.QDialog.__init__(self, parent)
        self.setupUi(self)
        self.btnExecute.clicked.connect(self.execute_tesis)
        self.btnBinary.clicked.connect(self.choose_binary_file)
        self.btnConfig.clicked.connect(self.choose_config_file)

    def execute_tesis(self):
        self.btnExecute.setEnabled(False)
        cmd = self.fieldBinary.text()
        the_config = self.comboConfig.currentIndex()
        if the_config == 0:
            cmd = cmd + ' -h'
        elif the_config == 1:
            cmd = cmd + ' -s'
        elif the_config == 2:
            cmd = cmd + ' -f ' + self.fieldConfigFile.text()
        elif the_config == 3:
            cmd = cmd + ' -t'
        if self.checkBoxLog.isChecked():
            cmd = cmd + ' -l'
        output = commands.getoutput(str(cmd))
        self.textResult.setText(output[0:output.find('profi')])
        self.btnExecute.setEnabled(True)

    def choose_binary_file(self):
        self.fieldBinary.setText(QtGui.QFileDialog.getOpenFileName())

    def choose_config_file(self):
        self.fieldConfigFile.setText(QtGui.QFileDialog.getOpenFileName())