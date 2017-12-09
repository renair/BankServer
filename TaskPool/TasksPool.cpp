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
    QThread* thread = new QThread();
    task->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), task.get(), SLOT(startTaskLoop()));
    QObject::connect(task.get(), SIGNAL(loopStoped()), thread, SLOT(quit()), Qt::QueuedConnection);
    //QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
    _tasksContainer.append(QPair<QThread*, AbstractTaskHolder>(thread, task));
    return _tasksContainer.size()-1; //return pseudo ID of service
}

const AbstractTask& TasksPool::getTask(unsigned int id) const
{
    return *(_tasksContainer.at(id).second);
}

void TasksPool::stopTask(unsigned int id)
{
    if(id < (unsigned int)_tasksContainer.size())
    {
        QPair<QThread*, AbstractTaskHolder>& pair = _tasksContainer[id]; //TODO check id existings
        pair.second->stopTaskLoop();
        pair.first->wait();
        delete pair.first;
        assert(pair.second.use_count() == 1);
        pair.second.reset(); //will delete object if there is 1 ref
        pair.first = NULL;
        pair.second = NULL;
    }
}

unsigned int TasksPool::restartTask(unsigned int id)
{
    AbstractTaskHolder newTask = getTask(id).clone();
    stopTask(id);
    return addNewTask(*newTask);
}

void TasksPool::stopAll()
{
    for(int i = 0;i < _tasksContainer.length();++i)
    {
        QPair<QThread*, AbstractTaskHolder>& pair = _tasksContainer[i];
        if(pair.first != NULL && pair.second != NULL)
        {
            stopTask(i);
        }
    }
}
