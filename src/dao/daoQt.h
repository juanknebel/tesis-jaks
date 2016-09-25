//
// Created by zero on 24/09/16.
//

#ifndef TESIS_JAKS_EXE_DAOQT_H
#define TESIS_JAKS_EXE_DAOQT_H

#include "dao.h"
#include <string>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DaoQt : public Dao {
private:
    QSqlDatabase db_;
    QSqlQuery query_;

public:
    DaoQt(std::string database, std::string user, std::string password, std::string server) : Dao(database, user, password, server) {}
    DaoQt(const DaoQt& dao) : Dao(dao.database_, dao.user_, dao.password_, dao.server_) {}
    ~DaoQt();

    bool connect();
    bool disconnect();

    bool executeCustomConsultativeQuery(std::string query);
    bool executeCustomModifiableQuery(std::string query);
    bool fetch();
    std::string getField(int index);
    std::string getField(std::string fieldName);
    bool isConnected() const;
    int getNumberOfFields() const;
    virtual std::string getError() const;
};


#endif //TESIS_JAKS_EXE_DAOQT_H
