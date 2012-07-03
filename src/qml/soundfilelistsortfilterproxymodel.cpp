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
