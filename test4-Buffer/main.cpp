#include <QCoreApplication>

#include <customtimerbuf.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer::singleShot(14400000, &a, SLOT(quit()));

    CustomTimerBuf cTimer;

    return a.exec();
}
