#include "simulinhodbusserver.h"

#include <dbus-cxx.h>
#include <sigc++/sigc++.h>
#include <unistd.h>
#include <iostream>

std::string version(){
    printf("SIMULinhoDBusServer version method");
    return "0";
}




SIMULinhoDBusServer::SIMULinhoDBusServer()
{
    connection->add_thread_dispatcher( thrDisp );

    DBus::RequestNameResponse ret = connection->request_name(
                SIMULINHO_DBUS_DOMAIN,
                DBUSCXX_NAME_FLAG_REPLACE_EXISTING);
    printf("SIMULinhoDBusServer connection result: %s, %i !\n", ret,ret);
    if( ret != DBus::RequestNameResponse::PrimaryOwner )
        return ;

    printf("SIMULinhoDBusServer dispatcher and connection: %s ok!\n", SIMULINHO_DBUS_DOMAIN);

    object = connection->create_object(SIMULINHO_DBUS_OBJECT_PATH,
                                 DBus::ThreadForCalling::DispatcherThread);

    printf("SIMULinhoDBusServer new object path: %s\n", SIMULINHO_DBUS_OBJECT_PATH);

    object->create_method<std::string()>(SIMULINHO_DBUS_INTERFACE,
                                         "version",
                                         sigc::ptr_fun(version) );

    printf("SIMULinhoDBusServer new method: version, interface: %s\n", SIMULINHO_DBUS_INTERFACE);
}
