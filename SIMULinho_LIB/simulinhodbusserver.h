#ifndef SIMULINHODBUSSERVER_H
#define SIMULINHODBUSSERVER_H

#include "simulinho_lib_global.h"
#include "simulinhoserver.h"
#include "simulinhodbus.h"

#include <dbus-cxx.h>
#include <dbus-cxx-qt.h>

#include <iostream>

std::string version();

class SIMULINHO_LIB_SHARED SIMULinhoDBusServer : public
        SIMULinhoServer,
        SIMULinhoDBus
{
public:
  static SIMULinhoServer* getInstance()
  {
      static SIMULinhoDBusServer instance;
      printf("SIMULinhoDBusServer!/n");
      return &instance;
  }
protected:
  std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();
    std::shared_ptr<DBus::Connection> connection = dispatcher->create_connection( DBus::BusType::SESSION );
    std::shared_ptr<DBus::Qt::QtThreadDispatcher> thrDisp = DBus::Qt::QtThreadDispatcher::create();
    std::shared_ptr<DBus::Object> object;

private:
    SIMULinhoDBusServer();

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
