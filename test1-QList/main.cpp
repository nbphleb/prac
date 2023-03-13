#include <QCoreApplication>

#include <changestimer.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer::singleShot(14400000, &a, SLOT(quit()));

    ChangesTimer cTimer;

    return a.exec();

}
