#include<iostream>
#include"hdr/tasking.hpp"
#include"hdr/taskmanager.hpp" 
#include"hdr/tac.hpp"
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
        if(ptr != nullptr) self->write(ptr->str + self->getName()); 
    }//EOF Tasking Loop. 
}

class TestManager : virtual public TAC::TaskingManager
{
    public:
        TestManager() = default;
        ~TestManager() = default; 
        void construct()
        {
            TestData T; 
            for(unsigned int i = 1; i <= 3; ++i)
            {
                TestTask* tac = new TestTask;
                tac->construct("Test task " + std::to_string(i), "testlog_" + std::to_string(i) + ".log", T, TestBody);
                Add(tac); 
            }
        };

};



int main()
{
    TestManager manager;
    manager.construct();
    manager.StartWork(); 
    sleep(10);
    manager.StopWork();  
    return EXIT_SUCCESS; 
}
