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

import QtQuick 1.1
import com.nokia.meego 1.0

Sheet{
    id: settingsSheet

    anchors.fill: parent
    visualParent: mainPage

    onStatusChanged: {
        if(status === DialogStatus.Opening){
            console.log("Opening...")

            volumeOverride.checked = qmlSettingsAdapter.getBool("sound/volume_override")
            volume.value = qmlSettingsAdapter.getInt("sound/volume")
        }
    }

    acceptButtonText: "OK"
    rejectButtonText: "Cancel"

    content: Flickable {
        anchors.fill: parent
        contentHeight: sheetContent.height

        Item {
            id: sheetContent

            anchors{top: parent.top; left: parent.left; right: parent.right; margins: 15}

            Item{
                id: volumeOverrideItem
                anchors{top: parent.top; left: parent.left; right: parent.right}
                height: volumeOverride.height

                Text{
                    anchors.left: parent.left
                    text: "Override Volume:"
                    font.pixelSize: 30
                }
                Switch{
                    anchors.right: parent.right
                    id: volumeOverride
                }
            }
            Item{
                anchors{top: volumeOverrideItem.bottom; topMargin: 12; left: parent.left; right: parent.right}

                Text{
                    id: volumeText
                    anchors.left: parent.left
                    text: "Volume:"
                    font.pixelSize: 30
                }
                Slider{
                    anchors.left: volumeText.right
                    anchors.right: parent.right
                    id: volume
                    minimumValue: 0
                    maximumValue: 100
                    valueIndicatorVisible: true
                }
            }
        }
    }

    onAccepted: {
        qmlSettingsAdapter.set("sound/volume_override", volumeOverride.checked)
        qmlSettingsAdapter.set("sound/volume", Math.round(volume.value))
    }
}
