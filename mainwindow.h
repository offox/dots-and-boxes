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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "grid.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool d_initialized;
    int d_numBoxBySide;
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    Grid *d_grid;


private slots:
    void changePlayer(enum Grid::Player);
    void setPlayerPoints(enum Grid::Player, int);
    void init();
};

#endif // MAINWINDOW_H
