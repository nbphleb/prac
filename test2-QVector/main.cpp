#include <QCoreApplication>

#include <customtimervec.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer::singleShot(14400000, &a, SLOT(quit()));

    CustomTimerVec cTimer;

    return a.exec();
}
