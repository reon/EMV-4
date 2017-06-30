#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_checkBox_stateChanged(int)
{
    settings.setValue("start/EWHypo", ui->EW_Startup_Connect->isChecked());
}
