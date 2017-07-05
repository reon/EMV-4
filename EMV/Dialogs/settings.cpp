#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

}

Settings::~Settings()
{
    delete ui;
}

void Settings::closeEvent(QCloseEvent *)
{
    //Autostart
    settings.setValue("EW/autostart", ui->EW_Startup_Connect->isChecked());

    //IP
    QString IP = ui->EarthWormIP->text();
    if (IP.trimmed().length() == 0)
        settings.remove("EW/IP");
    else
        settings.setValue("EW/IP", IP);

    //Port
    QString Port = ui->EarthWormPort->text();
    if (Port.trimmed().length() == 0)
        settings.remove("EW/Port");
    else
        settings.setValue("EW/Port", ui->EarthWormPort->text());

    //Time
    int minutes = ui->TimeAmountSelect->text().toInt();
    int index = ui->TimeUnitSelect->currentIndex();

    if (index == 1)
        minutes *= 60;
    if (index == 2)
        minutes *= 60 * 24;

    QTime range(0, minutes);

    if (minutes <= 0)
        settings.remove("EW/RangeInMinutes");
    else
        settings.setValue("EW/RangeInMinutes", range);

    //Zoom
    int ZoomLevel = ui->ZoomLevel->text().toInt();
    if (ZoomLevel == 0)
        settings.remove("EW/ZoomOnResponse");
    else
        settings.setValue("EW/ZoomOnResponse", ZoomLevel);
}


