#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include <QMap>
#include <QMutex>

class User;

class UserService : public QObject
{
    Q_OBJECT
private:
    QMap<QString, const User*> _connectedUsers; //authorization signature -> connected user
    QMutex _mutex;
public:
    UserService();
    ~UserService(){}
    void registerNewUser(const User*);
    bool isUserConnected(long);
signals:
    void userDisconnected(long);
};

#endif // USERSERVICE_H
