#include "simulinho.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SIMULinho w;

    w.setWindowTitle("SIMULinho!");

    w.show();

    return a.exec();
}
