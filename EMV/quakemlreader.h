#ifndef QUAKEMLREADER_H
#define QUAKEMLREADER_H

#include <QString>
#include <QVector>
#include <QXmlStreamReader>

#include "quakemlevent.h"

class QuakeMLReader
{
public:
    QuakeMLReader(QString xml);

    QVector<QuakeMLEvent> events;

private:
    void ProcessEventParameters();
    void ProcessEvent();
    void ProcessOrigin();
    void ProcessMagnitude();
    QString ProcessValue();

    QXmlStreamReader xml;

    QuakeMLEvent currentEvent;
};

#endif // QUAKEMLREADER_H


