#ifndef __TASKING_MANAGER_HPP__
#define __TASKING_MANAGER_HPP__
#include<string>
#include<vector> 
#include"hdr/tasking.hpp" 


namespace TAC{

class TaskingManager
{
    public:
        TaskingManager();
        //TaskingManager(const TaskingManager&);
        //TaskingManager(TaskingManager&&);
        //TaskingManager& operator=(const TaskingManager&);
        //TaskingManager& operator=(TaskingManager&&);
        virtual ~TaskingManager() = default;
        
        virtual void construct() = 0; 
        void StartWork(); 
        void StopWork();
    protected:
        void Add(Tasking*);
    private:
        std::vector<Tasking*> _listOfTask;
        std::string           _nameOfManager; 

};//EOF TaskingManager 





}//EOF TAC namespace. 








#endif 
