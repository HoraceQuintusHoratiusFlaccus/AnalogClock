#include "AnalogClock.h"

AnalogClock::AnalogClock()
{
    setTitle("Analog Clock");
    resize(200, 200);

    TimerId = startTimer(1000);
}

void AnalogClock::timerEvent(QTimerEvent * Event)
{
    /* Rendering Asynchronously */
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
    static const QPoint SecondHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor HourColor(0, 100, 0);
    QColor MinuteColor(153, 204, 0, 191);
    QColor SecondColor(46, 139, 87, 163);

    Painter->setRenderHint(QPainter::Antialiasing);

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
    /* 1 Hour: 30.0 degrees, 12 Hours: 360.0 degrees */
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
    /* 1 Minute: 6.0 degrees, 5 Minutes: 30.0 degrees */
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

    Painter->setPen(Qt::NoPen);
    Painter->setBrush(SecondColor);

    Painter->save();
    Painter->rotate(6.0 * Time.second());
    Painter->drawConvexPolygon(SecondHand, 3);
    Painter->restore();

    Painter->setPen(SecondColor);
}
