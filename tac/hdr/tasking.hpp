#ifndef __TASKING_HPP__
#define __TASKING_HPP__
#include<thread> 
#include<functional>
#include<fstream> 
#include<string> 

/**
 * @file tasking.hpp
 * @brief This file defines the Tasking class.
 */

/**
 * @class Tasking
 * @brief A simple example class to demonstrate Doxygen.
 *
 * This class contains a constructor.
 */

namespace TAC{

class Tasking
{
    public:
        struct ClientData; //Forward declare.
        /**
         * @brief Constructor for Tasking.
         *
         * Initializes a new instance of Tasking.
         */
        Tasking(); 
        Tasking(const Tasking&)            = delete;
        Tasking(Tasking&&)                 = delete;
        Tasking& operator=(const Tasking&) = delete;
        Tasking& operator=(Tasking&&)      = delete;
        virtual ~Tasking();
        virtual void ShutDown();
        virtual void Start() final;  
        void Construct(std::string,
                       std::string, 
                       ClientData&, 
                       std::function<void(Tasking*)>);
        void Write(const std::string&);
        void SetDebug(bool debug = false);
        bool DebugOn() const;
        bool IsDone()  const; 
        std::string GetName() const; 
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
