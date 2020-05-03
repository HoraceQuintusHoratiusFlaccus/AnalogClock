#ifndef RASTERWINDOW_H
#define RASTERWINDOW_H

#include <QtGui>

class RasterWindow : public QWindow
{
    Q_OBJECT
public:
    explicit RasterWindow(QWindow * parent = 0);

    virtual void Render(QPainter *);

public slots:
    void RenderLater();
    void RenderNow();

protected:
    bool event(QEvent *) override;

    void resizeEvent(QResizeEvent *) override;
    void exposeEvent(QExposeEvent *) override;

private:
    QBackingStore * BackingStore;
};

#endif // RASTERWINDOW_H
