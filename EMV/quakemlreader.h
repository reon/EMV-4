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
    void ProcessEventParameters();      // <eventParameters>
    void ProcessEvent();                // <eventParameters><event>
    void ProcessOrigin();               // <event><origin>
    void ProcessMagnitude();            // <event><magnitude>
    QString ProcessValue();             // <*><value>QString</value>
    //QString ProcessValue(QString tag) // <*><tag>QString</tag>

    QXmlStreamReader xml;

    QuakeMLEvent currentEvent;
};

#endif // QUAKEMLREADER_H


