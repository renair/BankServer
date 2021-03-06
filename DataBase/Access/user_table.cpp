#include <QVariant>
#include <QDebug>
#include "user_table.h"

UserTable::UserTable(): _connection(Connection::getConnection())
{}

UserTable::~UserTable()
{}

bool UserTable::createNew(const User & u)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT UPID \
                         FROM user \
                         WHERE UPID='%1'").arg(u.upid())).second;
            if(is_exist.next())
            throw UserTableError("Unable to create an existing object");
    return _connection.execute(QString("INSERT INTO user(\
                                              UPID,\
                                              password,\
                                              pass_number,\
                                              name,\
                                              surname,\
                                              father_name,\
                                              phone_number) \
                            VALUES ('%1','%2','%3','%4','%5','%6','%7')").
                            arg(QString::number(u.upid()),
                                u.password(),
                                u.passNumber(),
                                u.name(),
                                u.surname(),
                                u.fatherName(),
                                QString::number(u.phoneNumber()))).first;
}

bool UserTable::update(const User & u)
{
    QSqlQuery is_exist = _connection.execute(
                QString("SELECT UPID \
                         FROM user \
                         WHERE UPID='%1'").arg(u.upid())).second;
            if(!is_exist.next())
            throw UserTableError("Unable to update non-existent object");
    return _connection.execute(
        QString("UPDATE user \
                 SET password='%2',\
                     pass_number='%3',\
                     name='%4',\
                     surname='%5',\
                     father_name='%6',\
                     phone_number='%7' \
                 WHERE UPID='%1'").
                arg(QString::number(u.upid()),
                    u.password(),
                    u.passNumber(),
                    u.name(),
                    u.surname(),
                    u.fatherName(),
                    QString::number(u.phoneNumber()))).first;
}

User UserTable::getByUpid(quint64 upid)
{
    QSqlQuery q = _connection.execute(
                QString("SELECT UPID,password,pass_number,name,surname,father_name,phone_number \
                         FROM user \
                         WHERE UPID='%1'").arg(QString::number(upid))).second;
    if(!q.next())
            throw UserTableError("The object does not exist");
    User u(q.value(0).toULongLong(),
           q.value(1).toString(),
           q.value(2).toString(),
           q.value(3).toString(),
           q.value(4).toString(),
           q.value(5).toString(),
           q.value(6).toULongLong());

    return u;
}

UserTable::UserTableError::UserTableError(const QString & reason): _reason(reason)
{}
