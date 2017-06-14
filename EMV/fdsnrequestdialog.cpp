#include "fdsnrequestdialog.h"
#include "ui_fdsnrequestdialog.h"

FDSNRequestDialog::FDSNRequestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDSNRequestDialog)
{
    ui->setupUi(this);

    ui->ServiceSelect->addItems(QStringList{"Event", "Station", "Dataselect"});
}

FDSNRequestDialog::~FDSNRequestDialog()
{
    delete ui;
}
