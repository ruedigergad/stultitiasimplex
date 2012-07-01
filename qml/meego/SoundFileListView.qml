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

ListView{
    id: soundFileListView

    delegate: Item{
        anchors{left: parent.left; leftMargin: 10; right: parent.right}
        height: descText.height

        Rectangle{
            anchors.fill: parent
            color: "black"
            opacity: delegateMouseArea.pressed ? 0.5 : 0
        }

        Text{
            id: descText
            anchors{left: parent.left; right: parent.right}
            text: description
            font.pixelSize: 40
            horizontalAlignment: Text.AlignLeft
            wrapMode: Text.WordWrap
        }

        MouseArea{
            id: delegateMouseArea
            anchors.fill: parent

            onClicked: {
                soundFileListView.currentIndex = index
            }

            onDoubleClicked: {
                console.log("Selected: " + description)
                console.log("File name: " + fileName)
                player.play(fileName)
            }
        }
    }

    highlightMoveDuration: 200
    highlight: Rectangle {
        id: highlightRectangle
        color: "gray"
        width: parent.width
        opacity: 0.4
    }

    section {
        property: "category"
        criteria: ViewSection.FullString
        delegate: Item {
            width: parent.width
            height: sectionText.height

            Text {
                id: sectionText
                anchors.right: parent.right
                anchors.rightMargin: 10
                font.pixelSize: 35
                font.bold: true
                text: section
                color: "gray"
            }

            Rectangle {
                height: 1
                color: "gray"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }
    }
}

