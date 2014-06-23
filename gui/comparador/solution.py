class Author(object):
    def __init__(self, name, place):
        self.name = name
        self.place = name

    def __repr__(self):
        return '<Nombre: ' + self.name + '-' + 'Lugar: ' + self.place + '>'

    def __str__(self):
        return self.__repr__()

    def __eq__(self, other):
        return self.name == other.name and self.place == other.place


class Solution(object):
    def __init__(self, fileName, separator, countBoundle):
        self.bundles = {}
        self.countBoundle = countBoundle
        with open(fileName, 'r') as fileSolution:
            theSolution = fileSolution.read().split('\n')
            theSolution = theSolution[1:-1]
            for anElem in theSolution:
                aRow = anElem.split(separator)
                numberOfBundle = getBundleId(aRow[0])
                author = Author(aRow[1], aRow[2])
                if self.bundles.has_key(numberOfBundle):
                    self.bundles[numberOfBundle].append(author)
                else:
                    self.bundles[numberOfBundle] = [author]

    def hasAuthor(self, anAuhorToFind):
        for aBundle, aListOfAuthors in self.bundles.iteritems():
            for anAuthor in aListOfAuthors:
                if anAuhorToFind == anAuthor:
                    return True
        return False

    def hasAuthorInBundle(self, anAuhorToFind, inBundle):
        aListOfAuthors = self.bundles[inBundle]
        for anAuthor in aListOfAuthors:
            if anAuhorToFind == anAuthor:
                return True
        return False

    def __repr__(self):
        return self.bundles.__str__()

    def __str__(self):
        return self.__repr__()


def getBundleId(aBundleName):
    if aBundleName == 'Bundle 1':
        return 1
    elif aBundleName == 'Bundle 2':
        return 2
    elif aBundleName == 'Bundle 3':
        return 3
    elif aBundleName == 'Bundle 4':
        return 4
    elif aBundleName == 'Bundle 5':
        return 5
    elif aBundleName == 'Bundle 6':
        return 6
    elif aBundleName == 'Bundle 7':
        return 7
    elif aBundleName == 'Bundle 8':
        return 8
    elif aBundleName == 'Bundle 9':
        return 9
    elif aBundleName == 'Bundle 10':
        return 10
