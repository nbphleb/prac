#include "customtimerque.h"

CustomTimerQue::CustomTimerQue()
{
    que = new QQueue<TestObject>;
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1, SIGNAL(timeout()), this, SLOT(getCounter()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(changeArray()));

    timer1->start(200); // каждые N мс обращение на изменение
    timer2->start(200); // каждые M мс изменяется массив

    //счетчики изменений
    counter = 0;
}

// функция внесения изменений в массив
void CustomTimerQue::changeArray()
{
    // генерация случайного значения для выбора действия. 0<=key<4
    short int key = QRandomGenerator::global()->bounded(4);
    //qDebug() << "Key = " << key;

    switch (key)
    {
     case 0: // добавление одного элемента
        if (que->length() < 200) // проверка на заполненность
        {   // если vec не заполнен, добавляется один эл-т
            enqueSingleElement();
        }
        break;

    case 1: // удаление одного элемента
        if (!que->isEmpty()) // проверка на заполненность
        {   // если vec не пуст, удаляется один эл-т
            dequeSingleElement();
        }
        break;

    case 2: // добавление списком
        if (que->length() < 200) // проверка на заполненность
        {   //если vec не заполнен, добавляется несколько эл-тов
            enqueMultipleElements();
        }
        break;

    case 3: // удаление списком
        if (!que->isEmpty()) // проверка на заполненность
        {   // если vec не пуст, удаляется несколько эл-тов
            dequeMultipleElements();
        }
        break;
    }
}

//функция обращения на изменения массива
void CustomTimerQue::getCounter()
{
    qDebug() << "Overall changes: " << counter;
}

// функция генерирации имени TestObject
QString CustomTimerQue::getRandomString()
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
TestObject CustomTimerQue::objectData()
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

//функция добавления одного элемента в очередь
void CustomTimerQue::enqueSingleElement()
{
    // генерация значений TestObject
    TestObject obj = objectData();
    // добавление элемента
    que->enqueue(obj);
    counter++; //увеличение счетчика изменений
}

//функция добавления нескольких элементов в очередь
void CustomTimerQue::enqueMultipleElements()
{
    // генерируется количество добавляемых объектов
    short int n = QRandomGenerator::global()->bounded(199);
    // если количество превысит длину списка, уменьшаем его до приемлимого
    if ((que->length() + n) > 200)
    {
        n = 200 - que->length();
    }

    // пока количество добавляемых эл-тов не 0
    while (n > 0)
    {
        // генерация значений TestObject
        TestObject obj = objectData();
        // добавление элемента
        que->enqueue(obj);
        n--; // уменьшение количества добавляемых эл-тов
    }
    counter++; //увеличение счетчика изменений
}

//функция удаления одного элемента из очереди
void CustomTimerQue::dequeSingleElement()
{
    //удаление элемента
    que->dequeue();
    counter++; //увеличение счетчика изменений
}

//функция удаления нескольких элементов из очереди
void CustomTimerQue::dequeMultipleElements()
{
    // генерируется кол-во удаляемых объектов, не превышающее количество эл-тов
    short int n = QRandomGenerator::global()->bounded(que->length());
    while (n > 0)
    {
        // удаляется по одному элементу
        que->dequeue();
        n--;
        //counter[0]++; //увеличение счетчика изменений
    }
    counter++; //увеличение счетчика изменений
}
