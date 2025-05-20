#include"hdr/tasking.hpp"


namespace TAC{


Tasking::Tasking() : _shutdown(false), _debug(false), _thread(nullptr), _name("default"), _taskBody() 
{

}

Tasking::~Tasking()
{

}

void Tasking::construct(/*Add args*/ std::string taskName, 
                        std::function<void(Tasking*, ClientData*)> taskBody) 
{
    initialize();
    _name = taskName;
    _taskfile.open("./testing.log"); //TODO: update this.
    _taskBody = taskBody;
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

bool Tasking::debugOn() const
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

void Tasking::shutDown()
{
    //_shutdown = true;
    _thread->join(); 
}

void Tasking::start(ClientData* classPtr)
{
    pthread_setname_np(pthread_self(),_name.c_str()); 
    _thread = new std::thread(_taskBody,this,classPtr);  
}

}//EOF TAC namespace. 
