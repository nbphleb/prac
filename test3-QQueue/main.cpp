#include <QCoreApplication>

#include <customtimerque.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer::singleShot(14400000, &a, SLOT(quit()));

    CustomTimerQue cTimer;

    return a.exec();
}
