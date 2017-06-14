#ifndef FDSNREQUESTDIALOG_H
#define FDSNREQUESTDIALOG_H

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDialog>

#include <QUrl>

#include "Dialogs/connectdialog.h"

namespace Ui {
class FDSNRequestDialog;
}

class FDSNRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FDSNRequestDialog(QWidget *parent = 0);
    ~FDSNRequestDialog();

signals:
    void NewFDSNResponse(QString QuakeML);

private slots:
    void on_ConnectButton_clicked();

    void on_StandardCallingPatternCheck_toggled(bool checked);

private:
    /// Return Scheme + Authority + Path
    QUrl GenerateURL();
    QString GenerateQuery();


    //Members
public:

private:
    Ui::FDSNRequestDialog *ui;


};

#endif // FDSNREQUESTDIALOG_H
