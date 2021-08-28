#include "simulinho.h"
#include <QApplication>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFile>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(registers);

    QApplication a(argc, argv);
    SIMULinho w;

    QStandardItemModel *model=new QStandardItemModel();

    QFile file(":/registers.txt");
    if (file.open(QFile::ReadOnly)) {
        QString line = file.readLine(200);
        QStringList list = line.simplified().split(',');
        model->setHorizontalHeaderLabels(list);

        int row = 0;
        QStandardItem *newItem = 0;
        while (file.canReadLine()) {
            line = file.readLine(200);
            if (!line.startsWith('#') && line.contains(',')) {
                list = line.simplified().split(',');
                for (int col = 0; col < list.length(); ++col){
                    newItem = new QStandardItem(list.at(col));
                    model->setItem(row, col, newItem);
                }
                ++row;
            }
        }
    }
    file.close();

    w.setRegisterTableModel(model);

    w.setWindowTitle("SIMULinho!");

    w.show();

    return a.exec();
}
