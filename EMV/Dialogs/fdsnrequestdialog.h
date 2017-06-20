#ifndef FDSNREQUESTDIALOG_H
#define FDSNREQUESTDIALOG_H

#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDialog>
#include <QDateTime>
#include <QUrl>

#include "Dialogs/connectdialog.h"

namespace Ui {
class FDSNRequestDialog;
}

class FDSNRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FDSNRequestDialog(QWidget *parent = 0, qreal latitude = 37.0 /*43.085*/, qreal longitude = -104.0 /*-73.788*/);
    ~FDSNRequestDialog();

signals:
    void NewFDSNResponse(QString QuakeML);

public slots:
    void onUpdateCoords(qreal latitude, qreal longitude);

private slots:
    void on_ConnectButton_clicked();
    void on_StandardCallingPatternCheck_toggled(bool checked);

    void on_StartDateTimeEdit_dateTimeChanged(const QDateTime&);

    void on_EndDateTimeEdit_dateTimeChanged(const QDateTime&);

private:
    /// Return Scheme + Authority + Path
    QUrl GenerateURL();
    QString GenerateQuery();
    QString GenerateOrderByFragment();
    QString GenerateDateTimeFragment(QDateTime);


    //Members
public:
    const float RANGE = 1.0f;
private:
    Ui::FDSNRequestDialog *ui;


};

#endif // FDSNREQUESTDIALOG_H
