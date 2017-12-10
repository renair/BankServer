#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <QObject>
#include <thread>
#include <chrono>
#include <memory>

class AbstractTask;
typedef std::shared_ptr<AbstractTask> AbstractTaskHolder;

class AbstractTask
{
private:
    bool _isActive; //is process executing now
    bool _isFinished; //is process fully stoped
    std::thread* _loopThread;
    virtual void specificStartTaskLoop() = 0;
    virtual AbstractTaskHolder specificClone() const = 0;
    AbstractTask& operator=(const AbstractTask&) = delete;
    void run();
public:
    AbstractTask();
    AbstractTask(const AbstractTask&);
    virtual ~AbstractTask();
    bool isActive() const;
    bool isFinished() const;
    AbstractTaskHolder clone() const;
    void startTaskLoop();
    void stopTaskLoop();
    void wait();
};

#endif // ABSTRACTTASK_H
