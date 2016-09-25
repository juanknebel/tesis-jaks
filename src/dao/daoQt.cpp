//
// Created by zero on 24/09/16.
//

#include "daoQt.h"
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>

std::string DaoQt::getField(std::string fieldName) {
    return this->query_.value(QString::fromStdString(fieldName)).toString().toUtf8().constData();
}

std::string DaoQt::getField(int index) {
    return this->query_.value(index).toString().toUtf8().constData();
}

bool DaoQt::fetch() {
    return this->query_.next();
}

bool DaoQt::executeCustomModifiableQuery(std::string query) {
    return this->query_.exec(QString::fromStdString(query));
}

bool DaoQt::executeCustomConsultativeQuery(std::string query) {
    return this->query_.exec(QString::fromStdString(query));
}

bool DaoQt::disconnect() {
    QString connection;
    connection = this->db_.connectionName();
    this->db_.close();
    this->db_ = QSqlDatabase();
    this->db_.removeDatabase(connection);
    return this->db_.isOpen();
}

bool DaoQt::connect() {
    this->db_ = QSqlDatabase::addDatabase("QMYSQL");
    this->db_.setHostName(QString::fromStdString(this->server_));
    this->db_.setDatabaseName(QString::fromStdString(this->database_));
    this->db_.setUserName(QString::fromStdString(this->user_));
    this->db_.setPassword(QString::fromStdString(this->password_));
    this->query_ = QSqlQuery(QSqlDatabase::database(this->db_.connectionName()));
    return this->db_.open();
}

DaoQt::~DaoQt() {
    this->disconnect();
}

bool DaoQt::isConnected() const {
    return this->db_.isOpen();
}

int DaoQt::getNumberOfFields() const {
    return this->query_.record().count();
}

std::string DaoQt::getError() const {
    return this->query_.lastError().text().toUtf8().constData();
}
