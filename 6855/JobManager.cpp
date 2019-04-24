#include "JobManager.h"
#include <algorithm>

using std::swap;

JobManager *JobManager::instance = nullptr;
JobManager *JobManager::getInstance()
{
    if (instance == nullptr)
        instance = new JobManager();
    return instance;
}
bool JobManager::deleteInstance()
{
    if (instance == nullptr)
        return false;
    instance->clear();
    delete instance;
    instance = nullptr;
    return true;
}

void JobManager::addJob(int priority)
{
    if (jobFrontPointer == nullptr)
    {
        jobFrontPointer = new Job(priority);
    }
    else
    {
        auto ptr = jobFrontPointer;
        while (ptr != nullptr && ptr->getNext() != nullptr)
        {
            ptr = ptr->getNext();
        }
        ptr->setNext(new Job(priority));
    }
}
void JobManager::finishOneJob()
{
    auto ptr = jobFrontPointer;
    jobFrontPointer = ptr->getNext();
    delete ptr;
}
void JobManager::sortJob()
{
    for (auto i = jobFrontPointer; i != nullptr; i = i->getNext())
    {
        for (auto j = i->getNext(); j != nullptr; j = j->getNext())
        {
            if (i->getPriority() < j->getPriority() ||
                (i->getPriority() == j->getPriority() && i->getId() > j->getId()))
            {
                auto p = i->getPriority();
                auto d = i->getId();
                i->setPriority(j->getPriority());
                i->setId(j->getId());
                j->setPriority(p);
                j->setId(d);
            }
        }
    }
}
void JobManager::printJob()
{
    auto ptr = jobFrontPointer;
    while (ptr != nullptr && ptr->getNext() != nullptr)
    {
        cout << ptr->toString() << "->";
        ptr = ptr->getNext();
    }
    if (ptr != nullptr)
        cout << ptr->toString();
    else
        cout << "empty!";
    cout << endl;
}
int JobManager::getNumOfJob()
{
    int count = 0;
    auto ptr = jobFrontPointer;
    while (ptr != nullptr)
    {
        ptr = ptr->getNext();
        count++;
    }
    return count;
}
void JobManager::clear()
{
    auto ptr = jobFrontPointer;
    while (ptr != nullptr)
    {
        auto tmp = ptr;
        ptr = ptr->getNext();
        delete tmp;
    }
    jobFrontPointer = nullptr;
}

JobManager::~JobManager()
{
    clear();
}
JobManager::JobManager() : jobFrontPointer(nullptr)
{
}