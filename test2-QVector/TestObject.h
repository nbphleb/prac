#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QString>

struct TestObject
    {
        //Идентификатор
        int id;

        //Координаты
        double  x;
        double  y;
        double  z;

        //Скорость
        double  vx;
        double  vy;
        double  vz;

        //Описание
        QString name;
    };

#endif // TESTOBJECT_H
