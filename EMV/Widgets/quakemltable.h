#ifndef QUAKEMLTABLE_H
#define QUAKEMLTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

#include "QuakeML/quakemlevent.h"

class QuakeMLTable : public QTableWidget
{
        Q_OBJECT
public:
    QuakeMLTable(QWidget* parent = 0);

    void AddQuakeMLEvent(QuakeMLEvent event);
    void AddQuakeMLEvents(QVector<QuakeMLEvent> events);

};

#endif // QUAKEMLTABLE_H
