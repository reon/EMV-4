#include "emv.h"
#include "ui_emv.h"

#include <QMessageBox>

EMV::EMV(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EMV),
    net{this}
{
    ui->setupUi(this);

    connect(&net, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}

EMV::~EMV()
{
    delete ui;
}

void EMV::on_actionTest_1_Get_triggered()
{
//    QMessageBox::information(this, "Host", GetURL().host());
    QString rawQuery = "minmag=5&limit=200&maxlat=38.101&minlon=-105.64100000000002&minlat=36.099&maxlon=-103.769&orderby=time";
    QUrlQuery query(rawQuery);

    QUrl url = GetURL();
    url.setQuery(query);

    net.get(QNetworkRequest(url));
}

void EMV::replyFinished(QNetworkReply* response)
{
    QString status = response->error()==QNetworkReply::NoError ? "Success" : "Error";
    QMessageBox::information(this, "Network response.", status);
    response->deleteLater();
}
