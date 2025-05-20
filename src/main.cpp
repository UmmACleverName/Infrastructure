#include<iostream>
#include"hdr/tasking.hpp"
#include"hdr/taskmanager.hpp" 
#include"hdr/tac.hpp"
#include<functional>

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
        void shutDown() override
        {
            Tasking::shutDown();
            std::cout << "Shutting down\n"; 
        }
    private:
        void initialize() override
        {
            std::cout << "TestTask\n"; 
        }
}; 


void run(TAC::Tac& tac)
{
    for(int i = 0; i < 5; i++)
    {
        std::cout << tac.GetName() << std::endl;
    }
}

void TestBody(TAC::Tasking* self, TAC::Tasking::ClientData* classPtr)
{
    TestData* ptr = (classPtr == nullptr ? nullptr : (TestData*)(classPtr)); 

    while(!(self->IsDone()))
    {
        if(ptr != nullptr) self->write(ptr->str); 
    }//EOF Tasking Loop. 
}





int main()
{
    TestData test;
    TestTask tac;
    std::function<void(TAC::Tasking*, TAC::Tasking::ClientData*)> func = TestBody; 
    tac.construct("Josh is awesome", func);
    tac.start(test.Clone());
    tac.shutDown(); 
    return EXIT_SUCCESS; 
}
