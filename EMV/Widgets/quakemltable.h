#ifndef QUAKEMLTABLE_H
#define QUAKEMLTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

#include "QuakeML/quakemlevent.h"

class QuakeMLTableWidget : public QTableWidget
{
        Q_OBJECT
public:
    QuakeMLTableWidget(QWidget* parent = 0);

    void AddQuakeMLEvent(QuakeMLEvent event);
    void AddQuakeMLEvents(QVector<QuakeMLEvent> events);

};

#endif // QUAKEMLTABLE_H
