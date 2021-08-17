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

public slots:

private slots:
    void on_label_windowTitleChanged(const QString &title);

private:
    Ui::SIMULinhoWindow *ui;
};


#endif // SIMULINHOWINDOW_H
