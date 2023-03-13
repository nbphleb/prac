#include "changestimer.h"

ChangesTimer::ChangesTimer()
{
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    list = new QList<TestObject>;

    connect(timer1, SIGNAL(timeout()), this, SLOT(getCounter()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(changeArray()));

    timer1->start(200); // каждые N мс обращение на изменение
    timer2->start(200); // каждые M изменяется массив

    //счетчики изменений
    counter = 0;
}

//функция изменения массива
void ChangesTimer::changeArray()
{
    // генерация случайного значения для выбора действия. 0<=key<4
    short int key = QRandomGenerator::global()->bounded(4);
    //qDebug() << "Key = " << key;

    switch (key)
    {
     case 0: // добавление одного элемента
        if (list->length() < 200) // проверка на заполненность
        {   // если list не заполнен, добавляется один эл-т
            insertSingleElement();
        }
        break;

    case 1: // удаление одного элемента
        if (!list->isEmpty()) // проверка на заполненность
        {   // если list не пуст, удаляется один эл-т
            removeSingleElement();
        }
        break;

    case 2: // добавление списком
        if (list->length() < 200) // проверка на заполненность
        {   //если list не заполнен, добавляется несколько эл-тов
            insertMultipleElements();
        }
        break;

    case 3: // удаление списком
        if (!list->isEmpty()) // проверка на заполненность
        {   // если list не пуст, удаляется несколько эл-тов
            removeMultipleElements();
        }
        break;
    }
}

//функция обращения на количество изменений
void ChangesTimer::getCounter()
{
    qDebug() << "Overall changes: " << counter;
}

// функция генерирации имени TestObject
QString ChangesTimer::getRandomString()
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
TestObject ChangesTimer::objectData()
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

//Функция добавления одного эл-та
void ChangesTimer::insertSingleElement()
{
    // выбор, куда именно добавится элемент 0 <= i <= 198; 199 индекс последнего эл-та
    short int i = QRandomGenerator::global()->bounded(199);
    // генерация значений TestObject
    TestObject obj = objectData();
    // добавление элемента
    if (i > list->count()) // если i выходит за пределы list
        list->append(obj); // элемент добавляется в конец
    else // иначе добавляется в случайное место внутри list
        list->insert(i, obj);
    counter++; //увеличение счетчика изменений
}

//Функция добавления нескольких эл-тов
void ChangesTimer::insertMultipleElements()
{
    // генерируется количество добавляемых объектов
    short int n = QRandomGenerator::global()->bounded(199);
    // если количество превысит длину списка, уменьшаем его до приемлимого
    if ((list->length() + n) > 200)
    {
        n = 200 - list->length();
    }
    // выбор, с какого индекса добавлять элементы 0 <= i <= 198; 199 индекс последнего эл-та
    short int i = QRandomGenerator::global()->bounded(198);
    // пока количество добавляемых эл-тов не 0
    while (n > 0 && i < 199)
    {
        // генерация значений TestObject
        TestObject obj = objectData();
        // добавление элемента
        if (i > list->count()) // если i выходит за пределы list
            list->append(obj); // элемент добавляется в конец
        else // иначе добавляется в случайное место внутри list
            list->insert(i, obj);

        i++; // сдвиг для добавления по порядку
        n--; // уменьшение количества добавляемых эл-тов
    }
    counter++; //увеличение счетчика изменений
}

//Функция удаления одного эл-та
void ChangesTimer::removeSingleElement()
{
    // выбор, откуда именно удалится эл-т
    short int i = QRandomGenerator::global()->bounded(list->length());
    // удаление элемента
    list->removeAt(i);
    counter++; //увеличение счетчика изменений
}

//Функция удаления нескольких эл-тов
void ChangesTimer::removeMultipleElements()
{
    // генерируется кол-во удаляемых объектов, не превышающее количество эл-тов
    short int n = QRandomGenerator::global()->bounded(list->length());
    // выбор, с какого индекса начнется удаление
    short int i = QRandomGenerator::global()->bounded(list->length()-1);
    // если с данного индекса меньше эл-тов, чем требуется удалить, уменьшаем кол-во удаляемых эл-тов
    if ( (n + i) > list->length())
    {
        n = list->length()-1 - i;
    }
    // пока количество удаляемых не 0
    while ((n > 0) && (i < list->length()-1))
    {
        // удаляется по одному элементу
        list->removeAt(i);
        n--;
        i++;
    }
    counter++; //увеличение счетчика изменений
}

