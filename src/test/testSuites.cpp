/*
 * testSuites.cpp
 *
 *  Created on: 25/08/2013
 *      Author: zero
 */

#include <iostream>
#include "testSuites.h"
#include "testingMatrix.h"
#include "../dao/factoryDao.h"
#include "../util/system/stringUtilities.h"

MatrixConcrete giveMeMatrix2x2(double a, double b, double c, double d)
{
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,a);
	matrix.set(0,1,b);
	matrix.set(1,0,c);
	matrix.set(1,1,d);
	return matrix;
}

MatrixConcrete giveMeMatrix2x2()
{
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(1,0,3.0);
	matrix.set(1,1,4.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix2x2()
{
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(1,0,3.0);
	matrix.set(1,1,2.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix2x2With0InDiagonal()
{
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,0.0);
	matrix.set(0,1,2.0);
	matrix.set(1,0,3.0);
	matrix.set(1,1,0.0);
	return matrix;
}

MatrixConcrete giveMeMatrix3x3()
{
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,4.0);
	matrix.set(1,1,5.0);
	matrix.set(1,2,6.0);
	matrix.set(2,0,7.0);
	matrix.set(2,1,8.0);
	matrix.set(2,2,9.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix3x3()
{
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,2.0);
	matrix.set(1,1,1.0);
	matrix.set(1,2,2.0);
	matrix.set(2,0,3.0);
	matrix.set(2,1,2.0);
	matrix.set(2,2,1.0);
	return matrix;
}

MatrixConcrete giveMeMatrix3x3With0InDiagonal()
{
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,0.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,4.0);
	matrix.set(1,1,0.0);
	matrix.set(1,2,6.0);
	matrix.set(2,0,7.0);
	matrix.set(2,1,8.0);
	matrix.set(2,2,0.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix3x3With0InDiagonal()
{
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,0.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,2.0);
	matrix.set(1,1,0.0);
	matrix.set(1,2,2.0);
	matrix.set(2,0,3.0);
	matrix.set(2,1,2.0);
	matrix.set(2,2,0.0);
	return matrix;
}

void testDBGeneric(Dao& dao, std::string tableName)
{
	if (dao.isConnected()) {
		bool hasresult = dao.executeCustomConsultativeQuery("select * from " + tableName);

		if (hasresult) {
			int numOffields = dao.getNumberOfFields();

			while(dao.fetch()) {
				for (int i=0; i<numOffields; ++i) {
					if (!(dao.getField(i)).empty()) {
						std::cout<<dao.getField(i);
					}

					else {
						std::cout<<"NULL";
					}

					if (i!=numOffields-1) {
						std::cout<<"|";
					}
				}

				std::cout<<std::endl;
			}
		}

		else {
			std::cerr<<"Error al obtener resutlados"<<std::endl;
			std::cerr<<dao.getError()<<std::endl;
		}
	}

	else {
		std::cerr<<"Error no esta conectado a ninguna base de datos"<<std::endl;
	}
}

void testDB1()
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("TEST");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	bool connect = dao.connect();
	std::cout<<dao.showConnection();

	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao.getError()<<std::endl;
	}

	else {
		if (dao.executeCustomConsultativeQuery("select count(*) from ARTICLES")) {
			if (dao.fetch()) {
				int count = convertToInt(dao.getField(1));
				std::cout<<"La cantidad que hay es de: "<<count<<std::endl;
			}
		}

		testDBGeneric(dao,"ARTICLES");
	}
}

void testDBCustomQuery()
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("TEST");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	bool connect = dao.connect();

	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao.getError()<<std::endl;
	}

	else {
		std::cout<<dao.showConnection();

		if (dao.isConnected()) {
			bool wasOk = dao.executeCustomConsultativeQuery("SELECT * from AUTHORS");

			if (wasOk) {
				std::cout<<"Ejecuto bien"<<std::endl;
				int numOffields = dao.getNumberOfFields();
				bool hasresult = false;

				while(dao.fetch()) {
					hasresult = true;
					for (int i=0; i<numOffields; ++i) {
						if (!(dao.getField(i)).empty()) {
							std::cout<<dao.getField(i);
						}

						else {
							std::cout<<"NULL";
						}

						if (i!=numOffields-1) {
							std::cout<<"|";
						}
					}
					std::cout<<std::endl;
				}

				if (hasresult) {
					std::cout<<"Encontró alguna fila que cumple con la condición"<<std::endl;
				}

				else {
					std::cout<<"No encontró ninguna fila que cumple con la condición"<<std::endl;
				}
			}

			else {
				std::cerr<<"Error al obtener resutlados"<<std::endl;
				std::cerr<<dao.getError()<<std::endl;
			}
		}
		else {
			std::cerr<<"Error no esta conectado a ninguna base de datos"<<std::endl;
		}
	}
}

void testDBInsertCustom()
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("TEST");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	bool connect = dao.connect();

	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao.getError()<<std::endl;
	}

	else {
		std::cout<<dao.showConnection();

		if (dao.isConnected()) {
			bool isOk = dao.executeCustomModifiableQuery("insert into tablaPrueba values (3,5,\'prueba tres\')");

			if (!isOk) {
				std::cerr<<dao.getError()<<std::endl;
			}
		}
	}
}

void testDBInsertPartial()
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("TEST");
	Dao& dao = theFactoryDao.get()->getDaoInstance();
	bool connect = dao.connect();

	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao.getError()<<std::endl;
	}

	else {
		std::cout<<dao.showConnection();

		if (dao.isConnected()) {
			bool isOk = dao.executeCustomModifiableQuery("insert into tablaPrueba set id=6, descripcion=\'prueba tesis\',valor=3");

			if (!isOk) {
				std::cerr<<dao.getError()<<std::endl;
			}
		}
	}
}

void testDB()
{
	std::shared_ptr<FactoryDao> theFactoryDao = FactoryDao::getInstance("TEST");
	Dao& dao = theFactoryDao.get()->getDaoInstance();


	std::shared_ptr<FactoryDao> theFactoryDao2 = FactoryDao::getInstance("TEST");
	Dao& dao2 = theFactoryDao.get()->getDaoInstance();


	testDBCustomQuery();
}

void testMatrix()
{
	std::cout << "Test MatrixWrapper y MatrixConcrete" << std::endl;
	MatrixConcrete matrix = giveMeMatrix2x2(1.0,2.0,3.0,4.0);

	TestingMatrix testMatrix = TestingMatrix();
	testMatrix.setMatrix(&matrix);

	MatrixConcrete matrixToCompare = giveMeMatrix2x2(1.0,2.0,3.0,4.0);

	testMatrix.testRows(2);
	testMatrix.testCols(2);
	testMatrix.testMinValue(1.0);
	testMatrix.testMaxValue(4.0);
	testMatrix.testGet(1,0,3.0);

	testMatrix.testSet(1,1,66.6,66.6);

	matrixToCompare.set(0,0,2.0);
	matrixToCompare.set(0,1,4.0);
	matrixToCompare.set(1,0,6.0);

	matrixToCompare.set(1,1,133.2);
	testMatrix.getMatrix()->showMe();
	matrixToCompare.showMe();
	testMatrix.testScalarMultiply(2.0, &matrixToCompare);

	matrixToCompare.set(1,1,8.0);
	testMatrix.getMatrix()->showMe();
	matrixToCompare.showMe();
	testMatrix.testScalarMultiply(2.0, &matrixToCompare);

	MatrixConcrete anotherMatrix = giveMeMatrix2x2(0.0,0.0,0.0,0.0);
	testMatrix.setMatrix(&anotherMatrix);

	testMatrix.getMatrix()->showMe();
	testMatrix.testCountNonZeros(0);
	testMatrix.getMatrix()->showMe();
	testMatrix.testCountNonZeros(2);
}
