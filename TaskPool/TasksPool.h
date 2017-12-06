#ifndef TASKSPOOL_H
#define TASKSPOOL_H

#include <QVector>
#include "AbstractTask.h"

class TasksPool
{
private:
    QVector<AbstractTaskHolder> _tasksContainer;
    TasksPool(const TasksPool&) = delete;
    TasksPool& operator=(const TasksPool&) = delete;
public:
    class TaskNotExistException;
    TasksPool();
    virtual ~TasksPool();
    unsigned int addNewTask(const AbstractTask&);
    const AbstractTask& getTask(unsigned int) const;
    void stopTask(unsigned int);
    unsigned int restartTask(unsigned int);
    void stopAll();
};

class TasksPool::TaskNotExistException
{
private:
    const unsigned int _taskIndex;
    const std::string _errorMessage;
public:
    TaskNotExistException(unsigned int,const char*);
    ~TaskNotExistException();
    void examine() const;
    unsigned int index() const;
    const std::string& message() const;
};

#endif // TASKSPOOL_H
