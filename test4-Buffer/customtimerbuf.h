#ifndef CUSTOMTIMERBUF_H
#define CUSTOMTIMERBUF_H

#include <QtCore>

#include <buffer.h>
#include <TestObject.h>

class CustomTimerBuf : QObject
{
    Q_OBJECT
public:
    CustomTimerBuf();
    QTimer *timer1;
    QTimer *timer2;
    int counter;
    Numbers::Buffer<TestObject> *buf;


public slots:
    void changeArray();
    void getCounter();

    QString getRandomString();
    TestObject objectData();

    void insertSingleElement();
    void insertMultipleElements();
    void removeSingleElement();
    void removeMultipleElements();
};

#endif // CUSTOMTIMERBUF_H
