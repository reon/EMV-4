#ifndef EARTHWORMSETTINGS_H
#define EARTHWORMSETTINGS_H

#include <QDebug>
#include <QDialog>
#include <QSettings>
#include <QDateTime>
#include <QFileDialog>


namespace Ui {
class EarthWormSettings;
}

class EarthWormSettings : public QDialog
{
    Q_OBJECT

public:
    explicit EarthWormSettings(QWidget *parent = 0);
    ~EarthWormSettings();

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::EarthWormSettings *ui;
    QSettings qsettings;
};

#endif // EARTHWORMSETTINGS_H
