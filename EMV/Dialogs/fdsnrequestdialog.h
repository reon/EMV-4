#ifndef FDSNREQUESTDIALOG_H
#define FDSNREQUESTDIALOG_H

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDialog>

#include <QUrl>

namespace Ui {
class FDSNRequestDialog;
}

class FDSNRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FDSNRequestDialog(QWidget *parent = 0);
    ~FDSNRequestDialog();

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
