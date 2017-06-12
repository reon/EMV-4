#ifndef QUAKEMLREADER_H
#define QUAKEMLREADER_H

#include <QString>
#include <QVector>
#include <QXmlStreamReader>


class QMLEvent {
public:
    QString time;

    QString latitude;
    QString longitude;

    QString magnitude;
};


class QuakeMLReader
{
public:
    QuakeMLReader(QString xml);

    QVector<QMLEvent> events;

private:
    void ProcessEventParameters();
    void ProcessEvent();
    void ProcessOrigin();
    QString ProcessValue();

    QXmlStreamReader xml;

    QMLEvent currentEvent;
};

#endif // QUAKEMLREADER_H
