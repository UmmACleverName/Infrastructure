#include"hdr/taskmanager.hpp"





namespace TAC{


TaskingManager::TaskingManager(): _listOfTask(), _nameOfManager("Default") {} 


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





}//EOF TAC namespace. 
