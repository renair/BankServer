#ifndef USER_H
#define USER_H

#include <QString>
#include <ostream>
using namespace std;

class User
{
    friend class UserTable;
public:
    User(quint64 upid=0,
         const QString& password="",
         const QString& pass_number="",
         const QString& name="",
         const QString& surname="",
         const QString& father_name="",
         quint64 phone_number=0);
    //Selectors
    const quint64& upid() const           {return _upid;}
    const QString& passNumber() const  {return _pass_number;}
    const QString& name() const        {return _name;}
    const QString& surname() const     {return _surname;}
    const QString& fatherName() const  {return _father_name;}
    const quint64& phoneNumber() const    {return _phone_number;}
    //Selector-modifiers
    quint64& upid()            {return _upid;}
    QString& passNumber()   {return _pass_number;}
    QString& name()         {return _name;}
    QString& surname()      {return _surname;}
    QString& fatherName()   {return _father_name;}
    quint64& phoneNumber()     {return _phone_number;}
    //Work with password
    bool checkPassword(const QString& password="");
    bool setNewPass(const QString& new_pass, const QString& old_pass="");

private:
    quint64 _upid;
    QString _password;
    QString _pass_number;
    QString _name;
    QString _surname;
    QString _father_name;
    quint64 _phone_number;

    const QString& password() const {return _password;}
};

ostream& operator<<(ostream&, const User&);

#endif // USER_H
