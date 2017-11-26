#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include "QSharedPointer"

class AbstractTask;
typedef QSharedPointer<AbstractTask> AbstractTaskHolder;

class AbstractTask : public QObject
{
Q_OBJECT
private:
    bool _isActive;
    virtual void doSpecificTaskLoop() = 0;
public:
    virtual ~AbstractTask(){}
    inline bool isActive() const;
public slots:
    inline void doTaskLoop();
    inline void stopTaskLoop();
};

bool AbstractTask::isActive() const
{
    return _isActive;
}

void AbstractTask::doTaskLoop()
{
    doSpecificTaskLoop();
}

void AbstractTask::stopTaskLoop()
{
    _isActive = false;
}

#endif // ABSTRACTTASK_H
