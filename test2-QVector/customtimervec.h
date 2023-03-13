#ifndef CUSTOMTIMERVEC_H
#define CUSTOMTIMERVEC_H

#include <QtCore>

#include <TestObject.h>

class CustomTimerVec : QObject
{
    Q_OBJECT
public:
    CustomTimerVec();
    QTimer *timer1;
    QTimer *timer2;
    int counter;
    QVector<TestObject> *vec;

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

#endif // CUSTOMTIMERVEC_H
