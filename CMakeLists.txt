cmake_minimum_required(VERSION 2.8)

project(tesis-jaks_exe)

set(tesis-jaks_source_files src/test/testingClusterAndPickSolver.cpp src/test/testingClustering.cpp
src/main.cpp
src/matrixConcrete.cpp
src/problemInstance.cpp
src/problemInstanceFromFiles.cpp
src/snowFlake.cpp
src/test/testingMatrix.cpp
src/test/testingMetisWrapper.cpp
src/test/testingProblemInstance.cpp
src/test/testingProblemInstanceFromFiles.cpp
src/test/testSuites.cpp
src/util/id2Str.cpp
src/util/Logger.cpp
src/util/pairsToJaccardSimilarity.cpp
src/util/stringUtilities.cpp
src/util/systemUtilities.cpp
src/solver/clusterAndPickSolver.cpp
src/solver/exhaustiveGreedyAnySimSOBOSolver.cpp
src/solver/exhaustiveGreedySumSimSOBOSolver.cpp
src/solver/exhaustiveSOBOSolver.cpp
src/solver/multiplicativeEffortProduceAndChooseSolver.cpp
src/solver/produceAndChooseSolver.cpp
src/solver/randomBOBOSolver.cpp
src/solver/randomSOBOSolver.cpp
src/solver/restrictedHACSolver.cpp
src/solver/sequentialScanSolver.cpp
src/solver/snowflakesOneByOneSolver.cpp
src/solver/solver.cpp
src/cluster/clustering.cpp
src/cluster/metisWrapper.cpp
)

add_executable(tesis-jaks ${tesis-jaks_source_files})
