#include "simulinho_base_app.h"
#include "simulinho_window.h"

#include <QApplication>
#include <QCoreApplication>
#include <QScopedPointer>
#include <QtConcurrent/QtConcurrent>
#include <QThread>

int startMainWithOutWindow(int argc, char *argv[]){

    QScopedPointer<QCoreApplication> app(new QCoreApplication(argc, argv));

    return app->exec();
}

int startMainWindow(int argc, char *argv[]){
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QScopedPointer<QCoreApplication> app(new QApplication(argc, argv));

        SIMULinhoWindow w;
        w.show();

//    return app->exec();
        QtConcurrent::run([&app]{
            // this runs in a worker thread, and causes the application
            // object to destroy itself and then the program to exit
            app->exec();
          });
        return 0;
}

void closeMainWindow(){
    //w.close();
}

