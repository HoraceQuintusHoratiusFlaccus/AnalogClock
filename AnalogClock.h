#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include "RasterWindow.h"

class AnalogClock : public RasterWindow
{
public:
    AnalogClock();

protected:
    void timerEvent(QTimerEvent *) override;
    void Render(QPainter *) override;

private:
    int TimerId;
};

#endif // ANALOGCLOCK_H
