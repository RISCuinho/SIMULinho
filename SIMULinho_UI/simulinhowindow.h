#ifndef SIMULINHOWINDOW_H
#define SIMULINHOWINDOW_H

#include <QMainWindow>

namespace Ui {
    class SIMULinhoWindow;
}

class SIMULinhoWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SIMULinhoWindow(QWidget *parent = nullptr);
    ~SIMULinhoWindow();

signals:

private:
    Ui::SIMULinhoWindow *ui;
};


#endif // SIMULINHOWINDOW_H
