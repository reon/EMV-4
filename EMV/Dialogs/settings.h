#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>

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
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::Settings *ui;
    QSettings settings;
};

#endif // SETTINGS_H
