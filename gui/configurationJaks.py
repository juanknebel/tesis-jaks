__author__ = 'zero'

_comment = '#'
_separator = '\t'
_final_line = '\n'

from mappingFields import mappingGuiFile


class ConfigurationJaks(object):
    def __init__(self):
        self.the_values = {}

    def add_value(self, field_in_ui, value):
        self.the_values[mappingGuiFile[str(field_in_ui)]] = str(value)

    def get_value(self, field_in_ui):
        if mappingGuiFile[str(field_in_ui)] in self.the_values:
            return self.the_values[mappingGuiFile[str(field_in_ui)]]

    def remove_value(self, field_in_ui):
        if mappingGuiFile[str(field_in_ui)] in self.the_values:
            del self.the_values[mappingGuiFile[str(field_in_ui)]]

    def save_to_file(self, file_name):
        with open(file_name, 'w') as file_to_save:
            file_to_save.write(self.__str__())

    def load_file(self, file_name):
        with open(file_name, 'r') as file_to_read:
            the_configuration = file_to_read.read().split(_final_line)
            for elem in the_configuration:
                if elem == '' or elem[0] == '#':
                    pass
                else:
                    line = elem.split(_separator)
                    self.the_values[line[0]] = str(line[1])

    def has_mapping_key(self, field_in_ui):
        return mappingGuiFile[str(field_in_ui)] in self.the_values

    def get_all_mapping_keys(self):
        return mappingGuiFile.keys()

    def __repr__(self):
        result = ''
        for key, value in self.the_values.iteritems():
            if value is None:
                result = result + key + _separator + 'None' + _final_line
            else:
                result = result + key + _separator + value + _final_line
        return result

    def __str__(self):
        return self.__repr__()