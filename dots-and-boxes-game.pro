###############################################################################
#   Dots and Boxes game.
#   Copyright (C) 2012  Offox - Oswaldo F. Filho 
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
###############################################################################

#-------------------------------------------------
#
# Project created by QtCreator 2012-04-05T11:18:50
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = dots-and-boxes-game
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        grid.cpp \
        line.cpp \

HEADERS  += mainwindow.h \
            grid.h \
            line.h \

FORMS    += mainwindow.ui
