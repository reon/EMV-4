#ifndef QUAKEMLREADER_H
#define QUAKEMLREADER_H

#include <QString>
#include <QXmlStreamReader>

class QuakeMLReader
{
public:
    QuakeMLReader(QString xml);

private:
    void ProcessEventParameters();
    void ProcessEvent();
    void ProcessOrigin();
    void ProcessLatitude();
    void ProcessValue();

    QXmlStreamReader xml;
};

#endif // QUAKEMLREADER_H
