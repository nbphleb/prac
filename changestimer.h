#ifndef CHANGESTIMER_H
#define CHANGESTIMER_H

#include <QtCore>

#include <TestObject.h>

class ChangesTimer : public QObject
{
    Q_OBJECT
public:
    ChangesTimer();
    QTimer *timer1;
    QTimer *timer2;
    int counter;
    QList<TestObject> *list;

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

#endif // CHANGESTIMER_H
