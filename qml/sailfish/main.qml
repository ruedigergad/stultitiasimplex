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
import harbour.stultitiasimplex 1.0

ApplicationWindow {
    id: appWindow

    property int primaryFontSize: Theme.fontSizeMedium
    property int primaryBorderSize: Theme.fontSizeMedium

    initialPage: Page {
        SoundFileListView {
            id: soundFileListView

            anchors.fill: parent
            clip: true
            model: soundFileList
        }

        FastScroll {
            id: sectionScroller
            listView: soundFileListView
        }
    }

    cover: CoverBackground {
        id: coverBackground

        property string fileName1: ""
        property string fileName2: ""
        property alias description1: action1Label.text
        property alias description2: action2Label.text

        Image {
            id: coverIcon

            anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 40}
            source: "/usr/share/harbour-stultitiasimplex/cover_icon.png"
        }

        Label {
            id: action1Label

            anchors {top: coverIcon.bottom; topMargin: 40
                     left: parent.left; leftMargin: 10
                     right: parent.right; rightMargin: 30}
            color: Theme.primaryColor
            horizontalAlignment: Text.AlignLeft
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }

        Label {
            id: action2Label

            anchors {top: action1Label.bottom; topMargin: 40
                     left: parent.left; leftMargin: 30
                     right: parent.right; rightMargin: 10}
            color: Theme.primaryColor
            horizontalAlignment: Text.AlignRight
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }

        CoverActionList {
            enabled: mediaPlayer.playbackState != MediaPlayer.PlayingState
                     && coverBackground.fileName1 != ""
                     && coverBackground.fileName2 != ""

            CoverAction {
                onTriggered: mediaPlayer.playSoundFile(coverBackground.fileName1)
            }

            CoverAction {
                onTriggered: mediaPlayer.playSoundFile(coverBackground.fileName2)
            }
        }
    }

    SoundFileListSortFilterProxyModel {
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

    MediaPlayer {
        id: mediaPlayer

        onPlaying: abortDialog.open()
        onStopped: abortDialog.close()

        function playSoundFile(fileName) {
            mediaPlayer.source = "/home/nemo/.stultitiaSimplex/sounds/" + fileName
            mediaPlayer.play()
        }
    }

    QMultimediaAudioRecorder {
        id: recorder
    }

    QMultimediaVuMeterBackend {
        id: vuMeterBackend
    }

    FileSystemHelper {
        id: fileSystemHelper
    }

    RecordDialog {
        id: recordDialog
    }

    Dialog{
        id: abortDialog

        Text {
            anchors.fill: parent
            text: "Close to abort playback."
            font.pixelSize: 50
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }

        onAccepted: {
            console.log("Aborting playback.")
            mediaPlayer.stop()
        }

        onRejected: {
            console.log("Aborting playback.")
            mediaPlayer.stop()
        }
    }

    AboutDialog {
        id: aboutDialog
    }

    EditSoundFileSheet {
        id: editSoundFileSheet

        onAccepted: {
            soundFileList.save()
            soundFileList.reset()
        }
    }

    SettingsSheet {
        id: settingsSheet
    }

    QmlSettingsAdapter {
        id: qmlSettingsAdapter

        onSettingsChanged: applyCoverSettings()

        function applyCoverSettings() {
            coverBackground.description1 = qmlSettingsAdapter.getString("cover_action_1_description")
            coverBackground.fileName1 = qmlSettingsAdapter.getString("cover_action_1_file_name")
            coverBackground.description2 = qmlSettingsAdapter.getString("cover_action_2_description")
            coverBackground.fileName2 = qmlSettingsAdapter.getString("cover_action_2_file_name")
        }
    }

    Component.onCompleted: {
        qmlSettingsAdapter.applyCoverSettings()
        mediaPlayer.source = ""
    }
}
