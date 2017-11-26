#ifndef TASKSPOOL_H
#define TASKSPOOL_H

#include <QThread>
#include <QPair>
#include <QVector>
#include "AbstractTask.h"

class TasksPool
{
private:
    QVector<QPair<QThread*, AbstractTaskHolder>> _tasksContainer;
    TasksPool(const TasksPool&) = delete;
    TasksPool& operator=(const TasksPool&) = delete;
public:
    TasksPool();
    ~TasksPool();
    unsigned int addNewTask(AbstractTaskHolder);
    AbstractTaskHolder getTask(unsigned int) const;
    void stopTask(unsigned int);
    unsigned int restartTask(unsigned int);
    void stopAll();
};

#endif // TASKSPOOL_H
