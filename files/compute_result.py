#!/usr/bin/env python

import sys

class Costs:
  theCosts = {}
  
  def __init__(self, aPairCollection, separator):
    self.theCosts = {}
    for elem in aPairCollection:
      if (elem != ''):
	aPair = elem.split(separator)
	self.theCosts[aPair[0]] = float(aPair[1])
      else:
	continue
  
  def get(self, key):
    return self.theCosts[key]
    
class Solution:
  thSeolution = {}
  
  def __init__(self, aBundleCollection, separator):
    self.theSolution = {}
    i = 1
    for elem in aBundleCollection:
      if (elem != ''):
	listOfElements = elem.split()
	self.theSolution[i] = listOfElements
	i = i + 1
      else:
	continue
  
  def get(self, key):
    return self.theSolution[key]
  
  def getAllKeys(self):
    return self.theSolution.keys()
  
  def sumAllCosts(self, key, theCosts):
    total = 0.0
    for elem in self.theSolution[key]:
      total = total + theCosts.get(elem)
    return total

def readArguments(argv):
  error = 'Modo de uso compute_resut.py -c <archivo_costos.csv> -s <archivo_solucion.csv>'
  canExecute = True
  costFileName = ''
  solutionFileName = ''
  if (len(argv) != 5):
    print error
    canExecute = False
  elif (argv[1] != '-c'):
    print error
    canExecute = False
  elif (argv[3] != '-s'):
    print error
    canExecute = False
  else:
    costFileName = argv[2]
    solutionFileName = argv[4]
  return [canExecute, costFileName, solutionFileName]

def main():
  result = readArguments(sys.argv)
  if (result[0]):
    costFileName = result[1]
    solutionFileName = result[2]

    theCosts = Costs(open(costFileName).read().split('\n'), '\t')
    theSolution = Solution(open(solutionFileName).read().split('\n'), '\t')

    for key in theSolution.getAllKeys():
      print ("Costo para la solucion " + str(key) + ": " + str(theSolution.sumAllCosts(key, theCosts)))
  
if __name__ == '__main__':
    main()
