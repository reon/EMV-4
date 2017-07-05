#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QDateTime>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();



private slots:

protected:
    void closeEvent(QCloseEvent *) override;

private:
    Ui::Settings *ui;
    QSettings settings;
};

#endif // SETTINGS_H
