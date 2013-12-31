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

#ifndef QMLSETTINGSADAPTER_H
#define QMLSETTINGSADAPTER_H

#include <QObject>
#include <QVariant>

class QmlSettingsAdapter : public QObject
{
    Q_OBJECT
public:
    explicit QmlSettingsAdapter(QObject *parent = 0);

    Q_INVOKABLE QVariant get(QString key);
    Q_INVOKABLE int getInt(QString key);
    Q_INVOKABLE bool getBool(QString key);
    Q_INVOKABLE QString getString(QString kex);
    
signals:
    void settingsChanged();
    
public slots:
    void set(QString key, QVariant val);
    
};

#endif // QMLSETTINGSADAPTER_H
