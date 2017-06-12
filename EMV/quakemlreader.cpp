#include <QMessageBox>
#include <QDebug>

#include "quakemlreader.h"

QuakeMLReader::QuakeMLReader(QString XMLstring)
    : xml(XMLstring)
{
    while(!xml.atEnd())
    {
        xml.readNextStartElement();

        if (xml.name() == "eventParameters") ProcessEventParameters();

        if (xml.tokenType() == QXmlStreamReader::Invalid)
            xml.readNext();
    }

    if (xml.hasError()) {
//        xml.raiseError();
        qDebug() << xml.errorString();
    }
}

void QuakeMLReader::ProcessEventParameters()
{
    while(xml.readNextStartElement()) {
        if (xml.name() == "event")
            ProcessEvent();
        else xml.skipCurrentElement();
    }
}

void QuakeMLReader::ProcessEvent()
{
    currentEvent = {};
    while(xml.readNextStartElement()) {
        if (xml.name() == "origin") ProcessOrigin();
        else if (xml.name() == "magnitude")   ProcessMagnitude();
        else xml.skipCurrentElement();
    }
    events.push_back(currentEvent);
}

void QuakeMLReader::ProcessOrigin()
{
    while (xml.readNextStartElement()) {
        QStringRef name = xml.name();
        if (name == "time")             currentEvent.time = ProcessValue();
        else if (name == "latitude")    currentEvent.latitude = ProcessValue();
        else if (name == "longitude")   currentEvent.longitude = ProcessValue();
        else xml.skipCurrentElement();
    }
}

void QuakeMLReader::ProcessMagnitude()
{
    while (xml.readNextStartElement()) {
        if (xml.name() == "mag")
            currentEvent.magnitude = ProcessValue();
        else
            xml.skipCurrentElement();
    }
}

QString QuakeMLReader::ProcessValue()
{
    QString value;

    while (xml.readNextStartElement()) {
        if (xml.name() == "value")
            value = xml.readElementText();
        else
            xml.skipCurrentElement();
    }

    return value;
}
