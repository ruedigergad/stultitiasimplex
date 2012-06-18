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

#include "soundfile.h"

SoundFile::SoundFile(QObject *parent, SoundFileList *list) :
    QObject(parent)
{
    this->list = list;
}

SoundFile::~SoundFile() {
    qDebug("Entering ~SoundFile::SoundFile()...");
    //FIXME: Clean up here..
}

QString SoundFile::getDescription(){
    return description;
}

QString SoundFile::getFileName(){
    return fileName;
}

SoundFileList *SoundFile::getList(){
    return list;
}

void SoundFile::setDescription(const QString desc){
    this->description = desc;
    emit changed();
}

void SoundFile::setFileName(const QString name){
    this->fileName = name;
    emit changed();
}
