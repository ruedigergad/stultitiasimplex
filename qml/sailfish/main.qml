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

import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.stultitiasimplex 1.0

ApplicationWindow {
    id: appWindow

    initialPage: mainPage

    property int primaryFontSize: Theme.fontSizeMedium
    property int primaryBorderSize: Theme.fontSizeMedium

    Page {
        id: mainPage

        SoundFileListView {
            id: soundFileListView

            model: soundFileList

            anchors.fill: parent
            clip: true
        }

        FastScroll {
            id: sectionScroller
            listView: soundFileListView
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

    QmlAudioPlayer {
        id: player
        onStarted: abortDialog.open()
        onFinished: abortDialog.close()
    }

    QmlAudioRecorder {
        id: recorder
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
    }

}
