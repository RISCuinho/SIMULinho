#ifndef SIMULINHOWINDOW_H
#define SIMULINHOWINDOW_H

#include <QMainWindow>

namespace Ui {
    class SIMULinho;
}

class SIMULinho : public QMainWindow
{
    Q_OBJECT
public:
    explicit SIMULinho(QWidget *parent = nullptr);
    ~SIMULinho();

signals:

private:
    Ui::SIMULinho *ui;
};


#endif // SIMULINHOWINDOW_H
