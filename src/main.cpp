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


#if defined(MEEGO_EDITION_HARMATTAN) || defined(MER_EDITION_SAILFISH)
#include <QGuiApplication>
#include <QQuickView>
#include <QQuickWindow>
#include <QtQml>

#include "src/data/soundfile.h"
#include "src/data/soundfilelist.h"
#include "src/qml/qmlaudioplayer.h"
#include "src/qml/filesystemhelper.h"
#include "src/qml/qmlsettingsadapter.h"
#include "src/qml/soundfilelistsortfilterproxymodel.h"
#include "src/qml/qmlaudiorecorder.h"
#else
#include <QtGui/QApplication>
#include "src/ui/mainwindow.h"
#endif


#if defined(MEEGO_EDITION_HARMATTAN) || defined(MER_EDITION_SAILFISH)
Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QQuickWindow::setDefaultAlphaBuffer(true);

    QGuiApplication *app = new QGuiApplication(argc, argv);
    QQuickView *view = new QQuickView();

    qmlRegisterType<SoundFile>("harbour.stultitiasimplex", 1, 0, "SoundFile");
    qmlRegisterType<SoundFileList>("harbour.stultitiasimplex", 1, 0, "SoundFileList");
    qmlRegisterType<QmlAudioPlayer>("harbour.stultitiasimplex", 1, 0, "QmlAudioPlayer");
    qmlRegisterType<QmlAudioRecorder>("harbour.stultitiasimplex", 1, 0, "QmlAudioRecorder");
    qmlRegisterType<FileSystemHelper>("harbour.stultitiasimplex", 1, 0, "FileSystemHelper");
    qmlRegisterType<QmlSettingsAdapter>("harbour.stultitiasimplex", 1, 0, "QmlSettingsAdapter");
    qmlRegisterType<SoundFileListSortFilterProxyModel>("harbour.stultitiasimplex", 1, 0, "SoundFileListSortFilterProxyModel");

    view->setSource(QUrl("/usr/share/harbour-stultitiasimplex/qml/main.qml"));
    view->show();

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
