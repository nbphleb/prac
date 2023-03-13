#ifndef CUSTOMTIMERQUE_H
#define CUSTOMTIMERQUE_H

#include <QtCore>

#include <TestObject.h>

class CustomTimerQue : public QObject
{
    Q_OBJECT
public:
    CustomTimerQue();
    QTimer *timer1;
    QTimer *timer2;
    int counter;
    QQueue<TestObject> *que;

public slots:
    void changeArray();
    void getCounter();

    QString getRandomString();
    TestObject objectData();

    void enqueSingleElement();
    void enqueMultipleElements();
    void dequeSingleElement();
    void dequeMultipleElements();
};

#endif // CUSTOMTIMERQUE_H
