#ifndef __TASKING_HPP__
#define __TASKING_HPP__
#include<thread> 
#include<functional>
#include<fstream> 
#include<string> 

namespace TAC{

class Tasking
{
    public:
        struct ClientData; //Forward declare. 
        Tasking(); 
        Tasking(const Tasking&)            = delete;
        Tasking(Tasking&&)                 = delete;
        Tasking& operator=(const Tasking&) = delete;
        Tasking& operator=(Tasking&&)      = delete;
        virtual ~Tasking();
        virtual void ShutDown();
        virtual void Start() final;  
        void construct(std::string,
                       std::string, 
                       ClientData&, 
                       std::function<void(Tasking*)>); //Cap
        void write(const std::string&); //Cap
        void setDebug(bool debug = false); //Cap
        bool DebugOn() const;
        bool IsDone()  const; 
        std::string getName() const; //Cap
        const ClientData*  GetClientData() const;
        std::thread::id GetID() const; 
    public:
        struct ClientData
        {
            ClientData()                  = default;
            virtual ~ClientData()         = default;
            ClientData(const ClientData&) = default;
            ClientData(ClientData&&)      = default;
            virtual ClientData* Clone()   = 0;
            private:
                /*Inherit then add into its private*/ 
        };

    private: 
        virtual void initialize() = 0; 
    protected: 
        bool                          _shutdown; //
        bool                          _debug;   //
        std::thread*                  _thread;
        std::ofstream                 _taskfile;
        mutable std::string           _name;
        std::function<void(Tasking*)> _taskBody;
        ClientData*                   _clientData;
        std::thread::id               _myID; 
};







}//EOF TAC namespace. 



#endif 
