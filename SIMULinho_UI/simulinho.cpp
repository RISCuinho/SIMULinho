#include "simulinho.h"
#include "ui_simulinho.h"

SIMULinho::SIMULinho(QWidget *parent) : QMainWindow(parent),  ui(new Ui::SIMULinho)
{
    ui->setupUi(this);
}

SIMULinho::~SIMULinho()
{
    delete ui;
}

