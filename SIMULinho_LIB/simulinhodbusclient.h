#ifndef SIMULINHODBUSCLIENT_H
#define SIMULINHODBUSCLIENT_H

#include "simulinho_lib_global.h"
#include "simulinhoclient.h"
#include "simulinhodbus.h"
#include "shared_mutex"

class SIMULINHO_LIB_SHARED SIMULinhoDBusClient : public
        SIMULinhoClient,
        SIMULinhoDBus
{
public:
    std::string simulatorVersion();

    static SIMULinhoClient* getInstance();


private:
    SIMULinhoDBusClient(){}

#if (__cplusplus < 201703L)
public:
    SIMULinhoDBusClient(SIMULinhoDBusClient *const)   = delete;
    void operator=(SIMULinhoDBusClient *const) = delete;
#else
private:
    SIMULinhoDBusClient(SIMULinhoDBusClient const&);   // Don't Implement
    void operator=(SIMULinhoDBusClient const&); // Don't implement
#endif
};

#endif // SIMULINHODBUSCLIENT_H
