#ifndef SIMULINHOWINDOW_H
#define SIMULINHOWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
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
    ~SIMULinho();

signals:

private:
    Ui::SIMULinho *ui;
};


#endif // SIMULINHOWINDOW_H
