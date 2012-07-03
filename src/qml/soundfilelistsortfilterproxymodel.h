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
    Q_INVOKABLE SoundFile* get(int index) { return soundFileList->get(index); }
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const {
        return soundFileList->rowCount(parent);
    }

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
