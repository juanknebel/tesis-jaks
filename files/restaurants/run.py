import commands

cmdGamma01 = './tesis-jaks -f BoboProp01.jaks'
cmdGamma05 = './tesis-jaks -f BoboProp05.jaks'
cmdGamma09 = './tesis-jaks -f BoboProp09.jaks'
cmdGamma01BS = './tesis-jaks -f BoboSimple01.jaks'
cmdGamma05BS = './tesis-jaks -f BoboSimple05.jaks'
cmdGamma09BS = './tesis-jaks -f BoboSimple09.jaks'
cmdGamma01EHP = './tesis-jaks -f EffHacProp01.jaks'
cmdGamma05EHP = './tesis-jaks -f EffHacProp05.jaks'
cmdGamma09EHP = './tesis-jaks -f EffHacProp09.jaks'
cmdGamma01EAS = './tesis-jaks -f EffHacSimple01.jaks'
cmdGamma05EAS = './tesis-jaks -f EffHacSimple05.jaks'
cmdGamma09EAS = './tesis-jaks -f EffHacSimple09.jaks'
cmdGamma01HS = './tesis-jaks -f HacSimple01.jaks'
cmdGamma05HS = './tesis-jaks -f HacSimple05.jaks'
cmdGamma09HS = './tesis-jaks -f HacSimple09.jaks'
cmdGenerateData = 'python ./generateCSVForTesis.py -c '

fileName = 'toBoxPlot.csv'
fileNameTabu = 'toBoxPlotTabu.csv'
fileNameBS = 'toBoxPlotBS.csv'
fileNameTabuBS = 'toBoxPlotTabuBS.csv'
fileNameEHP = 'toBoxPlotEHP.csv'
fileNameTabuEHP = 'toBoxPlotTabuEHP.csv'
fileNameEAS = 'toBoxPlotEAS.csv'
fileNameTabuEAS = 'toBoxPlotTabuEAS.csv'
fileNameHS = 'toBoxPlotHS.csv'
fileNameTabuHS = 'toBoxPlotTabuHS.csv'

cities = [999,76,48,24,99,63,31,119,85,97,7,9,98,105,59,29,88,51,34,17,107,116,6,53,94,68,26,100,11,70,47,18,54,71,83]
separator = "\t"
endOfLine = "\n"
header = '0.1' + separator + '0.5' + separator + '0.9' + endOfLine

def executeTesis(cmd, outputFile, outputFileTabu):
	output = commands.getoutput(str(cmd))
	print (output)
	startFirstSolution = output.find('Primera solucion: ')
	startSecodSolution = output.find('Segunda solucion: ')
	firstSolution = output[startFirstSolution:startSecodSolution - 1]
	secondSolution = output[startSecodSolution:len(output)]
	firstSolution = firstSolution[firstSolution.find(': ') + 2:len(firstSolution)]
	secondSolution = secondSolution[secondSolution.find(': ') + 2:len(secondSolution)]
	outputFile.write(firstSolution)
	outputFileTabu.write(secondSolution)

def execute(cmdGamma01, cmdGamma05, cmdGamma09, fileResults, fileResultsTabu):
	executeTesis(cmdGamma01, fileResults, fileResultsTabu)
	fileResults.write(separator)
	fileResultsTabu.write(separator)
	
	executeTesis(cmdGamma05, fileResults, fileResultsTabu)
	fileResults.write(separator)
	fileResultsTabu.write(separator)
	
	executeTesis(cmdGamma09, fileResults, fileResultsTabu)
	fileResults.write(separator)
	fileResultsTabu.write(separator)
	
	fileResults.write(endOfLine)
	fileResultsTabu.write(endOfLine)


fileResults = open(fileName,"w")
fileResultsTabu = open(fileNameTabu,"w")
fileResultsBS = open(fileNameBS,"w")
fileResultsTabuBS = open(fileNameTabuBS,"w")
fileResultsEHP = open(fileNameEHP,"w")
fileResultsTabuEHP = open(fileNameTabuEHP,"w")
fileResultsEAS = open(fileNameEAS,"w")
fileResultsTabuEAS = open(fileNameTabuEAS,"w")
fileResultsHS = open(fileNameHS,"w")
fileResultsTabuHS = open(fileNameTabuHS,"w")


fileResults.write(header)
fileResultsTabu.write(header)
fileResultsBS.write(header)
fileResultsTabuBS.write(header)
fileResultsEHP.write(header)
fileResultsTabuEHP.write(header)
fileResultsEAS.write(header)
fileResultsTabuEAS.write(header)
fileResultsHS.write(header)
fileResultsTabuHS.write(header)

for aCity in cities:
	print ('Procesando la ciudad: ' + str(aCity))
	garbageOutput = commands.getoutput(str(cmdGenerateData + str(aCity)))
	#execute(cmdGamma01, cmdGamma05, cmdGamma09, fileResults, fileResultsTabu)
	execute(cmdGamma01BS, cmdGamma05BS, cmdGamma09BS, fileResultsBS, fileResultsTabuBS)
	execute(cmdGamma01EHP, cmdGamma05EHP, cmdGamma09EHP, fileResultsEHP, fileResultsTabuEHP)
	execute(cmdGamma01EAS, cmdGamma05EAS, cmdGamma09EAS, fileResultsEAS, fileResultsTabuEAS)
	execute(cmdGamma01HS, cmdGamma05HS, cmdGamma09HS, fileResultsHS, fileResultsTabuHS)

fileResults.close()
fileResultsTabu.close()
fileResultsBS.close()
fileResultsTabuBS.close()
fileResultsEHP.close()
fileResultsTabuEHP.close()
fileResultsEAS.close()
fileResultsTabuEAS.close()
fileResultsHS.close()
fileResultsTabuHS.close()
