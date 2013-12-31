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

import QtMultimedia 5.0
import QtQuick 2.0
import Sailfish.Silica 1.0

SilicaListView {
    id: soundFileListView

    property Item contextMenu

    pressDelay: 0

    delegate: BackgroundItem {
        id: listItem

        width: parent.width
        height: menuOpen ? contextMenu.height + descText.height : descText.height

        property bool menuOpen: contextMenu != null && contextMenu.parent === listItem

        function triggerRemorseDeleteItem() {
            remorse.execute(listItem, "Deleting Sound File...", function() { soundFileList.remove(index) })
        }

        Text {
            id: descText

            anchors {left: parent.left; right: parent.right}
            color: Theme.primaryColor
            font.pointSize: primaryFontSize
            horizontalAlignment: Text.AlignHCenter
            text: description
            wrapMode: Text.WordWrap
        }

        RemorseItem { id: remorse }

        onClicked: {
            console.log("Delegate clicked.")
            soundFileListView.currentIndex = index
        }

        onDoubleClicked: {
            console.log("Delegate double-clicked.")
            soundFileListView.currentIndex = index
            console.log("Selected: " + description)
            console.log("File name: " + fileName)
            mediaPlayer.source = "/home/nemo/.stultitiaSimplex/sounds/" + fileName
            mediaPlayer.play()
        }

        onPressAndHold: {
            console.log("Delegate press and hold...")
            soundFileListView.currentIndex = index
            if (!contextMenu)
                contextMenu = contextMenuComponent.createObject(listItem)
            contextMenu.show(listItem)
        }

    }

    Component {
        id: contextMenuComponent
        ContextMenu {
            MenuItem {
                text: "Edit Sound"

                onClicked: {
                    console.log("Edit...")
                    var itm = soundFileList.get(soundFileListView.currentIndex)
                    editSoundFileSheet.category = itm.category
                    editSoundFileSheet.description = itm.description
                    editSoundFileSheet.fileName = itm.fileName
                    editSoundFileSheet.edit = true
                    editSoundFileSheet.open()
                }
            }

            MenuItem {
                text: "Delete Sound"

                onClicked: {
                    soundFileListView.currentItem.triggerRemorseDeleteItem();
                }
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
                font.pointSize: primaryFontSize
                font.bold: true
                text: section
                color: Theme.secondaryColor
            }

            Rectangle {
                height: 1
                color: Theme.secondaryColor
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }
    }

    PullDownMenu {
        MenuItem {
            text: "Add Sound"

            onClicked: {
                console.log("Add...")
                editSoundFileSheet.category = "Please chose a category."
                editSoundFileSheet.description = ""
                editSoundFileSheet.fileName = "Please select a sound file."
                editSoundFileSheet.edit = false
                editSoundFileSheet.open()
            }
        }

        MenuItem {
            text: "Record Sound"
            onClicked: {
                console.log("Record...")
                recordDialog.open()
            }
        }

//        MenuItem {
//            text: "Settings"
//            onClicked: {
//                console.log("Settings...")
//                settingsSheet.open()
//            }
//        }

        MenuItem {
            text: "About"
            onClicked: aboutDialog.open()
        }
    }

    PushUpMenu {
        MenuItem {
            text: "Go to Top"
            onClicked: soundFileListView.scrollToTop()
        }
    }
}

