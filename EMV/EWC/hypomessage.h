#ifndef HYPOMESSAGE_H
#define HYPOMESSAGE_H

#include <QObject>

class HypoMessage : public QObject
{
    Q_OBJECT
public:
    explicit HypoMessage(QObject *parent = 0);

signals:
    void MessageReceived();

public slots:

};

#endif // HYPOMESSAGE_H
