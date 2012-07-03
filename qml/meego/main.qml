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
import stultitiasimplex 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    Page{
        id: mainPage
        tools: commonTools

        Rectangle{
            anchors.fill: parent
            color: "lightgray"

            Rectangle {
                id: header
                height: 72
                color: "#0c61a8"
                anchors{left: parent.left; right: parent.right; top: parent.top}

                Text {
                    text: "Stultitia Simplex"
                    color: "white"
                    font{pixelSize: 32; family: "Nokia Pure Text Light"}
                    anchors{left: parent.left; leftMargin: 20; verticalCenter: parent.verticalCenter}
                }
            }

            SoundFileListView{
                id: soundFileListView

                model: soundFileList

                anchors{top: header.bottom; left: parent.left; right: parent.right; bottom: parent.bottom}
                clip: true
            }

            FastScroll {
                id: sectionScroller
                listView: soundFileListView
            }
        }
    }

    SoundFileListSortFilterProxyModel{
        id: soundFileList

        onChanged: {
            /*
             * Needed to make SectionScroller happy.
             * First we set the list property of the SectionScroller.
             * This is done here for the sake of completeness.
             */
            sectionScroller.listView = soundFileListView
            /*
             * Second and more important, we force a re-initialization
             * of the SectionScroller. Note: the requirement to do this
             * may be due to the way the model is set for the list here.
             */
            sectionScroller.listViewChanged()
        }
    }

    QmlAudioPlayer{
        id: player
        onStarted: abortDialog.open()
        onFinished: abortDialog.close()
    }

    FileSystemHelper{
        id: fileSystemHelper
    }

    Dialog{
        id: abortDialog

        content: Text{
            anchors.fill: parent
            text: "Press to abort playback."
            font.pixelSize: 50
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }

        onRejected: {
            console.log("Aborting playback.")
            player.abort()
        }
    }

    AboutDialog{
        id: aboutDialog
    }

    EditSoundFileSheet{
        id: editSoundFileSheet

        onAccepted: {
            soundFileList.save()
            soundFileList.reset()
        }
    }

    SettingsSheet{
        id: settingsSheet
    }

    QmlSettingsAdapter{
        id: qmlSettingsAdapter
    }

    ToolBarLayout {
        id: commonTools

        ToolIcon {
            id: iconAdd
            platformIconId: "toolbar-add"
            onClicked: {
                console.log("Add...")
                editSoundFileSheet.category = ""
                editSoundFileSheet.description = ""
                editSoundFileSheet.fileName = ""
                editSoundFileSheet.edit = false
                editSoundFileSheet.open()
            }
        }

        ToolIcon {
            id: iconEdit
            platformIconId: "toolbar-edit"
            enabled: soundFileListView.currentIndex >= 0
            opacity: enabled ? 1 : 0.5
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

        ToolIcon {
            id: iconPlay
            platformIconId: "toolbar-mediacontrol-play"
            enabled: soundFileListView.currentIndex >= 0
            opacity: enabled ? 1 : 0.5
            onClicked: {
                console.log("Play...")
                player.play(soundFileList.get(soundFileListView.currentIndex).fileName)
            }
        }

        ToolIcon {
            id: iconMenu
            platformIconId: "toolbar-view-menu"
            anchors.right: parent === undefined ? undefined : parent.right
            onClicked: myMenu.status === DialogStatus.Closed ? myMenu.open() : myMenu.close()
        }
    }

    Menu {
        id: myMenu

        MenuLayout {
            MenuItem {
                text: "Record Sound"
                onClicked: {
                    console.log("Record...")
                }
            }
            MenuItem {
                text: "Settings"
                onClicked: {
                    console.log("Settings...")
                    settingsSheet.open()
                }
            }
            MenuItem {
                text: "About"
                onClicked: aboutDialog.open()
            }
        }
    }
}
