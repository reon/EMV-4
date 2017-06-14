#include "fdsnrequestdialog.h"
#include "ui_fdsnrequestdialog.h"

FDSNRequestDialog::FDSNRequestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDSNRequestDialog)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
}

FDSNRequestDialog::~FDSNRequestDialog()
{
    delete ui;
}

//Add error checking function

void FDSNRequestDialog::on_ConnectButton_clicked()
{
//    ui->ConnectButton->setDisabled(true);

    QUrl url = GenerateURL();
    url.setQuery(GenerateQuery());

    QMessageBox::information(this, "Result", url.toString());

    ConnectDialog connect(this);
    if (!connect.exec())
        return;

    emit NewFDSNResponse(connect.RetrieveResponse());

}

void FDSNRequestDialog::on_StandardCallingPatternCheck_toggled(bool checked)
{
    ui->ServiceSelect->setEnabled(checked);
    ui->MethodSelect->setEnabled(checked);
}

QUrl FDSNRequestDialog::GenerateURL()
{
//    QUrl url(ui->HostListWidget->currentItem()->text());

    QUrl url = QUrl::fromUserInput(ui->HostListWidget->currentItem()->text());

    if (ui->StandardCallingPatternCheck->isChecked()) {
        url.setPath("/fdsnws/" + ui->ServiceSelect->currentText().toLower()
            + "/" + ui->VersionEdit->text() + "/");
    }

    return url;
}

QString FDSNRequestDialog::GenerateQuery()
{
    QString Remove = "Remove";

    QMap<QString, QString> fragments
    {
        { "minmag", ui->MagnitudeMinimumEdit->text() },
        { "maxmag", ui->MagnitudeMaximumEdit->text() },
        { "minlat", ui->LatitudeMinimumEdit->text() },
        { "maxlat", ui->LatitudeMaximumEdit->text() },
        { "minlon", ui->LongitudeMinimumEdit->text() },
        { "maxlon", ui->LongitudeMaximumEdit->text() }
    };

    //Remove empty pairs
    for (auto key : fragments.uniqueKeys()) {
        qDebug() << key << "\n";
        if (fragments.value(key).isEmpty())
            fragments.remove(key);
    }

    QString query;


    for (auto i = fragments.begin(); i != fragments.end(); i++) {
        query += i.key() + "=" + i.value() + "&";
    }

    return query;
}

