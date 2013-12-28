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

#ifndef SOUNDFILELIST_H
#define SOUNDFILELIST_H

#include <QObject>
#include <QAbstractListModel>
#include "soundfile.h"

class SoundFile;

class SoundFileList : public QAbstractListModel
{
    Q_OBJECT
    // Needed to make SectionScroller happy.
    Q_PROPERTY(int count READ rowCount)
public:
    enum SoundFileRoles {
        DescriptionRole = Qt::UserRole + 1,
        FileNameRole = Qt::UserRole + 2,
        CategoryRole = Qt::UserRole + 3
    };

    explicit SoundFileList(QObject *parent = 0);
    ~SoundFileList();

    void add(SoundFile *file);
    const QList<SoundFile *> *getList();
    void move(int from, int to);
    void remove(SoundFile *file);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE SoundFile* at(int index);
    // Needed to make SectionScroller happy.
    Q_INVOKABLE SoundFile* get(int index) { return at(index); }

    virtual QHash<int, QByteArray> roleNames() const { return m_roles; }

signals:
    void changed();
    void moved(int to);

public slots:
    void save();
    void reset();

private:
    QList<SoundFile *> *soundFiles;
    void readFromCsv(QString filename);
    void writeToCsv(QString filename);

    QHash<int, QByteArray> m_roles;
};

#endif // SOUNDFILELIST_H
