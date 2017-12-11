#ifndef APPCLOSE_H
#define APPCLOSE_H

#include <QCoreApplication>
#include <signal.h>

inline void quitApp(int)
{
    QCoreApplication::quit();
}

#endif // APPCLOSE_H
