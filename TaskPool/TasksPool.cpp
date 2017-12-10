#include <cassert>
#include "TasksPool.h"
#include "AbstractTask.h"

#include <iostream>
using namespace std;

TasksPool::TasksPool()
{}

TasksPool::~TasksPool()
{
    stopAll();
}

unsigned int TasksPool::addNewTask(const AbstractTask& newTask)
{
    AbstractTaskHolder task = newTask.clone();
    task->startTaskLoop();
    _tasksContainer.append(task);
    return _tasksContainer.size()-1; //return pseudo ID of service
}

const AbstractTask& TasksPool::getTask(unsigned int id) const
{
    if(id < (unsigned int)_tasksContainer.size())
    {
        return *(_tasksContainer.at(id));
    }
    throw TaskNotExistException(id, "Can't get task.");
}

void TasksPool::stopTask(unsigned int id)
{
    if(id < (unsigned int)_tasksContainer.size())
    {
        AbstractTaskHolder& task = _tasksContainer[id];
        task->stopTaskLoop();
        task->wait();
        assert(task.use_count() == 1);
        task.reset();
    }
}

unsigned int TasksPool::restartTask(unsigned int id)
{
    if(id < (unsigned int)_tasksContainer.size())
    {
        AbstractTaskHolder newTask = getTask(id).clone();
        stopTask(id);
        return addNewTask(*newTask);
    }
    throw TaskNotExistException(id, "Can't restart task.");
}

void TasksPool::stopAll()
{
    for(int i = 0;i < _tasksContainer.length();++i)
    {
        AbstractTaskHolder& task = _tasksContainer[i];
        if(task->isActive())
        {
            stopTask(i);
        }
    }
}


//Exception class

TasksPool::TaskNotExistException::TaskNotExistException(unsigned int id, const char* msg):
    _taskIndex(id),
    _errorMessage(msg)
{}

TasksPool::TaskNotExistException::~TaskNotExistException()
{}

void TasksPool::TaskNotExistException::examine() const
{
    cout << "There no task with id: " << index() << endl;
    cout << "Error message: " << message().c_str() << endl;
}

unsigned int TasksPool::TaskNotExistException::index() const
{
    return _taskIndex;
}

const std::string& TasksPool::TaskNotExistException::message() const
{
    return _errorMessage;
}
