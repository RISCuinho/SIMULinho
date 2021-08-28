#include "simulinho.h"
#include "memorytable.h"
#include "ui_simulinho.h"

#include <QWidget>
#include <QLabel>
#include <QProgressBar>

SIMULinho::SIMULinho(QWidget *parent) : QMainWindow(parent),  ui(new Ui::SIMULinho)
{

    ui->setupUi(this);

    // create objects for the label and progress bar
    statusLabel = new QLabel(this);
    statusProgressBar = new QProgressBar(this);

    // add the two controls to the status bar
    ui->statusbar->addPermanentWidget(statusLabel);
    ui->statusbar->addPermanentWidget(statusProgressBar,1);

    // set text for the label
    statusLabel->setText("Status Label!");

    // make progress bar text invisible
    statusProgressBar->setTextVisible(false);
}

void SIMULinho::setRegisterTableModel(QAbstractItemModel * model){
    ui->registersTableView->init(model);
}
void SIMULinho::setProgramTableModel(QAbstractItemModel * model){
    ui->programTableView->init(model);
}
void SIMULinho::setDataTableModel(QAbstractItemModel * model){
    ui->dataTableView->init(model);
}

SIMULinho::~SIMULinho()
{
    delete ui;
}


void SIMULinho::on_actionSair_triggered()
{
    //connect(ui->actionSair, &QAction::triggered, this, &QWidget::close);
    printf("Sair!\n");

}
