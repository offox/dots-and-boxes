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

#ifndef GRID_H
#define GRID_H

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QLineF>
#include <QList>
#include <QPen>
#include <QPointF>
#include <QTransform>
#include <QVector>

#include "line.h"

#define LINE_LENGTH         40
#define DOT_DIAMETER        10
#define DOT_RADIUS          (DOT_DIAMETER/2)
#define LINE_WIDTH          DOT_RADIUS
#define SCENE_WIDTH         400
#define SCENE_HEIGHT        400
#define DOT_COLOR           Qt::black
#define LINE_COLOR          Qt::black

class Grid : public QObject
{  
    Q_OBJECT
public:
    enum Player {
        red = 0x01,
        blue = 0x02
    };

    Grid(QGraphicsScene *, QObject *parent = 0);
    void init(int numBoxBySide);

private:
    enum Player d_currentPlayer;
    int d_bluePlayerPoints;
    int d_redPlayerPoints;
    QBrush d_brush;
    QGraphicsScene *d_scene;
    QVector< QVector< QGraphicsEllipseItem * > >d_dotsList;
    QList<Line *> d_linesList;
    QPen d_pen;
    QTransform d_transform;

    void changePlayer();
    void increasePlayerPoints();
    void drawBox(qreal, qreal);

private slots:
    void tryToDrawBoxes(Line::State, QLineF);

signals:
    void playerChanged(enum Grid::Player);
    void playerPointsChanged(enum Grid::Player, int);
};

#endif // GRID_H
