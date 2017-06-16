#include "fdsnrequestdialog.h"
#include "ui_fdsnrequestdialog.h"



FDSNRequestDialog::FDSNRequestDialog(QWidget *parent, qreal latitude, qreal longitude) :
    QDialog(parent),
    ui(new Ui::FDSNRequestDialog)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->LatitudeMaximumEdit->setText(QString::number(latitude + (RANGE / 2.0f)));
    ui->LatitudeMinimumEdit->setText(QString::number(latitude - (RANGE / 2.0f)));

    ui->LongitudeMaximumEdit->setText(QString::number(longitude + (RANGE / 2.0f)));
    ui->LongitudeMinimumEdit->setText(QString::number(longitude - (RANGE / 2.0f)));

}

FDSNRequestDialog::~FDSNRequestDialog()
{
    delete ui;
}

//Add error checking function

void FDSNRequestDialog::on_ConnectButton_clicked()
{
    QUrl url = GenerateURL();
    url.setQuery(GenerateQuery());

    QMessageBox::information(this, "Result", url.toString());

    ConnectDialog connect(this);
    connect.SetURL(url);
    if (connect.exec() == QDialog::Rejected)
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
        url.setPath(
            "/fdsnws/" +
            ui->ServiceSelect->currentText().toLower() + "/" +
            ui->VersionEdit->text() + "/" +
            ui->MethodSelect->currentText().toLower());
    }

    return url;
}

void FDSNRequestDialog::onUpdateCoords(qreal latitude, qreal longitude)
{
    ui->LatitudeMaximumEdit->setText(QString::number(latitude + (RANGE / 2.0f)));
    ui->LatitudeMinimumEdit->setText(QString::number(latitude - (RANGE / 2.0f)));

    ui->LongitudeMaximumEdit->setText(QString::number(longitude + (RANGE / 2.0f)));
    ui->LongitudeMinimumEdit->setText(QString::number(longitude - (RANGE / 2.0f)));
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
        { "maxlon", ui->LongitudeMaximumEdit->text() },
        { "limit", ui->LimitEdit->text() },
        { "orderby", GenerateOrderByFragment() }
    };

    //Remove empty pairs
    for (auto key : fragments.uniqueKeys()) {
        if (fragments.value(key).isEmpty())
            fragments.remove(key);
    }

    QString query;


    for (auto i = fragments.begin(); i != fragments.end(); i++) {
        query += i.key() + "=" + i.value() + "&";
    }

    return query;
}

QString FDSNRequestDialog::GenerateOrderByFragment()
{
    QString fragment;
    if (ui->OrderByMagnitudeRadioButton->isChecked())
        fragment = "magnitude";
    else
        fragment = "time";

    if (ui->OrderByAscendingRadioButton->isChecked())
        fragment += "-asc";

    return fragment;
}


