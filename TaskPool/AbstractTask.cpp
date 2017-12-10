#include <cassert>
#include "AbstractTask.h"

using namespace std;

AbstractTask::AbstractTask():
    _isActive(false),
    _isFinished(true),
    _loopThread(NULL)
{}

AbstractTask::AbstractTask(const AbstractTask&):
    AbstractTask() // constructor delegating
{}

AbstractTask::~AbstractTask()
{
    if(_loopThread != NULL)
    {
        stopTaskLoop();
        wait();
        delete _loopThread;
    }
}

bool AbstractTask::isActive() const
{
    return _isActive;
}

bool AbstractTask::isFinished() const
{
    return _isFinished;
}

AbstractTaskHolder AbstractTask::clone() const
{
    AbstractTaskHolder res = specificClone();
    res->_isActive = false;
    res->_isFinished = true;
    return res;
}

void AbstractTask::run()
{
    _isActive = true;
    _isFinished = false;
    specificStartTaskLoop();
    _isActive = false; //in case of loop will be finished by itself
    _isFinished = true;
}

void AbstractTask::startTaskLoop()
{
    if(_loopThread == NULL)
    {
        _loopThread = new thread(&AbstractTask::run, this);
        _loopThread->detach();
    }
}

void AbstractTask::stopTaskLoop()
{
    _isActive = false;
}

void AbstractTask::wait()
{
    while(!isFinished())
    {
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}
