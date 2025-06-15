#include"hdr/logger.hpp" 

#include<iostream>
#include"hdr/taskmanager.hpp" 






namespace LOGGER{


void Log(std::string details, TAC::Tasking* task)
{
    if(task != nullptr)
    {
        if(task->DebugOn())
        {
            task->write(details); 
        }
    }
    else //Try to find the task info. 
    {
        std::thread::id taskID = std::this_thread::get_id();
        for(const auto itr : TAC::theListOfManagers)
        {
            if(itr->BelongToMe(taskID))
            {
                itr->GetTask(taskID)->write(details); 
                return;
            }
        }
    }
};












};//EOF Logger namespace. 
