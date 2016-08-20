cmake_minimum_required(VERSION 2.8)
project(tesis-jaks_exe)
SET(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#find_package( Threads )
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost 1.54.0 COMPONENTS log log_setup thread system REQUIRED )
link_libraries(${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${Boost_LIBRARIES})
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(tesis-jaks_source_files
        src/util/logger/simpleLogger.cpp
        src/util/configurator/configuratorToDataBase.cpp
        src/util/configurator/configurator.cpp
        src/util/configurator/factoryConfigurator.cpp
        src/util/configurator/configurationJaks.cpp
        src/util/writer/factoryWriter.cpp
        src/util/writer/writerSolution.cpp
        src/util/writer/writerSolutionAffiliations.cpp
        src/util/writer/writerSolutionAuthors.cpp
        src/util/writer/writerSolutionArticles.cpp
        src/util/identificator/factoryIdentificationGenerator.cpp
        src/util/identificator/identificationGeneretor.cpp
        src/util/identificator/identificationGeneretorAffiliation.cpp
        src/util/identificator/identificationGeneretorAuthor.cpp
        src/util/identificator/identificationGeneretorArticle.cpp
        src/util/identificator/id2Str.cpp
        src/util/algorithm/vectornorm.cpp
        src/util/algorithm/pairsToJaccardSimilarity.cpp
        src/util/algorithm/localSearch.cpp
        src/util/algorithm/localSearchBundles.cpp
        src/util/system/exception.cpp
        src/util/system/stringUtilities.cpp
        src/util/system/systemUtilities.cpp
        src/dao/daoMySql.cpp
        src/dao/dao.cpp
        src/executeSolver.cpp
        src/main.cpp
        src/problem/factoryProblem.cpp
        src/problem/problemInstanceFromDataBase.cpp
        src/problem/problemInstance.cpp
        src/problem/problemInstanceFromFiles.cpp
        src/problem/snowFlake.cpp
        src/queue/priorityQueue.cpp
        src/matrix/matrixConcrete.cpp
        src/solver/factorySolver.cpp
        src/solver/greedySolver.cpp
        src/solver/restrictedHACWithSpecificItemSolver.cpp
        src/solver/clusterAndPickSolver.cpp
        src/solver/exhaustiveGreedyAnySimSOBOSolver.cpp
        src/solver/exhaustiveGreedySumSimSOBOSolver.cpp
        src/solver/exhaustiveSOBOSolver.cpp
        src/solver/multiplicativeEffortProduceAndChooseSolver.cpp
        src/solver/produceAndChooseSolver.cpp
        src/solver/randomBOBOSolver.cpp
        src/solver/randomSOBOSolver.cpp
        src/solver/restrictedHACSolver.cpp
        src/solver/restrictedEfficientHACSolver.cpp
        src/solver/sequentialScanSolver.cpp
        src/solver/snowflakesOneByOneSolver.cpp
        src/solver/solver.cpp
        src/cluster/clustering.cpp
        src/cluster/metisWrapper.cpp
        src/test/testingClusterAndPickSolver.cpp
        src/test/testingClustering.cpp
        src/test/testingMatrix.cpp
        src/test/testingMetisWrapper.cpp
        src/test/testingProblemInstance.cpp
        src/test/testingProblemInstanceFromFiles.cpp
        src/test/testSuites.cpp
        src/util/writer/writterSolutionFile.cpp)
add_executable(tesis-jaks ${tesis-jaks_source_files})
target_link_libraries(tesis-jaks boost_log mysqlcppconn)