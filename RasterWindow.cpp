#include "RasterWindow.h"

RasterWindow::RasterWindow(QWindow * Parent)
    : QWindow(Parent)
    , BackingStore(new QBackingStore(this))
{
    setGeometry(100, 100, 300, 200);
}

void RasterWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed())
        RenderNow();
}

void RasterWindow::resizeEvent(QResizeEvent * resizeEvent)
{
    BackingStore->resize(resizeEvent->size());
}

void RasterWindow::RenderNow()
{
    if (!isExposed())
        return;

    QRect Rect(0, 0, width(), height());
    BackingStore->beginPaint(Rect);

    QPaintDevice * Device = BackingStore->paintDevice();
    QPainter Painter(Device);

    Painter.fillRect(0, 0, width(), height(), QGradient::LogicalMode);
    Render(&Painter);
    Painter.end();

    BackingStore->endPaint();
    BackingStore->flush(Rect);
}

void RasterWindow::Render(QPainter * Painter)
{
    /* Ex) Painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("QWindow")); */
}

void RasterWindow::RenderLater()
{
    requestUpdate();
}

bool RasterWindow::event(QEvent * Event)
{
    if (Event->type() == QEvent::UpdateRequest)
    {
        RenderNow();
        return true;
    }

    return QWindow::event(Event);
}
