#include "AnalogClock.h"

AnalogClock::AnalogClock()
{
    setTitle("Analog Clock");
    resize(200, 200);

    /* 1 Hour: 10, 1 Minute: 100, 1 Second: 1000 */
    TimerId = startTimer(1000);
}

void AnalogClock::timerEvent(QTimerEvent * Event)
{
    if (Event->timerId() == TimerId)
        RenderLater();
}

void AnalogClock::Render(QPainter * Painter)
{
    static const QPoint HourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    static const QPoint MinuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    /* 191 means that it's 75% opaque */
    QColor HourColor(127, 0, 127);
    QColor MinuteColor(0, 127, 127, 191);

    /* Minimize broken patterns at low resolution */
    Painter->setRenderHint(QPainter::Antialiasing);

    /* Move the origin to the center of the window */
    Painter->translate(width() / 2, height() / 2);

    /*
     * The scale operation ensures that
     * the drawing operations are scaled
     * to fit within the window
    */
    int Side = qMin(width(), height());
    Painter->scale(Side / 200.0, Side / 200.0);

    Painter->setPen(Qt::NoPen);
    Painter->setBrush(HourColor);

    QTime Time = QTime::currentTime();

    Painter->save();
    Painter->rotate(30.0 * (Time.hour() + Time.minute() / 60.0));
    Painter->drawConvexPolygon(HourHand, 3);
    Painter->restore();

    Painter->setPen(HourColor);

    for (int i = 0; i < 12; ++i)
    {
        Painter->drawLine(88, 0, 96, 0);
        Painter->rotate(30.0);
    }

    Painter->setPen(Qt::NoPen);
    Painter->setBrush(MinuteColor);

    Painter->save();
    Painter->rotate(6.0 * (Time.minute() + Time.second() / 60.0));
    Painter->drawConvexPolygon(MinuteHand, 3);
    Painter->restore();

    Painter->setPen(MinuteColor);

    for (int j = 0; j < 60; ++j)
    {
        /*
         * Skip multiples of 5
         * to avoid drawing minute markers
         * on top of hour markers
        */
        if ((j % 5) != 0)
            Painter->drawLine(92, 0, 96, 0);
       Painter->rotate(6.0);
    }
}
