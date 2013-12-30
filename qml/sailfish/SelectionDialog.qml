/*
 *  Copyright 2011 Ruediger Gad
 *
 *  This file is part of MeePasswords.
 *
 *  MeePasswords is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MeePasswords is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with MeePasswords.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: selectionDialog

    anchors.fill: parent

    property alias title: titleText.text
    property alias label: labelText.text
    property alias model: selectionlListView.model
    property alias selectedIndex: selectionlListView.currentIndex
    property alias selectedItem: selectionlListView.currentItem

    function accept() {
        close()
        accepted()
    }

    Item {
        anchors.fill: parent

        Text {
            id: titleText
            font {pointSize: primaryFontSize; bold: true}
            anchors {bottom: labelText.top; bottomMargin: primaryFontSize * 0.25; horizontalCenter: parent.horizontalCenter}
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            color: "white"
        }

        Text {
            id: labelText; font.pointSize: primaryFontSize * 0.75; color: "lightgray"
            anchors {bottom: selectionListViewRectangle.top; bottomMargin: primaryFontSize}
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }

        ListView {
            id: selectionlListView

            anchors.fill: parent
            clip: true

            delegate: Label {
                width: parent.width
                text: name
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: Theme.fontSizeMedium
                color: Theme.primaryColor

//                    property string itemName: name

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        selectionlListView.currentIndex = index
                        selectionDialog.accept()
                    }
                }
            }
        }
    }
}
