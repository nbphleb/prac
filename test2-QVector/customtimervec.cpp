#include "customtimervec.h"

CustomTimerVec::CustomTimerVec()
{
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    vec = new QVector<TestObject>(200);

    connect(timer1, SIGNAL(timeout()), this, SLOT(getCounter()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(changeArray()));

    timer1->start(200); // каждые N мс обращение на изменение
    timer2->start(200); // каждые M мс изменяется массив

    //счетчики изменений
    counter = 0;
}

// функция внесения изменений в массив
void CustomTimerVec::changeArray()
{
    // генерация случайного значения для выбора действия. 0<=key<4
    short int key = QRandomGenerator::global()->bounded(4);
    //qDebug() << "Key = " << key;

    switch (key)
    {
     case 0: // добавление одного элемента
        if (vec->length() < 200) // проверка на заполненность
        {   // если vec не заполнен, добавляется один эл-т
            insertSingleElement();
        }
        break;

    case 1: // удаление одного элемента
        if (!vec->isEmpty()) // проверка на заполненность
        {   // если vec не пуст, удаляется один эл-т
            removeSingleElement();
        }
        break;

    case 2: // добавление списком
        if (vec->length() < 200) // проверка на заполненность
        {   //если vec не заполнен, добавляется несколько эл-тов
            insertMultipleElements();
        }
        break;

    case 3: // удаление списком
        if (!vec->isEmpty()) // проверка на заполненность
        {   // если vec не пуст, удаляется несколько эл-тов
            removeMultipleElements();
        }
        break;
    }
}

//функция обращения на изменения массива
void CustomTimerVec::getCounter()
{
    qDebug() << "Overall changes: " << counter;
}

// функция генерирации имени TestObject
QString CustomTimerVec::getRandomString()
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
TestObject CustomTimerVec::objectData()
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

//функция добавления одного элемента в vec
void CustomTimerVec::insertSingleElement()
{
    // выбор, куда именно добавится элемент 0 <= i <= 198; 199 индекс последнего эл-та
    short int i = QRandomGenerator::global()->bounded(199);
    // генерация значений TestObject
    TestObject obj = objectData();
    // добавление элемента
    if (i > vec->count()) // если i выходит за пределы vec
        vec->append(obj); // элемент добавляется в конец
    else // иначе добавляется в случайное место внутри vec
        vec->insert(i, obj);
    counter++; //увеличение счетчика изменений
}

//функция добавления нескольких элементов в vec
void CustomTimerVec::insertMultipleElements()
{
    // генерируется количество добавляемых объектов
    short int n = QRandomGenerator::global()->bounded(199);
    // если количество превысит длину списка, уменьшаем его до приемлимого
    if ((vec->length() + n) > 200)
    {
        n = 200 - vec->length();
    }
    // выбор, с какого индекса добавлять элементы 0 <= i <= 198; 199 индекс последнего эл-та
    short int i = QRandomGenerator::global()->bounded(198);
    // пока количество добавляемых эл-тов не 0
    while (n > 0 && i < 199)
    {
        // генерация значений TestObject
        TestObject obj = objectData();
        // добавление элемента
        if (i > vec->count()) // если i выходит за пределы vec
            vec->append(obj); // элемент добавляется в конец
        else // иначе добавляется в случайное место внутри vec
            vec->insert(i, obj);

        i++; // сдвиг для добавления по порядку
        n--; // уменьшение количества добавляемых эл-тов
    }
    counter++; //увеличение счетчика изменений
}

//функция удаления одного элемента из vec
void CustomTimerVec::removeSingleElement()
{
    // выбор, откуда именно удалится эл-т
    short int i = QRandomGenerator::global()->bounded(vec->length());
    // удаление элемента
    vec->removeAt(i);
    counter++; //увеличение счетчика изменений
}

//функция удаления нескольких элементов из vec
void CustomTimerVec::removeMultipleElements()
{
    // генерируется кол-во удаляемых объектов, не превышающее количество эл-тов
    short int n = QRandomGenerator::global()->bounded(vec->length());
    // выбор, с какого индекса начнется удаление
    short int i = QRandomGenerator::global()->bounded(vec->length()-1);
    // если с данного индекса меньше эл-тов, чем требуется удалить, уменьшаем кол-во удаляемых эл-тов
    if ( (n + i) > vec->length())
    {
        n = vec->length() - i;
    }
    // пока количество удаляемых не 0
    while ((n > 0) && (i < vec->length())-1)
    {
        // удаляется по одному элементу
        vec->removeAt(i);
        n--;
        i++;
    }
    counter++; //увеличение счетчика изменений
}


