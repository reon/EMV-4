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
        if (xml.name() == "event") ProcessEvent();
        else xml.skipCurrentElement();
    }
}

void QuakeMLReader::ProcessEvent()
{
    while(xml.readNextStartElement()) {
        if (xml.name() == "origin") ProcessOrigin();
        else xml.skipCurrentElement();
    }
}

void QuakeMLReader::ProcessOrigin()
{
    while (xml.readNextStartElement()) {
        if (xml.name() == "latitude") ProcessLatitude();
        else xml.skipCurrentElement();
    }
}

void QuakeMLReader::ProcessLatitude()
{
    QString value;

    while (xml.readNextStartElement()) {
        if (xml.name() == "value")
        {
            value = xml.readElementText();
            QMessageBox::information(nullptr, "Latitude", value);
        }
    }
}
