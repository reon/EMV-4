#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QAtomicInt>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

    void SetURL(QUrl url) { this->url = url; }
    QString RetrieveResponse() { return xmlResponse; }

protected:
    virtual void showEvent(QShowEvent *);

private:
    bool ProcessReply(QNetworkReply* response);

private slots:
    void ReplyFinished(QNetworkReply*);


    // Members
    void on_CancelButton_clicked();

private:
    Ui::ConnectDialog *ui;

    QNetworkAccessManager net;

    QAtomicInt started {0}; ///< Started if !0

    QUrl url;

    QString xmlResponse;
};

#endif // CONNECTDIALOG_H
