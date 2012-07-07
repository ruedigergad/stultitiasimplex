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

#ifndef SOUNDFILELISTSORTFILTERPROXYMODEL_H
#define SOUNDFILELISTSORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

#include "src/data/soundfile.h"
#include "src/data/soundfilelist.h"

class SoundFileListSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    // Needed to make SectionScroller happy.
    Q_PROPERTY(int count READ rowCount)

public:
    explicit SoundFileListSortFilterProxyModel(QObject *parent = 0);
    ~SoundFileListSortFilterProxyModel();

    // Needed to make SectionScroller happy.
    Q_INVOKABLE SoundFile* get(int index);
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const {
        return soundFileList->rowCount(parent);
    }

    Q_INVOKABLE void add(QString description, QString fileName, QString category);

signals:
    void changed();

public slots:
    void save();
    void reset();

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    SoundFileList *soundFileList;
};

#endif // SOUNDFILELISTSORTFILTERPROXYMODEL_H
