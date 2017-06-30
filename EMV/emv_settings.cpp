#include "emv.h"
#include "ui_emv.h"


void EMV::LoadSettings()
{
    ui->action_Connect_on_Startup->blockSignals(true);
    ui->action_Connect_on_Startup->setChecked(settings.value("start/EWHypo").toBool());
    ui->action_Connect_on_Startup->blockSignals(false);

}
