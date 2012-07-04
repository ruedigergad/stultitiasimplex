/*
 *  Copyright 2012 Ruediger Gad
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

#include "filesystemhelper.h"

#include <QDir>
#include <QDebug>

#include "src/constants.h"

FileSystemHelper::FileSystemHelper(QObject *parent) :
    QObject(parent)
{
}

QString FileSystemHelper::getWavFiles(){
    qDebug() << "Listing files in: " << Constants::SOUNDS_DIR;

    QDir soundFileDir(Constants::SOUNDS_DIR);
    soundFileDir.setFilter(QDir::Files);
    soundFileDir.setSorting(QDir::Name);

//    QStringList filter;
//    filter.append("*.wav");

    QStringList files;
    files.append(soundFileDir.entryList());

    qDebug() << "Files: " << files;

    if(files.length() <= 0){
        return "";
    }

    QString ret;
    for(int i = 0; i < files.length() - 1; i++){
        ret += files.at(i) + "/";
    }
    ret += files.last();

    qDebug() << "Return: " << ret;
    return ret;
}
