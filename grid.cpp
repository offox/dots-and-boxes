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

#include <math.h>

#include <QDebug>

#include "grid.h"

Grid::Grid(QGraphicsScene *scene, QObject *parent) :
    QObject(parent)
{
    d_scene = scene;
    d_scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
}

void
Grid::init(int numBoxBySide)
{
    QList<QGraphicsItem *> listItens = d_scene->items();
    for(int i = 0; i < listItens.size(); i ++) {
       d_scene->removeItem(listItens.at(i));
       listItens.at(i)->~QGraphicsItem();
    }

    d_dotsList.clear();
    d_linesList.clear();
    d_transform.reset();

    d_currentPlayer = Grid::red;
    d_redPlayerPoints = 0;
    d_bluePlayerPoints = 0;

    /* Desenha os dots. */
    d_brush.setColor(DOT_COLOR);
    d_brush.setStyle(Qt::SolidPattern);
    d_pen.setBrush(d_brush);

    d_transform.translate(-DOT_RADIUS, -DOT_RADIUS);

    int marginTB = (SCENE_HEIGHT - (LINE_LENGTH * numBoxBySide)) / 2;
    int marginRL = (SCENE_WIDTH - (LINE_LENGTH * numBoxBySide)) / 2;

    for(int row = 0; row <= numBoxBySide; row++) {
        d_dotsList.append(QVector<QGraphicsEllipseItem *>());
        for(int col = 0; col <= numBoxBySide ; col++) {
            d_dotsList[d_dotsList.size()-1].append(d_scene->addEllipse(0, 0, DOT_DIAMETER, DOT_DIAMETER, d_pen, d_brush));
            d_dotsList[row][col]->setTransform(d_transform);
            d_dotsList[row][col]->setPos((LINE_LENGTH * col) + marginTB,
                                         (LINE_LENGTH * row) + marginRL);
        }
    }

    /* Desenha as linhas horizontais com base na posição dos dots. */
    d_transform.translate(DOT_RADIUS, DOT_RADIUS);

    for (int row = 0; row < d_dotsList.size(); row++) {
        for(int col = 0; col < d_dotsList[row].size()-1; col++) {

         d_linesList.append(new Line());
         d_linesList.last()->setLine(d_dotsList[row][col]->x(),
                                  d_dotsList[row][col]->y(),
                                  d_dotsList[row][col + 1]->x(),
                                  d_dotsList[row][col + 1]->y(),
                                  LINE_WIDTH);
         d_linesList.last()->setTransform(d_transform);
         d_scene->addItem(d_linesList.last());
         connect(d_linesList.last(), SIGNAL(lineStateChanged(Line::State, QLineF)),
                                    SLOT(tryToDrawBoxes(Line::State, QLineF)));
        }
    }

    /* Desenha as linhas verticais com base na posição dos dots. */
    for (int col = 0; col < d_dotsList[0].size(); col++) {
        for(int row = 0; row < d_dotsList.size()-1; row++) {
            d_linesList.append(new Line());
            d_linesList.last()->setLine(d_dotsList[row][col]->x(),
                                     d_dotsList[row][col]->y(),
                                     d_dotsList[row + 1][col]->x(),
                                     d_dotsList[row + 1][col]->y(),
                                     LINE_WIDTH);
            d_linesList.last()->setTransform(d_transform);
            d_scene->addItem(d_linesList.last());
            connect(d_linesList.last(), SIGNAL(lineStateChanged(Line::State, QLineF)),
                                       SLOT(tryToDrawBoxes(Line::State, QLineF)));
        }
    }
}

void
Grid::tryToDrawBoxes(Line::State lineState, QLineF refLine )
{
    if (lineState != Line::used)
        return;

    qreal refX = refLine.x1();
    qreal refY = refLine.y1();

    d_transform.reset();
    d_transform.translate(DOT_RADIUS, DOT_RADIUS);

    QGraphicsEllipseItem circle;
    QList<QGraphicsItem *> cLinesList;

    circle.setRect(refX, refY, LINE_LENGTH, LINE_LENGTH);

    cLinesList = d_scene->collidingItems(&circle);

    int numCLines1 = 0;
    for(int i = 0; i < cLinesList.size(); i++) {
        if (static_cast<Line *>(cLinesList.at(i))->state() == Line::used)
            numCLines1++;
    }

    if( numCLines1 == 4) {
        drawBox(refX, refY);
    }

    if (refLine.y1() == refLine.y2())
        refY = refLine.y1() - LINE_LENGTH;
    else
        refX = refLine.x1() - LINE_LENGTH;

    circle.setRect(refX, refY, LINE_LENGTH, LINE_LENGTH);

    cLinesList = d_scene->collidingItems(&circle);

    int numCLines2 = 0;
    for(int i = 0; i < cLinesList.size(); i++) {
        if (static_cast<Line *>(cLinesList.at(i))->state() == Line::used)
            numCLines2++;
    }

    if(numCLines2 == 4) {
        drawBox(refX, refY);
    }

    if (numCLines1 != 4 && numCLines2 != 4)
        changePlayer();
}

void
Grid::drawBox(qreal refX, qreal refY)
{
    if (d_currentPlayer == blue)
        d_brush.setColor(QColor(Qt::blue));
    else
        d_brush.setColor(QColor(Qt::red));

    d_brush.setStyle(Qt::SolidPattern);
    d_pen.setWidth(0);
    d_pen.setBrush(d_brush);

    d_scene->addRect(refX + LINE_WIDTH,
            refY + LINE_WIDTH,
            LINE_LENGTH - LINE_WIDTH * 2,
            LINE_LENGTH - LINE_WIDTH * 2,
            d_pen, d_brush);

    increasePlayerPoints();
}

void
Grid::changePlayer()
{
    if (d_currentPlayer == Grid::red)
        d_currentPlayer = Grid::blue;
    else
        d_currentPlayer = Grid::red;

    emit playerChanged(d_currentPlayer);
}

void
Grid::increasePlayerPoints()
{
    if (d_currentPlayer == Grid::red) {
        d_redPlayerPoints++;
        emit playerPointsChanged(d_currentPlayer, d_redPlayerPoints);
    } else {
        d_bluePlayerPoints++;
        emit playerPointsChanged(d_currentPlayer, d_bluePlayerPoints);
    }
}
