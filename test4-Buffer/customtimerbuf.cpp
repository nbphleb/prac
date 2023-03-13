#include "customtimerbuf.h"

CustomTimerBuf::CustomTimerBuf()
{
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    buf = new Numbers::Buffer<TestObject>(200);

    connect(timer1, SIGNAL(timeout()), this, SLOT(getCounter()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(changeArray()));

    timer1->start(200); // каждые N мс обращение на изменение
    timer2->start(200); // каждые M мс изменяется массив

    //счетчики изменений
    counter = 0;
}

// функция внесения изменений в массив
void CustomTimerBuf::changeArray()
{
    // генерация случайного значения для выбора действия. 0<=key<4
    short int key = QRandomGenerator::global()->bounded(4);
    //qDebug() << "Key = " << key;

    switch (key)
    {
     case 0: // добавление одного элемента
        {
            insertSingleElement();
        }
        break;

    case 1: // удаление одного элемента
        {
            removeSingleElement();
        }
        break;

    case 2: // добавление списком
        {
            insertMultipleElements();
        }
        break;

    case 3: // удаление списком
        {
            removeMultipleElements();
        }
        break;
    }
}

//функция обращения на изменения массива
void CustomTimerBuf::getCounter()
{
    qDebug() << "Overall changes: " << counter;
}

// функция генерирации имени TestObject
QString CustomTimerBuf::getRandomString()
{
    QString str;
    for (int i = 0; i < 10; i++)
    {
        str = QUuid::createUuid().toString();
        str.remove(QRegularExpression("{|}|-"));
    }
    return str;
}

// функция генерирации значений TestObject
TestObject CustomTimerBuf::objectData()
{
    TestObject obj;
    obj.id = QRandomGenerator::global()->generate();
    obj.name = getRandomString();
    obj.vx = QRandomGenerator::global()->generateDouble();
    obj.vy = QRandomGenerator::global()->generateDouble();
    obj.vz = QRandomGenerator::global()->generateDouble();
    obj.x = QRandomGenerator::global()->generateDouble();
    obj.y = QRandomGenerator::global()->generateDouble();
    obj.z = QRandomGenerator::global()->generateDouble();
    return obj;
}

// функция добавления одного элемента в buf
void CustomTimerBuf::insertSingleElement()
{
    // генерация значений TestObject
    TestObject obj = objectData();
    // добавление элемента
    buf->addItem(obj);
    counter++; //увеличение счетчика изменений
}

// функция добавления нескольких элементов в buf
void CustomTimerBuf::insertMultipleElements()
{
    // генерируется количество добавляемых объектов
    short int n = QRandomGenerator::global()->bounded(199);
    // пока количество добавляемых эл-тов не 0
    while (n > 0)
    {
        // генерация значений TestObject
        TestObject obj = objectData();
        // добавление элемента
        buf->addItem(obj);
        n--; // уменьшение количества добавляемых эл-тов
    }
    counter++; //увеличение счетчика изменений
}

void CustomTimerBuf::removeSingleElement()
{
    // выбор, откуда именно удалится эл-т
    short int i = QRandomGenerator::global()->bounded(200);
    // удаление элемента
    buf->removeAt(i);
    counter++; //увеличение счетчика изменений
}

void CustomTimerBuf::removeMultipleElements()
{
    // генерируется кол-во удаляемых объектов, не превышающее количество эл-тов
    short int n = QRandomGenerator::global()->bounded(199);
    // выбор, с какого индекса начнется удаление
    short int i = QRandomGenerator::global()->bounded(198);
    // если с данного индекса меньше эл-тов, чем требуется удалить, уменьшаем кол-во удаляемых эл-тов
    if ( (n + i) > 200)
    {
        n = 200 - i;
    }
    // пока количество удаляемых не 0
    while ((n > 0) && (i < 200))
    {
        // удаляется по одному элементу
        buf->removeAt(i);
        n--;
        i++;
    }
    counter++; //увеличение счетчика изменений
}

