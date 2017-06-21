#ifndef QUAKEMLREADER_H
#define QUAKEMLREADER_H

#include <QtCore>
#include <QString>
#include <QVector>
#include <QXmlStreamReader>

#include <QRegularExpression> //Should not be needed

#include "quakemlevent.h"

class QuakeMLReader
{
public:
    QuakeMLReader(QString xml);

    QVector<QuakeMLEvent> events;

private:
    void ProcessEventParameters();      // <eventParameters>
    void ProcessEvent();                // <eventParameters><event>
    void ProcessEventAttributes();      // <eventParameters><event *>
    void ProcessOrigin();               // <eventParameters><event><origin>
    void ProcessMagnitude();            // <eventParameters><event><magnitude>
    QString ProcessValue();             // <*><value>QString</value>
    //QString ProcessValue(QString tag) // <*><tag>QString</tag>

    QXmlStreamReader xml;

    QuakeMLEvent currentEvent;
};

#endif // QUAKEMLREADER_H


