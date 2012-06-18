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

#ifndef SOUNDFILE_H
#define SOUNDFILE_H

#include <QObject>
#include "soundfilelist.h"

class SoundFileList;

class SoundFile : public QObject
{
    Q_OBJECT
public:
    explicit SoundFile(QObject *parent = 0, SoundFileList *list = 0);
    ~SoundFile();

    QString getDescription();
    QString getFileName();
    SoundFileList *getList();

    void setDescription(const QString desc);
    void setFileName(const QString name);

signals:
    void changed();

public slots:

private:
    QString description;
    QString fileName;
    SoundFileList *list;

};

#endif // SOUNDFILE_H
