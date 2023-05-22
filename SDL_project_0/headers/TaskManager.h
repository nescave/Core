#pragma once
#include "CoreTypes.h"

class TaskManager
{
    
private:
    std::unordered_multimap<SharedObject, Task> tasks;
    void ResolveTasks();
    
public:
    TaskManager() = default;
    void AddTask(SharedObject client, Task task);
    void CancelClientsTasks(SharedObject client);
    void UpdateTasks(double dTime);
};
