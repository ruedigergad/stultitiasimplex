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

#ifndef SOUNDFILELIST_H
#define SOUNDFILELIST_H

#include <QObject>
#include "soundfile.h"

class SoundFile;

class SoundFileList : public QObject
{
    Q_OBJECT
public:
    explicit SoundFileList(QObject *parent = 0);
    ~SoundFileList();

    void add(SoundFile *file);
    const QList<SoundFile *> *getList();
    void move(int from, int to);
    void remove(SoundFile *file);

signals:
    void changed();
    void moved(int to);

public slots:
    void save();

private:
    QList<SoundFile *> *soundFiles;
    void readFromCsv(QString filename);
    void writeToCsv(QString filename);
};

#endif // SOUNDFILELIST_H
