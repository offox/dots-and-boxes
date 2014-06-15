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

#ifndef LINE_H
#define LINE_H

#include <QBrush>
#include <QGraphicsItemAnimation>
#include <QGraphicsObject>
#include <QLineF>
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QTimeLine>

class Line : public QGraphicsObject
{
    Q_OBJECT

public:

    enum State {
        hidden,
        tested,
        used
    };

    explicit Line(QGraphicsItem *parent = 0);
    void setLine(qreal x1, qreal y1, qreal x2, qreal y2, int lineWidth);
    void setLineState(enum Line::State);
    enum Line::State state();

private:

    enum State d_state;
    int d_lineWidth;
    QBrush d_brush;
    QGraphicsItemAnimation *d_animation;
    QPen d_pen;
    QRectF d_rect;
    QLineF d_line;
    QTimeLine *d_timer;

protected:

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual QRectF boundingRect() const;

signals:

    void lineStateChanged(enum Line::State, QLineF);
};

#endif // LINE_H
