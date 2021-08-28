#ifndef SIMULINHODBUSSERVER_H
#define SIMULINHODBUSSERVER_H

#include "simulinho_lib_global.h"
#include "simulinhoserver.h"
#include "simulinhodbus.h"
#include <iostream>

std::string version();

class SIMULINHO_LIB_SHARED SIMULinhoDBusServer : public
        SIMULinhoServer,
        SIMULinhoDBus
{
private:
    SIMULinhoDBusServer();
public:
    static SIMULinhoServer* getInstance()
    {
        static SIMULinhoDBusServer instance;
        return &instance;
    }
#if (__cplusplus < 201703L)
public:
    SIMULinhoDBusServer(SIMULinhoDBusServer *const)   = delete;
    void operator=(SIMULinhoDBusServer *const) = delete;
#else
private:
    SIMULinhoDBusServer(SIMULinhoDBusServer const&);   // Don't Implement
    void operator=(SIMULinhoDBusServer const&); // Don't implement
#endif
};

#endif // SIMULINHODBUSSERVER_H
