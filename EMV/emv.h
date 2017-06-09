#ifndef EMV_H
#define EMV_H

#include <QMainWindow>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QtNetwork/qnetworkaccessmanager.h>

namespace Ui {
class EMV;
}

class EMV : public QMainWindow
{
    Q_OBJECT

public:
    explicit EMV(QWidget *parent = 0);
    ~EMV();

    static QUrl GetURL() { return QUrl("http://service.iris.edu/fdsnws/event/1/query"); }
//    static QUrl GetURL() { return QUrl("http://www.google.com"); }

private slots:
    void on_actionTest_1_Get_triggered();

    //Network
    void replyFinished(QNetworkReply* response);

private:
    Ui::EMV *ui;
    QNetworkAccessManager net;


};

#endif // EMV_H
