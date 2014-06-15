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

#include <QtOpenGL>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);

    ui->graphicsView->setViewport(new QGLWidget());

    ui->graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing
                                      | QGraphicsView::DontClipPainter
                                      | QGraphicsView::DontSavePainterState);

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

    ui->graphicsView->setScene(scene);

    d_grid = new Grid(scene, this);

    d_initialized = false;

    connect(d_grid, SIGNAL(playerPointsChanged(Grid::Player, int)),
            SLOT(setPlayerPoints(enum Grid::Player, int)));

    connect(d_grid, SIGNAL(playerChanged(Grid::Player)),
            SLOT(changePlayer(enum Grid::Player)));

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(init()));
}

void
MainWindow::init()
{
    if (d_initialized) {
        enum QMessageBox::StandardButton buttom;
        buttom = QMessageBox::warning(this, "Restart?",
                                      "Do you really want restart game?",
                                      QMessageBox::Yes |QMessageBox::No);
        if (buttom  == QMessageBox::No) {
            return;
        }
        else {
            d_initialized = false;
        }
    }

    changePlayer(Grid::red);
    setPlayerPoints(Grid::red, 0);
    setPlayerPoints(Grid::blue, 0);

    if(ui->radioButton->isChecked())
        d_numBoxBySide = 3;
    else if(ui->radioButton_2->isChecked())
        d_numBoxBySide = 5;
    else
        d_numBoxBySide = 9;

    d_grid->init(d_numBoxBySide);
    ui->pushButton->setText("Restart");
    d_initialized = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::setPlayerPoints(enum Grid::Player currentPlayer, int points)
{
    if (currentPlayer == Grid::red)
        ui->label_11->setText(QString("%1").arg(points));
    else
        ui->label_12->setText(QString("%1").arg(points));

    if (d_initialized == false)
         return;

    /* Verifica se tem um ganhar do jogo. */
    if ((ui->label_11->text().toInt() + ui->label_12->text().toInt()) == pow(d_numBoxBySide, 2)) {
        int winner;
        if (ui->label_11->text().toInt() > ui->label_12->text().toInt())
            winner = 1;
        else
            winner = 2;
        QMessageBox::information(this, "Winner is...", QString("Player %1 win!!!").arg(winner));
        changePlayer((Grid::Player)winner);
    }
}

void
MainWindow::changePlayer(enum Grid::Player currentPlayer)
{
    if (currentPlayer == Grid::red) {
        ui->label_3->setEnabled(true);
        ui->label_11->setEnabled(true);
        ui->label_6->setEnabled(false);
        ui->label_12->setEnabled(false);
    } else {
        ui->label_3->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->label_6->setEnabled(true);
        ui->label_12->setEnabled(true);
    }
}

