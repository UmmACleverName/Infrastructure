#include<iostream>
#include"tac/hdr/tasking.hpp"
#include"tac/hdr/taskmanager.hpp" 
#include"hdr/logger.hpp" 
#include<functional>
#include<unistd.h> 

struct TestData : public TAC::Tasking::ClientData
{
    TestData()  = default;
    ~TestData() = default;
    ClientData* Clone()
    {
        ClientData* classPtr = new TestData; 
        return classPtr;  
    }

    std::string str = "Write this..\n"; 
};

class TestTask : virtual public TAC::Tasking 
{
    public:
        TestTask() {}
        ~TestTask() {}
        void ShutDown() override
        {
            Tasking::ShutDown();
            std::cout << "Shutting down\n"; 
        }
    private:
        void initialize() override
        {
            std::cout << "TestTask\n"; 
        }
}; 


void TestBody(TAC::Tasking* self)
{
    TestData* ptr = (self->GetClientData() == nullptr ? nullptr : (TestData*)(self->GetClientData())); 

    while(!(self->IsDone()))
    {
        if(ptr != nullptr){ 
            LOGGER::Log("Running in task\n"); 
        }
    }//EOF Tasking Loop. 
}

class TestManager : virtual public TAC::TaskingManager
{
    public:
        TestManager() = default;
        ~TestManager() = default; 
        void Construct()
        {
            TestData T; 
            for(unsigned int i = 1; i <= 3; ++i)
            {
                TestTask* tac = new TestTask;
                Add(tac); 
                tac->Construct("Test task " + std::to_string(i), "testlog_" + std::to_string(i) + ".log", T, TestBody);
            }
        };

};



int main()
{
    TestManager manager;
    manager.Construct();
    manager.StartWork(); 
    sleep(2);
    manager.StopWork(); 
    LOGGER::Log(" Running in main\n"); 
    return EXIT_SUCCESS; 
}
