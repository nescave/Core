#pragma once
#include "CoreTypes.h"

class TaskManager
{
public:
    TaskManager() = default;
    void AddTask(SharedObject object, Task task);
    void UpdateTasks(double dTime);
    
private:
    std::unordered_multimap<SharedObject, Task> tasks;
    void ResolveTasks();
};
