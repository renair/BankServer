#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <QObject>
#include <QThread>
#include <memory>

class AbstractTask;
typedef std::shared_ptr<AbstractTask> AbstractTaskHolder;

class AbstractTask : public QObject
{
Q_OBJECT
private:
    bool _isActive;
    virtual void specificStartTaskLoop() = 0;
    virtual AbstractTaskHolder specificClone() const = 0;
public:
    AbstractTask():
        _isActive(false)
    {}
    virtual ~AbstractTask(){}
    inline bool isActive() const;
    inline AbstractTaskHolder clone() const;
public slots:
    inline void startTaskLoop();
    inline void stopTaskLoop();
signals:
    void loopStoped();
};

bool AbstractTask::isActive() const
{
    return _isActive;
}

AbstractTaskHolder AbstractTask::clone() const
{
    return specificClone();
}

void AbstractTask::startTaskLoop()
{
    _isActive = true;
    specificStartTaskLoop();
    emit loopStoped();
}

void AbstractTask::stopTaskLoop()
{
    _isActive = false;
}

#endif // ABSTRACTTASK_H
