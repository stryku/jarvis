#ifndef _WORKERSMAP_HPP_
#define _WORKERSMAP_HPP_

#include <ConstMap.hpp>
#include <WorkersFactory.hpp>

class WorkersMap : public ConstMap<TaskType, std::shared_ptr<Worker>>
{
private:

    void addWorker( TaskType type );
    void init();

public:
    WorkersMap() { init(); }
    ~WorkersMap() {}
};

#endif // _WORKERSMAP_HPP_