#ifndef __TASKING_MANAGER_HPP__
#define __TASKING_MANAGER_HPP__
#include<string> 
#include"hdr/tasking.hpp" 


namespace TAC{

struct BasicManagerInfo
{
    unsigned int maxNumberOfTask;
    std::string  nameOfManager;
    //TODO: Add tasking info. 
}; 






class TaskingManager
{
    public:
        TaskingManager();
        TaskingManager(const TaskingManager&);
        TaskingManager(TaskingManager&&);
        TaskingManager& operator=(const TaskingManager&);
        TaskingManager& operator=(TaskingManager&&);
        void construct(BasicManagerInfo&); 
    public:
        virtual ~TaskingManager();
    private:
        virtual void construct() = 0; 
        
        






};//EOF TaskingManager 





}//EOF TAC namespace. 








#endif 
