#include <QMessageBox>
#include <QDebug>

#include "quakemlreader.h"

QuakeMLReader::QuakeMLReader(QString XMLstring)
    : xml(XMLstring)
{
    while(!xml.atEnd())
    {
        xml.readNextStartElement();

//        if (xml.name() == "eventParameters") ProcessEventParameters();
        if (QString::compare(xml.name().toString(),QString("eventParameters"),Qt::CaseInsensitive) == 0)
            ProcessEventParameters();

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
        else if (xml.name() == "type")
            currentEvent.magnitudeType = ProcessValue();
        else
            xml.skipCurrentElement();
    }
}

//QString QuakeMLReader::ProcessValue()
//{
//    while (xml.readNextStartElement()) {
//        if (xml.name() == "value")
//            value = xml.readElementText().trimmed();
//        else
//            xml.skipCurrentElement();
//    }

//    return value;
//}


QString QuakeMLReader::ProcessValue()
{
    QString innerText = xml.readElementText(QXmlStreamReader::SkipChildElements).trimmed();
    if (innerText.isEmpty()) return "";

    QString pattern = QStringLiteral(R"RAW((?:<value>)?(\S+)(?:<\/value>)?)RAW");
    QRegularExpression regex(pattern, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = regex.match(innerText);

    if (!match.hasMatch()) return "";

//    for (auto str : match.capturedTexts())
//        qDebug(str.toLatin1());

    return match.captured(0);
}
