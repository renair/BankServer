#include "TasksPool.h"
#include "AbstractTask.h"

TasksPool::TasksPool()
{}

TasksPool::~TasksPool()
{
    stopAll();
}

unsigned int TasksPool::addNewTask(AbstractTaskHolder task)
{
    QThread* thread = new QThread();
    task->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), &*task, SLOT(doTaskLoop()));
    thread->start();
    _tasksContainer.append(QPair<QThread*, AbstractTaskHolder>(thread, task));
    return _tasksContainer.size();
}

AbstractTaskHolder TasksPool::getTask(unsigned int id) const
{
    return _tasksContainer.at(id).second;
}

void TasksPool::stopTask(unsigned int id)
{
    QPair<QThread*, AbstractTaskHolder>& pair = _tasksContainer[id]; //TODO check id existings
    pair.second->stopTaskLoop(); //TODO clean resources after stoping
    pair.first->wait();
    delete pair.first;
    pair.first = NULL;
}

unsigned int TasksPool::restartTask(unsigned int id)
{
    //TODO implement
    return 0;
}

void TasksPool::stopAll()
{
    for(int i = 0;i < _tasksContainer.length();++i)
    {
        QPair<QThread*, AbstractTaskHolder>& pair = _tasksContainer[i]; //TODO check id existings
        pair.second->stopTaskLoop(); //TODO clean resources
        pair.first->wait();
        delete pair.first;
        pair.first = NULL;
    }
}
