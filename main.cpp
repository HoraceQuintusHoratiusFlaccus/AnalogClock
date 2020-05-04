#include "RasterWindow.h"
#include "AnalogClock.h"

#include <QtGui>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    AnalogClock Clock;
    Clock.show();

    return a.exec();
}
