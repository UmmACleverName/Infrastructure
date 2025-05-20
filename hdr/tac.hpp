#include<thread>
#include<string>



namespace TAC{

class Tac{

    public:
        Tac();
        ~Tac();
        Tac(const Tac&) = delete;
        //Tac(Tac&&);

    public:
        Tac& operator=(const Tac&) = delete;
        //Tac& operator=(Tac&&);
        template<class Function, class... Args>
        void Start(Function func, Args... args);
        virtual void End() = 0; 
        std::string GetName();

    private:
        std::thread* _cppThreadPtr;
        std::string  _tacName;
        bool         _hasStarted;


}; //EOF Tac class.


Tac::Tac() : _cppThreadPtr(nullptr), _tacName("Default Name"),
             _hasStarted(false)
{}

Tac::~Tac()
{
    delete _cppThreadPtr; 
}


template<class Function, class... Args>
void Tac::Start(Function func, Args... args)
{
    if(!_hasStarted)
    {
        _hasStarted   = true;
        _cppThreadPtr = new std::thread(func,args...);
    }

}


std::string Tac::GetName()
{
    return _tacName; 
}






}//EOF TAC Namespace.
