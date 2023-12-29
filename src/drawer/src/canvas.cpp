#include "canvas.hpp"
#include <qnamespace.h>
#include <qpoint.h>
#include <qwidget.h>
#include <QPainter>
#include <QDebug>

Canvas::Canvas(QWidget* parent) : QWidget(parent) { setMouseTracking(true); }

void Canvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    painter.fillRect(this->rect(), Qt::white);
    painter.setPen(
        QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    // painter.setBrush(QColor(122, 163, 39));
    const QPoint* old_point = nullptr;
    for (const auto& p : paths) {
        if (old_point != nullptr) {
            painter.drawLine(*old_point, p);
        }
        old_point = &p;
        qDebug() << *old_point;
    }
    if (canvas_state == Drawing) {
        painter.drawLine(*old_point, cur_pos);
    }
}
void Canvas::mousePressEvent(QMouseEvent* event) {
    switch (event->button()) {
        case Qt::LeftButton:
            if (canvas_state == Drawing) {
                paths.append(event->pos());
                qDebug() << "Line to " << event->pos();
            } else {
                canvas_state = Drawing;
                paths.append(event->pos());
                qDebug() << "begain draw " << event->pos();
            }
            break;
        case Qt::RightButton:
            canvas_state = IDLE;
            qDebug() << "back to IDLE";
            break;
        case Qt::MiddleButton:
        default:
            break;
    }
    update();
}
void Canvas::mouseMoveEvent(QMouseEvent* event) {
    switch (canvas_state) {
        case IDLE:
            break;
        case Drawing:
            cur_pos = event->pos();
            qDebug() << "Mouse move " << cur_pos;
            break;
        case Selecting:
            break;
        default:
            break;
    }
    update();
}
void Canvas::mouseReleaseEvent(QMouseEvent* event) {}