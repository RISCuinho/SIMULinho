#include "simulinhodbusclient.h"
#include <dbus-cxx.h>
#include <iostream>

std::string SIMULinhoDBusClient::simulatorVersion(){
    DBus::MethodProxy<std::string()>& getVersion = *(objectProxy->create_method<std::string()>("Simulinho", "Version"));
    return getVersion();
}

SIMULinhoDBusClient::SIMULinhoDBusClient(){

    //create an object proxy, which stands in for a real object.
    //a proxy exists over the dbus
    objectProxy = connection->create_object_proxy(
                SIMULINHO_DBUS_DOMAIN,
                SIMULINHO_DBUS_OBJECT_PATH);
}

SIMULinhoClient* SIMULinhoDBusClient::getInstance()
{
    static SIMULinhoDBusClient instance;
    return &instance;
}

