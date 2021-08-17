#include "simulinho_window.h"
#include "ui_simulinho_window.h"

SIMULinhoWindow::SIMULinhoWindow(QWidget *parent) : QMainWindow(parent),  ui(new Ui::SIMULinhoWindow)
{
    ui->setupUi(this);
}

SIMULinhoWindow::~SIMULinhoWindow()
{
    delete ui;
}

