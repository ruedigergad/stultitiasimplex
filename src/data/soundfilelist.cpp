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

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QTextStream>

#include "soundfilelist.h"
#include "src/constants.h"

SoundFileList::SoundFileList(QObject *parent) :
    QObject(parent){
    soundFiles = new QList<SoundFile *>();

    readFromCsv(Constants::SOUNDLIST_FILE);
    connect(this, SIGNAL(changed()), this, SLOT(save()));
}

SoundFileList::~SoundFileList() {
    writeToCsv(Constants::SOUNDLIST_FILE);

    if(soundFiles != 0){
        while(! soundFiles->isEmpty()){
            SoundFile *file = soundFiles->takeFirst();
            qDebug() << "Deleting entry " << file->getDescription() << " from sound file list...";
            delete file;
        }
    }
}


void SoundFileList::add(SoundFile *file){
    soundFiles->append(file);
    connect(file, SIGNAL(changed()), this, SLOT(save()));
    emit changed();
}

const QList<SoundFile *> * SoundFileList::getList(){
    return soundFiles;
}

void SoundFileList::move(int from, int to){
    if(to < 0){
        to = 0;
    }

    if(to > soundFiles->size() - 1){
        to = soundFiles->size() - 1;
    }

    soundFiles->move(from, to);
    emit moved(to);
}

void SoundFileList::readFromCsv(QString filename){
    QFile file(filename);

    if(file.open(QFile::ReadOnly)){
        QTextStream stream(& file);

        QString data = stream.readLine();
        while(data != 0 && data.length() > 0){
            QStringList list = data.split(Constants::CSV_SEPARATOR);

            SoundFile *sF = new SoundFile();
            sF->setDescription(list.takeFirst());
            sF->setFileName(list.takeFirst());

            add(sF);

            data = stream.readLine();
        }

        file.close();
    }
}

void SoundFileList::remove(SoundFile *file){
    qDebug("Entering SoundFileList::remove()...");
    disconnect(file, SIGNAL(changed()), this, SLOT(save()));
    soundFiles->removeOne(file);
    emit changed();
}

void SoundFileList::save(){
    writeToCsv(Constants::SOUNDLIST_FILE);
}

void SoundFileList::writeToCsv(QString filename){
    QFile file(filename);

    if(file.open(QFile::WriteOnly)){
        QTextStream stream(& file);

        QList<SoundFile *>::iterator iter;
        for(iter = soundFiles->begin(); iter != soundFiles->end(); iter++){
            SoundFile *sF = *iter;
            stream << sF->getDescription() << Constants::CSV_SEPARATOR << sF->getFileName() << "\n";
        }

        stream.flush();
        file.flush();
        file.close();
    }
}
