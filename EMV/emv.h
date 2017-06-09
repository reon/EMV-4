#ifndef EMV_H
#define EMV_H

#include <QMainWindow>

namespace Ui {
class EMV;
}

class EMV : public QMainWindow
{
    Q_OBJECT

public:
    explicit EMV(QWidget *parent = 0);
    ~EMV();

private:
    Ui::EMV *ui;
};

#endif // EMV_H
