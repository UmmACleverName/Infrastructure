#include"tac/hdr/tasking.hpp"


namespace TAC{


Tasking::Tasking() : _shutdown(false), _debug(false), _thread(nullptr), _name("default"), _taskBody(),
                     _clientData(nullptr), _myID() 
{}

Tasking::~Tasking()
{
    delete _thread;
    delete _clientData; 
}

void Tasking::construct(std::string taskName,
                        std::string logFile,
                        ClientData& clientData, 
                        std::function<void(Tasking*)> taskBody) 
{
    initialize();
    _name = taskName;
    _taskfile.open(logFile); //TODO: update this.
    _taskBody = taskBody;
    _clientData = clientData.Clone(); 
}

void Tasking::write(const std::string& msg)
{
    size_t size = msg.size(); 
    _taskfile.write(msg.c_str(),size);  
}

void Tasking::setDebug(bool debug)
{
    _debug = debug; 
}

bool Tasking::DebugOn() const
{
    return _debug; 
}

bool Tasking::IsDone() const 
{
    return (_shutdown == true); 
}

std::string Tasking::getName() const
{
    return _name; 
}

std::thread::id Tasking::GetID() const 
{
    return _myID; 
}

const Tasking::ClientData* Tasking::GetClientData() const
{
    return _clientData; 
}

void Tasking::ShutDown()
{
    _shutdown = true;
    _thread->join(); 
}

void Tasking::Start()
{
    pthread_setname_np(pthread_self(),_name.c_str()); 
    _thread = new std::thread(_taskBody,this);  
    _myID   = _thread->get_id(); 
}

}//EOF TAC namespace. 
