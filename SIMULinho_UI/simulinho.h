#ifndef SIMULINHOWINDOW_H
#define SIMULINHOWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QAbstractItemModel>
#include <QStatusBar>
#include <QProgressBar>

namespace Ui {
    class SIMULinho;
}

class SIMULinho : public QMainWindow
{
    Q_OBJECT

protected:
    QLabel *statusLabel;
    QProgressBar *statusProgressBar;

public:
    explicit SIMULinho(QWidget *parent = nullptr);
    void setRegisterTableModel(QAbstractItemModel * model);
    ~SIMULinho();

signals:

private slots:
    void on_actionSair_triggered();

private:
    Ui::SIMULinho *ui;
};


#endif // SIMULINHOWINDOW_H
