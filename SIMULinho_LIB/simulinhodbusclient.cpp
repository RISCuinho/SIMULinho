#include "simulinhodbusclient.h"
#include <dbus-cxx.h>
#include <iostream>

std::string SIMULinhoDBusClient::simulatorVersion(){

    std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();

    std::shared_ptr<DBus::Connection> connection = dispatcher->create_connection( DBus::BusType::SESSION );

    //create an object proxy, which stands in for a real object.
    //a proxy exists over the dbus
    std::shared_ptr<DBus::ObjectProxy>  objectProxy = connection->create_object_proxy(
                SIMULINHO_DBUS_DOMAIN,
                SIMULINHO_DBUS_OBJECT_PATH);

    DBus::MethodProxy<std::string()>& getVersion = *(objectProxy->create_method<std::string()>("Simulinho", "Version"));
    return getVersion();
}



SIMULinhoClient* SIMULinhoDBusClient::getInstance()
{
    static SIMULinhoDBusClient instance;
    return &instance;
}

