cmake_minimum_required(VERSION 2.8)
project(tesis-jaks_exe)
SET(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#find_package( Threads )
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost 1.54.0 COMPONENTS log log_setup thread program_options system REQUIRED )
link_libraries(${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${Boost_LIBRARIES})
find_package( Qt5 COMPONENTS Sql Gui Core Widgets REQUIRED )
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
set(tesis-jaks_source_files
        src/util/logger/simpleLogger.cpp
        src/util/algorithm/vectornorm.cpp
        src/util/algorithm/pairsToJaccardSimilarity.cpp
        src/util/algorithm/localSearch.cpp
        src/util/algorithm/localSearchBundles.cpp
        src/util/system/exception.cpp
        src/util/system/stringUtilities.cpp
        src/util/system/systemUtilities.cpp
        src/dao/dao.cpp
        src/dao/daoQt.cpp
        #src/dao/daoQt.h
        src/dao/factoryDao.cpp
        #src/dao/factoryDao.h
        src/executeSolver.cpp
        src/main.cpp
        src/problem/problemInstanceFromDataBase.cpp
        src/problem/problemInstance.cpp
        src/problem/problemInstanceFromFiles.cpp
        src/problem/snowFlake.cpp
        #src/problem/snowFlake.h
        src/problem/flake.cpp
        #src/problem/flake.h
        src/problem/factoryFlake.cpp
        #src/problem/factoryFlake.h
        src/problem/element.cpp
        #src/problem/element.h
        src/problem/elementArticle.cpp
        #src/problem/elementArticle.h
        src/problem/elementAuthor.cpp
        #src/problem/elementAuthor.h
        src/problem/elementAffiliation.cpp
        #src/problem/elementAffiliation.h
        src/problem/elementFile.cpp
        #src/problem/elementFile.h
        src/problem/factoryProblem.cpp
        #src/problem/factoryProblem.h
        src/problem/factoryElement.cpp
        #src/problem/factoryElement.h
        src/queue/priorityQueue.cpp
        src/matrix/matrixConcrete.cpp
        src/solver/algorithms/concretes/greedySolver.cpp
        src/solver/algorithms/concretes/restrictedHACWithSpecificItemSolver.cpp
        src/solver/algorithms/concretes/clusterAndPickSolver.cpp
        src/solver/algorithms/concretes/exhaustiveGreedyAnySimSOBOSolver.cpp
        src/solver/algorithms/concretes/exhaustiveGreedySumSimSOBOSolver.cpp
        src/solver/algorithms/abstract/exhaustiveSOBOSolver.cpp
        src/solver/algorithms/abstract/multiplicativeEffortProduceAndChooseSolver.cpp
        src/solver/algorithms/abstract/produceAndChooseSolver.cpp
        src/solver/algorithms/concretes/randomBOBOSolver.cpp
        src/solver/algorithms/concretes/randomSOBOSolver.cpp
        src/solver/algorithms/concretes/restrictedHACSolver.cpp
        src/solver/algorithms/concretes/restrictedEfficientHACSolver.cpp
        src/solver/algorithms/concretes/sequentialScanSolver.cpp
        src/solver/algorithms/abstract/snowflakesOneByOneSolver.cpp
        src/solver/algorithms/abstract/solver.cpp
        src/solver/factorySolver.cpp
        #src/solver/factorySolver.h
        src/cluster/clustering.cpp
        src/cluster/metisWrapper.cpp
        src/test/testingMatrix.cpp
        src/test/testSuites.cpp
        )
add_executable(tesis-jaks ${tesis-jaks_source_files})
target_link_libraries(tesis-jaks boost_log Qt5::Sql Qt5::Widgets)