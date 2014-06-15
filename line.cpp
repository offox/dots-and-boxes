/******************************************************************************
 *   Dots and Boxes game.
 *   Copyright (C) 2012  Offox - Oswaldo F. Filho 
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include <QDebug>

#include "line.h"

Line::Line(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    setAcceptHoverEvents(true);

    d_brush.setStyle(Qt::NoBrush);
    d_brush.setColor(Qt::black);

    d_pen.setWidth(0);
    d_pen.setBrush(d_brush);

    d_state =  Line::hidden;

    d_timer = new QTimeLine(300, this);
    d_timer->setFrameRange(0, 10);

    d_animation = new QGraphicsItemAnimation(this);
    d_animation->setTimeLine(d_timer);

    int i;
    for (i = 0; i <= 10; ++i) {
        d_animation->setScaleAt(i / 10.0, i / 10.0 , i / 10.0);
    }

    d_animation->setItem(this);
}

void
Line::setLine(qreal x1, qreal y1, qreal x2, qreal y2, int lineWidth)
{
    d_lineWidth = lineWidth;
    d_line = QLineF(x1, y1, x2, y2);

    if (x1 == x2)
        d_rect = QRectF(x1 - d_lineWidth/2, y1, d_lineWidth, y2 - y1);
    else
        d_rect = QRectF(x1, y1 - d_lineWidth/2, x2 - x1, d_lineWidth);
}

enum Line::State
Line::state()
{
    return d_state;
}

void
Line::setLineState(enum State state)
{
    if (d_state == state)
        return;

    if (state == Line::hidden) {
        d_brush.setStyle(Qt::NoBrush);
        d_pen.setBrush(d_brush);
    } else if (state == Line::tested) {
        d_brush.setStyle(Qt::SolidPattern);
        d_brush.setColor(Qt::gray);
        d_pen.setBrush(d_brush);
    } else {
        d_brush.setStyle(Qt::SolidPattern);
        d_brush.setColor(Qt::black);
        d_pen.setBrush(d_brush);
        d_timer->start();
    }

    d_state = state;
    emit lineStateChanged(d_state, d_line);
}

void
Line::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);

    setLineState(Line::used);

    update();
}

void
Line::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    Q_UNUSED(event);

    if (d_state == Line::used)
        return;

    setLineState(Line::tested);

    update();
}

void
Line::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    Q_UNUSED(event);

    if (d_state == Line::used)
        return;

    setLineState(Line::hidden);

    update();
}

QRectF
Line::boundingRect() const
{
    return d_rect;
}

void
Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(d_brush);
    painter->setPen(d_pen);

    painter->drawRect(d_rect);
}

