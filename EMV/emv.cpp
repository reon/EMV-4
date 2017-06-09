#include "emv.h"
#include "ui_emv.h"

EMV::EMV(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EMV)
{
    ui->setupUi(this);
}

EMV::~EMV()
{
    delete ui;
}
