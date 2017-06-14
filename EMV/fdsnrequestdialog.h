#ifndef FDSNREQUESTDIALOG_H
#define FDSNREQUESTDIALOG_H

#include <QDialog>

namespace Ui {
class FDSNRequestDialog;
}

class FDSNRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FDSNRequestDialog(QWidget *parent = 0);
    ~FDSNRequestDialog();

private:
    Ui::FDSNRequestDialog *ui;
};

#endif // FDSNREQUESTDIALOG_H
