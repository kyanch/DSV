#pragma once

#include <qline.h>
#include <qpainterpath.h>
#include <qpoint.h>
#include <qtransform.h>
#include <qwidget.h>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLine>

/*
 * Canvas state：
 * IDLE -> Drawing -> IDLE
 *
 *
 */
enum CanvasState { IDLE, Drawing, Selecting };
enum PaintTool { None, LineSeg, Circle };

class Canvas : public QWidget {
   private:
    Q_OBJECT
   protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

   public:
    Canvas(QWidget* parent = nullptr);

   private:
    void draw_item();
    void select();

   private:
    QPoint cur_pos;
    CanvasState canvas_state;
    QVector<QPoint> paths;
    QVector<QPainterPath> ondrawing_path;
};