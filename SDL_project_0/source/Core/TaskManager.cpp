﻿#include "stdafx.h"
#include "TaskManager.h"

void TaskManager::AddTask(SharedObject object, Task task)
{
    tasks.insert(std::make_pair(object,task));
}

void TaskManager::UpdateTasks(double dTime)
{
    ResolveTasks();
    for(auto& [fst, snd] : tasks)
    {
        snd.first -= dTime;
    }
}

void TaskManager::ResolveTasks()
{
    for(auto it = tasks.begin(); it!=tasks.end();)
    {
        if(it->first.use_count()<2) //checks if TaskManager is the only user of that object (object was deleted)
        {
            it = tasks.erase(it);
        }else if(it->second.first <= 0) //checks if delay of task elapsed
        {
            if(it->second.second)
                it->second.second();
            it = tasks.erase(it);
        }else
        {
            ++it;
        }
    }
}
