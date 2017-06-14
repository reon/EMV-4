#include "fdsnrequestdialog.h"
#include "ui_fdsnrequestdialog.h"

FDSNRequestDialog::FDSNRequestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDSNRequestDialog)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
//    ui->ServiceSelect->addItems(QStringList{"Event", "Station", "Dataselect"});
}

FDSNRequestDialog::~FDSNRequestDialog()
{
    delete ui;
}

void FDSNRequestDialog::on_ConnectButton_clicked()
{
    ui->ConnectButton->setDisabled(true);
}
