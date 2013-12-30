/*
 *  Copyright 2010, 2012 Ruediger Gad
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
    QAbstractListModel(parent){
    qDebug("SoundFileList constructor...");

    m_roles[DescriptionRole] = "description";
    m_roles[FileNameRole] = "fileName";
    /*
     * Needed to make SectionScroller happy.
     * Take care to give the property used for naming the
     * section in the ListView the same name as in the
     * model element class (here Entry, see entry.h).
     */
    m_roles[CategoryRole] = "category";

    readFromCsv(Constants::SOUNDLIST_FILE);
    connect(this, SIGNAL(changed()), this, SLOT(save()));
}

SoundFileList::~SoundFileList() {
    qDebug("Entering SoundFileList::~SoundFileList().");
    writeToCsv(Constants::SOUNDLIST_FILE);
}


void SoundFileList::add(const SoundFile &file){
    beginResetModel();
    soundFiles.append(file);
    connect(&file, SIGNAL(changed()), this, SLOT(save()));
    endResetModel();
    emit changed();
}

const QList<SoundFile> * SoundFileList::getList(){
    return &soundFiles;
}

void SoundFileList::move(int from, int to){
    beginResetModel();
    if(to < 0){
        to = 0;
    }

    if(to > soundFiles.size() - 1){
        to = soundFiles.size() - 1;
    }

    soundFiles.move(from, to);
    endResetModel();
    emit moved(to);
}

void SoundFileList::readFromCsv(QString filename){
    qDebug("Reading sound file list.");
    beginResetModel();
    QFile file(filename);

    if(file.open(QFile::ReadOnly)){
        qDebug("Success opening list file for reading.");
        QTextStream stream(& file);

        QString data = stream.readLine();
        while(data != 0 && data.length() > 0){
            QStringList list = data.split(Constants::CSV_SEPARATOR);

            SoundFile sF;
            sF.setDescription(list.takeFirst());
            sF.setFileName(list.takeFirst());
            if(list.isEmpty()){
                sF.setCategory("Default");
            }else{
                sF.setCategory(list.takeFirst());
            }

            soundFiles.append(sF);
            connect(&sF, SIGNAL(changed()), this, SLOT(save()));

            data = stream.readLine();
        }

        file.close();
        qDebug("Finished reading. List size is: %d", rowCount());
    }
    endResetModel();
}

void SoundFileList::remove(SoundFile *file) {
    qDebug("Entering SoundFileList::remove()...");
    beginResetModel();
    disconnect(file, SIGNAL(changed()), this, SLOT(save()));
    soundFiles.removeOne(*file);
    endResetModel();
    emit changed();
}

void SoundFileList::reset() {
    qDebug("Resetting SoundFileList model.");
    beginResetModel();
    endResetModel();
    emit changed();
}

void SoundFileList::save() {
    writeToCsv(Constants::SOUNDLIST_FILE);
}

void SoundFileList::writeToCsv(QString filename) {
    qDebug("Writing list to file.");
    QFile file(filename);

    if(file.open(QFile::WriteOnly)){
        qDebug("Success opening file for writing.");
        QTextStream stream(& file);

        QList<SoundFile>::iterator iter;
        for(iter = soundFiles.begin(); iter != soundFiles.end(); iter++){
            SoundFile sF = *iter;
            stream << sF.getDescription() << Constants::CSV_SEPARATOR << sF.getFileName() << Constants::CSV_SEPARATOR << sF.getCategory() << "\n";
        }

        stream.flush();
        file.flush();
        file.close();
        qDebug("Finished writing list to file.");
    }
}

SoundFile* SoundFileList::at(int index){
    return new SoundFile(soundFiles.at(index));
}

QVariant SoundFileList::data(const QModelIndex &index, int role) const{
    if (index.row() < 0 || index.row() > soundFiles.count())
        return QVariant();

    const SoundFile file = soundFiles.at(index.row());
    if(role == DescriptionRole)
        return file.getDescription();
    else if (role == FileNameRole)
        return file.getFileName();
    else if (role == CategoryRole){
        return file.getCategory();
    }
    return QVariant();
}

int SoundFileList::rowCount(const QModelIndex &/*parent*/) const{
    return soundFiles.count();
}
