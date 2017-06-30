#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);

    //Add another SIGNAL from net, the one that gives progress updates and display to user
    connect(&net, SIGNAL(finished(QNetworkReply*)), this, SLOT(ReplyFinished(QNetworkReply*)));
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::showEvent(QShowEvent *)
{
    if (url.isEmpty())
        return;

    if (started.testAndSetOrdered(0, 1))
    {
        net.get(QNetworkRequest(url));
    }
}

void ConnectDialog::ReplyFinished(QNetworkReply* response)
{
    if (ProcessReply(response))
        this->accept();
    else
        this->reject();
}

bool ConnectDialog::ProcessReply(QNetworkReply* response)
{
//    QString status = response->error()==QNetworkReply::NoError ? "Success" : "Error";
//    QMessageBox::information(this, "Network response.", status);

    response->deleteLater();

    if (response->error() != QNetworkReply::NoError) {
        qDebug() << "Network error.\n" << response->errorString();
        return false;
    }

    QByteArray bytes = response->readAll();
    QString strResponse = QString(bytes);

    int httpCode = response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (httpCode != 200)
    {
        //Default message
        QString message = "Failed to retreive data \n Response: \n" + strResponse;

        if (httpCode ==  204)
            message = "Request Successful, However No Data Matches Selection";

        QMessageBox::critical(this, "FDSN response", message);
        return false;
    }

    xmlResponse = strResponse;

    return true;
}



void ConnectDialog::on_CancelButton_clicked()
{
    this->reject();
}
