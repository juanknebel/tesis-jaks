__author__ = 'zero'
from configurator import Ui_MainWindow
from PyQt4 import QtCore, QtGui
from configurationJaks import ConfigurationJaks
from resultController import ResultController


class ConfiguratorController(QtGui.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        QtGui.QMainWindow.__init__(self, parent)
        self.setupUi(self)
        self.config_jaks = ConfigurationJaks()
        #self.fieldBinaryWork.setText(os.getcwd())
        self.btnExecute.clicked.connect(self.execute_tesis)
        self.checkSpecific.clicked.connect(self.set_specific_item_value)
        self.rbDatabase.clicked.connect(self.activate_db_fields)
        self.rbFile.clicked.connect(self.activate_file_fields)
        self.btnDirectoryWork.clicked.connect(self.choose_work_directory)
        self.btnPreview.clicked.connect(self.preview_file)
        self.actionExit.triggered.connect(QtGui.qApp.quit)
        self.actionLoadFile.triggered.connect(self.load_config_file)
        self.actionSaveFile.triggered.connect(self.save_config_file)

    def execute_tesis(self):
        self.btnExecute.setEnabled(False)
        self.fill_config_jaks()
        the_dialog = ResultController(None)
        the_dialog.exec_()
        self.btnExecute.setEnabled(True)

    def preview_file(self):
        self.fill_config_jaks()
        self.textEditResult.setText(self.config_jaks.__str__())

    def load_config_file(self):
        file_name_to_load = QtGui.QFileDialog.getOpenFileName()
        self.config_jaks.load_file(file_name_to_load)
        self.fill_grid_with_config()

    def save_config_file(self):
        self.fill_config_jaks()
        file_name_to_save = QtGui.QFileDialog.getOpenFileName()
        self.config_jaks.save_to_file(file_name_to_save)

    def choose_work_directory(self):
        self.fieldDirectory.setText(QtGui.QFileDialog.getExistingDirectory(self, 'Seleccione directorio de trabajo',
                                                                            './',  QtGui.QFileDialog.ShowDirsOnly))

    def activate_db_fields(self):
        self.set_files_fields(False)
        self.set_db_fields(True)

    def activate_file_fields(self):
        self.set_files_fields(True)
        self.set_db_fields(False)

    def set_files_fields(self, a_value):
        self.fileCompat.setEnabled(a_value)
        self.fileCosts.setEnabled(a_value)
        self.fileCover.setEnabled(a_value)
        self.fileName.setEnabled(a_value)
        self.fileType.setEnabled(a_value)

    def set_db_fields(self, a_value):
        self.fieldCosts.setEnabled(a_value)
        self.fieldCompatibility.setEnabled(a_value)
        self.fieldCover.setEnabled(a_value)
        self.fieldCovertion.setEnabled(a_value)
        self.fieldCost.setEnabled(a_value)
        self.fieldCover_2.setEnabled(a_value)
        self.fieldPrimary.setEnabled(a_value)
        self.fieldIDescription.setEnabled(a_value)
        self.fieldElement.setEnabled(a_value)
        self.fieldItem.setEnabled(a_value)
        self.fieldItem1.setEnabled(a_value)
        self.fieldItem2.setEnabled(a_value)
        self.fieldSimilarity.setEnabled(a_value)
        self.fieldServer.setEnabled(a_value)
        self.fieldUser.setEnabled(a_value)
        self.fieldPassword.setEnabled(a_value)
        self.fieldDatabase.setEnabled(a_value)

    def set_specific_item_value(self):
        if self.checkSpecific.isChecked():
            self.fieldSpecificItem.setEnabled(True)
        else:
            self.fieldSpecificItem.setText('')
            self.fieldSpecificItem.setEnabled(False)

    def fill_grid_with_config(self):
        all_keys = self.config_jaks.get_all_mapping_keys()
        for key in all_keys:
            if self.config_jaks.has_mapping_key(key):
                try:
                    a_field = getattr(self, key)
                    if isinstance(a_field, QtGui.QLineEdit):
                        a_field.setText(self.config_jaks.get_value(key))
                    elif isinstance(a_field, QtGui.QCheckBox):
                        a_field.setChecked(int(self.config_jaks.get_value(key)) == 1)
                        if a_field.objectName() == 'checkSpecific':
                            self.fieldSpecificItem.setEnabled(int(self.config_jaks.get_value(key)) == 1)
                    elif isinstance(a_field, QtGui.QRadioButton):
                        if a_field.objectName() == 'rbDatabase' and int(self.config_jaks.get_value(key)) == 1:
                            a_field.setChecked(True)
                            self.activate_db_fields()
                        elif a_field.objectName() == 'rbFile' and int(self.config_jaks.get_value(key)) == 0:
                            a_field.setChecked(True)
                            self.activate_file_fields()
                    elif isinstance(a_field, QtGui.QComboBox):
                        a_field.setCurrentIndex(int(self.config_jaks.get_value(key)))
                except Exception:
                    pass

    def fill_config_jaks(self):
        if self.rbDatabase.isChecked():
            self.config_jaks.add_value(self.rbDatabase.objectName(), 1)
            self.config_jaks.add_value(self.fieldServer.objectName(), self.fieldServer.text())
            self.config_jaks.add_value(self.fieldUser.objectName(), self.fieldUser.text())
            self.config_jaks.add_value(self.fieldPassword.objectName(), self.fieldPassword.text())
            self.config_jaks.add_value(self.fieldDatabase.objectName(), self.fieldDatabase.text())
            self.config_jaks.add_value(self.fieldCosts.objectName(), self.fieldCosts.text())
            self.config_jaks.add_value(self.fieldCompatibility.objectName(), self.fieldCompatibility.text())
            self.config_jaks.add_value(self.fieldCover.objectName(), self.fieldCover.text())
            self.config_jaks.add_value(self.fieldCovertion.objectName(), self.fieldCovertion.text())
            self.config_jaks.add_value(self.fieldCost.objectName(), self.fieldCost.text())
            self.config_jaks.add_value(self.fieldCover_2.objectName(), self.fieldCover_2.text())
            self.config_jaks.add_value(self.fieldPrimary.objectName(), self.fieldPrimary.text())
            self.config_jaks.add_value(self.fieldIDescription.objectName(), self.fieldIDescription.text())
            self.config_jaks.add_value(self.fieldElement.objectName(), self.fieldElement.text())
            self.config_jaks.add_value(self.fieldItem.objectName(), self.fieldItem.text())
            self.config_jaks.add_value(self.fieldItem1.objectName(), self.fieldItem1.text())
            self.config_jaks.add_value(self.fieldItem2.objectName(), self.fieldItem2.text())
        elif self.rbFile.isChecked():
            self.config_jaks.add_value(self.rbFile.objectName(), 0)
            self.config_jaks.add_value(self.fileCosts.objectName(), self.fileCosts.text())
            self.config_jaks.add_value(self.fileCompat.objectName(), self.fileCompat.text())
            self.config_jaks.add_value(self.fileCover.objectName(), self.fileCover.text())
            self.config_jaks.add_value(self.fileName.objectName(), self.fileName.text())
            self.config_jaks.add_value(self.fileType.objectName(), self.fileType.text())
        self.config_jaks.add_value(self.fieldDirectory.objectName(), self.fieldDirectory.text())
        self.config_jaks.add_value(self.fieldSimilarity.objectName(), self.fieldSimilarity.text())
        self.config_jaks.add_value(self.fieldNumFlakes.objectName(), self.fieldNumFlakes.text())
        self.config_jaks.add_value(self.fieldMaxTrials.objectName(), self.fieldMaxTrials.text())
        self.config_jaks.add_value(self.fieldBudget.objectName(), self.fieldBudget.text())
        self.config_jaks.add_value(self.fieldToProduce.objectName(), self.fieldToProduce.text())
        self.config_jaks.add_value(self.comboSolver.objectName(), self.comboSolver.currentIndex())
        self.config_jaks.add_value(self.fieldGamma.objectName(), self.fieldGamma.text())
        self.config_jaks.add_value(self.comboRankingStrategy.objectName(), self.comboRankingStrategy.currentIndex())
        if self.checkSpecific.isChecked():
            self.config_jaks.add_value(self.checkSpecific.objectName(), 1)
            self.config_jaks.add_value(self.fieldSpecificItem.objectName(), self.fieldSpecificItem.text())
        else:
            self.config_jaks.add_value(self.checkSpecific.objectName(), 0)
        if self.checkWriteFile.isChecked():
            self.config_jaks.add_value(self.checkWriteFile.objectName(), 1)
        else:
            self.config_jaks.add_value(self.checkWriteFile.objectName(), 0)
        if self.checkShowSolution.isChecked():
            self.config_jaks.add_value(self.checkShowSolution.objectName(), 1)
        else:
            self.config_jaks.add_value(self.checkShowSolution.objectName(), 0)