#include "filesystemhelper.h"

#include <QDir>
#include <QDebug>

FileSystemHelper::FileSystemHelper(QObject *parent) :
    QObject(parent)
{
}

QString FileSystemHelper::getWavFiles(){
    QString path = QDir::homePath() + "/.stultitiaSimplex/sounds";
    qDebug() << "Listing files in: " << path;

    QDir soundFileDir(path);
    soundFileDir.setFilter(QDir::Files);
    soundFileDir.setSorting(QDir::Name);

//    QStringList filter;
//    filter.append("*.wav");

    QStringList files;
    files.append(soundFileDir.entryList());

    qDebug() << "Files: " << files;

    if(files.length() <= 0){
        return "";
    }

    QString ret;
    for(int i = 0; i < files.length() - 1; i++){
        ret += files.at(i) + "/";
    }
    ret += files.last();

    qDebug() << "Return: " << ret;
    return ret;
}
