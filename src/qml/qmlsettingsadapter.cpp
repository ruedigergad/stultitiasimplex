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

#include "qmlsettingsadapter.h"
#include <QSettings>

QmlSettingsAdapter::QmlSettingsAdapter(QObject *parent) :
    QObject(parent)
{
    if (getString("cover_action_1_description").isNull()) {
        set("cover_action_1_description", "");
    }
    if (getString("cover_action_1_file_name").isNull()) {
        set("cover_action_1_file_name", "");
    }
    if (getString("cover_action_2_description").isNull()) {
        set("cover_action_2_description", "");
    }
    if (getString("cover_action_2_file_name").isNull()) {
        set("cover_action_2_file_name", "");
    }
}

QVariant QmlSettingsAdapter::get(QString key){
    QSettings settings;
    return settings.value(key);
}

bool QmlSettingsAdapter::getBool(QString key){
    return get(key).toBool();
}

int QmlSettingsAdapter::getInt(QString key){
    return get(key).toInt();
}

void QmlSettingsAdapter::set(QString key, QVariant val){
    QSettings settings;
    settings.setValue(key, val);
    settings.sync();
    emit settingsChanged();
}

QString QmlSettingsAdapter::getString(QString key) {
    return get(key).toString();
}
