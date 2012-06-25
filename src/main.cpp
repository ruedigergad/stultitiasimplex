/*
 *  Copyright 2010 Ruediger Gad
 *
 *  This file is part of StultitiaSimplex.
 *
 *  StultitiaSimplex is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  StultitiaSimplex is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with StultitiaSimplex.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGui/QApplication>

#ifndef MEEGO_EDITION_HARMATTAN
#include "src/ui/mainwindow.h"
#endif

int main(int argc, char *argv[])
{
#ifdef MEEGO_EDITION_HARMATTAN
    return 0;
#else
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
#endif
}
