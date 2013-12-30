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

#include "soundfilelistsortfilterproxymodel.h"

SoundFileListSortFilterProxyModel::SoundFileListSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    soundFileList = new SoundFileList();
    connect(soundFileList, SIGNAL(changed()), this, SIGNAL(changed()));
    setSourceModel(soundFileList);

    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(SoundFileList::DescriptionRole);
    setDynamicSortFilter(true);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    sort(0, Qt::AscendingOrder);
}

SoundFileListSortFilterProxyModel::~SoundFileListSortFilterProxyModel(){
    qDebug("Entering SoundFileListSortFilterProxyModel::~SoundFileListSortFilterProxyModel().");
    delete soundFileList;
}

void SoundFileListSortFilterProxyModel::save(){
    soundFileList->save();
}

void SoundFileListSortFilterProxyModel::reset(){
    soundFileList->reset();
}

bool SoundFileListSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftCategory = soundFileList->data(left, SoundFileList::CategoryRole);
    QVariant righCategory = soundFileList->data(right, SoundFileList::CategoryRole);

    // If both are in the same category sort by name
    if (leftCategory == righCategory) {
        QVariant leftDescription = soundFileList->data(left, SoundFileList::DescriptionRole);
        QVariant righDescription = soundFileList->data(right, SoundFileList::DescriptionRole);
        return QString::localeAwareCompare(leftDescription.toString(), righDescription.toString()) < 0;
    }

    // Else sort by category
    return QString::localeAwareCompare(leftCategory.toString(), righCategory.toString()) < 0;
}

SoundFile* SoundFileListSortFilterProxyModel::get(int index){
    QModelIndex idx = this->index(index, 0);
    QModelIndex srcIdx = mapToSource(idx);

    return (srcIdx.row() >= 0 && srcIdx.row() < sourceModel()->rowCount())
            ? soundFileList->get(srcIdx.row())
            : soundFileList->get(index);
}

void SoundFileListSortFilterProxyModel::add(QString description, QString fileName, QString category){
    SoundFile *soundFile = new SoundFile();

    soundFile->setCategory(category);
    soundFile->setDescription(description);
    soundFile->setFileName(fileName);

    soundFileList->add(soundFile);
}

void SoundFileListSortFilterProxyModel::remove(int index) {
    QModelIndex idx = this->index(index, 0);
    QModelIndex srcIdx = mapToSource(idx);

    soundFileList->remove(srcIdx.row());
}

void SoundFileListSortFilterProxyModel::update(int index, QString description, QString fileName, QString category) {
    QModelIndex idx = this->index(index, 0);
    QModelIndex srcIdx = mapToSource(idx);

    soundFileList->update(srcIdx.row(), description, fileName, category);
}
