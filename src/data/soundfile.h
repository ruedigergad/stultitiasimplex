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

    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString category READ getCategory WRITE setCategory NOTIFY categoryChanged)

public:
    SoundFile(QObject *parent = 0);
    SoundFile(const SoundFile &obj, QObject *parent = 0);

    SoundFile& operator = (const SoundFile &e);
    bool operator == (const SoundFile &e);

    QString getDescription() const;
    QString getFileName() const;
    QString getCategory() const;

    void setDescription(const QString desc);
    void setFileName(const QString name);
    void setCategory(const QString category);

signals:
    void changed();
    void descriptionChanged(QString);
    void fileNameChanged(QString);
    void categoryChanged(QString);

public slots:

private:
    QString category;
    QString description;
    QString fileName;

};

bool soundFileCompare(const SoundFile &e1, const SoundFile &e2);

#endif // SOUNDFILE_H
