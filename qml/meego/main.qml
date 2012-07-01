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

    initialPage: MainPage{}

    SoundFileList{
        id: soundFileList
    }

    QmlAudioPlayer{
        id: player
        onStarted: abortDialog.open()
        onFinished: abortDialog.close()
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
}
