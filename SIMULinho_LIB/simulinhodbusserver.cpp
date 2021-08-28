#include "simulinhodbusserver.h"

#include <dbus-cxx.h>
#include <sigc++/sigc++.h>
#include <unistd.h>
#include <iostream>

std::string version(){

    return "0";
}




SIMULinhoDBusServer::SIMULinhoDBusServer()
{
    std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();

    std::shared_ptr<DBus::Connection> conn = dispatcher->create_connection(DBus::BusType::SESSION);

    if( conn->request_name(SIMULINHO_DBUS_DOMAIN,
                           DBUSCXX_NAME_FLAG_REPLACE_EXISTING )
            != DBus::RequestNameResponse::PrimaryOwner )
        return ;

     std::shared_ptr<DBus::Object> object = conn->create_object(SIMULINHO_DBUS_OBJECT_PATH,
                                 DBus::ThreadForCalling::DispatcherThread);


    object->create_method<std::string()>(SIMULINHO_DBUS_INTERFACE,
                                         "version",
                                         sigc::ptr_fun(version) );
}
