#include "simulinho.h"
#include "ui_simulinhowindow.h"

SIMULinhoWindow::SIMULinhoWindow(QWidget *parent) : QMainWindow(parent),  ui(new Ui::SIMULinhoWindow)
{
    ui->setupUi(this);
}

SIMULinhoWindow::~SIMULinhoWindow()
{
    delete ui;
}

