#ifndef __TASKING_MANAGER_HPP__
#define __TASKING_MANAGER_HPP__
#include<string>
#include<vector> 
#include"hdr/tasking.hpp" 


namespace TAC{

using TacList = std::vector<Tasking*>; //TODO: Should make this a map with key as the tac id. This will allow function BelongToME efficient.

class TaskingManager
{
    public:
        TaskingManager();
        TaskingManager(const TaskingManager&);
        //TaskingManager(TaskingManager&&);
        TaskingManager& operator=(const TaskingManager&);
        //TaskingManager& operator=(TaskingManager&&);
        virtual ~TaskingManager() = default;
        
        virtual void construct() = 0; 
        void StartWork(); 
        void StopWork();

        TacList  GetTaskList();
        Tasking* GetTask(std::thread::id);
        bool BelongToMe(std::thread::id); 

    protected:
        void Add(Tasking*);
    private:
        TacList     _listOfTask;
        std::string _nameOfManager; 

};//EOF TaskingManager 




using ManagerList = std::vector<TaskingManager*>; //TODO: Should make this a map with key as the manager name?

extern ManagerList theListOfManagers; 

}//EOF TAC namespace. 




#endif 
