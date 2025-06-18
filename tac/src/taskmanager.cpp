#include"tac/hdr/taskmanager.hpp"





namespace TAC{


TaskingManager::TaskingManager(): _listOfTask(), _nameOfManager("Default") 
{
    theListOfManagers.push_back(this); 
} 

TaskingManager::TaskingManager(const TaskingManager& Manager): _listOfTask(Manager._listOfTask),
_nameOfManager(Manager._nameOfManager) 
{
    theListOfManagers.push_back(this); 
} 

TaskingManager& TaskingManager::operator=(const TaskingManager& Manager)
{
    _listOfTask = Manager._listOfTask;
    _nameOfManager = Manager._nameOfManager;
    return *this; 
}

void TaskingManager::Add(Tasking* classPtr)
{
    if(classPtr == nullptr)
        return;
    _listOfTask.push_back(classPtr); 
}

void TaskingManager::StartWork()
{
    for(auto itr : _listOfTask)
        itr->Start(); 
}

void TaskingManager::StopWork()
{
    for(auto itr : _listOfTask)
        itr->ShutDown(); 
}

TacList TaskingManager::GetTaskList()
{
    return _listOfTask; 
}

bool TaskingManager::BelongToMe(std::thread::id id)
{
    for(const auto itr : _listOfTask)
    {
        if( itr->GetID() == id)
            return true; 
    }
    return false; 
}

Tasking* TaskingManager::GetTask(std::thread::id id)
{
    for(const auto itr : _listOfTask)
    {
        if( itr->GetID() == id)
            return itr; 
    }
    return nullptr; 
}

ManagerList theListOfManagers; 


}//EOF TAC namespace. 
