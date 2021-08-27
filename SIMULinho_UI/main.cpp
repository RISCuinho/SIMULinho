#include "simulinho.h"
#include <QApplication>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFile>

QStandardItemModel *buildTableModel(const QString &name){
    QStandardItemModel *model=new QStandardItemModel();

    QFile file(name);
    if (file.open(QFile::ReadOnly)) {
        QString line = file.readLine(200);
        QStringList list = line.simplified().split(',');

        const int listLen = list.length();
        for(int i = 2; i < listLen;i++)
            list.removeLast(); // remove a coluna description

        model->setHorizontalHeaderLabels(list);

        int row = 0;
        QStandardItem *newItem = 0;
        QString toolTip;
        while (file.canReadLine()) {
            line = file.readLine(200);
            if (!line.startsWith('#') && line.contains(',')) {
                list = line.simplified().split(',');

                if(list.length() > 2) // description é usado como toolTip
                    toolTip = list.at(2);
                // os campos além de description são específicos de cada memória.
                // em especial memória de dados que possui parametros extras para dispositivos de saída.
                // nesta memória, existe um campo que identifica a estrutura que ela pertence.
                // por exemplo Serial, VGA, ADC, DAC, assim todos os endereços marcados com este grupo
                // pertence a esta estrutura de disposítivo.

                newItem = new QStandardItem(list.at(0));
                newItem->setToolTip(toolTip);
                model->setItem(row, 0, newItem);

                newItem = new QStandardItem(list.at(1));
                newItem->setToolTip(toolTip);
                model->setItem(row, 1, newItem);

                ++row;
            }
        }
    }
    file.close();
    return model;
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(memory);

    QApplication a(argc, argv);
    SIMULinho w;

    w.setRegisterTableModel(buildTableModel(":/registers.txt"));
    w.setProgramTableModel(buildTableModel(":/programmemory.txt"));
    w.setDataTableModel(buildTableModel(":/datamemory.txt"));

    w.setWindowTitle("SIMULinho!");

    w.show();

    return a.exec();
}
