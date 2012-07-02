#ifndef FILESYSTEMHELPER_H
#define FILESYSTEMHELPER_H

#include <QObject>
#include <QStringList>

class FileSystemHelper : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemHelper(QObject *parent = 0);

    Q_INVOKABLE QString getWavFiles();
    
signals:
    
public slots:
    
};

#endif // FILESYSTEMHELPER_H
