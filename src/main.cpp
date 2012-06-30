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

#ifdef MEEGO_EDITION_HARMATTAN
#include <applauncherd/MDeclarativeCache>
#include <QtDeclarative>
#else
#include "src/ui/mainwindow.h"
#endif


#ifdef MEEGO_EDITION_HARMATTAN
Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication *app = MDeclarativeCache::qApplication(argc, argv);
    QDeclarativeView *view = MDeclarativeCache::qDeclarativeView();

//    qmlRegisterType<NodeListModel>("qtodo", 1, 0, "NodeListModel");
//    qmlRegisterType<ToDoStorage>("qtodo", 1, 0, "ToDoStorage");

    view->setSource(QUrl("/opt/stultitiasimplex/qml/main.qml"));
    view->showFullScreen();

//    view.setResizeMode(QDeclarativeView::SizeRootObjectToView);
//    view.resize(500, 400);
//    view.show();
    return app->exec();
}
#else
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
#endif
