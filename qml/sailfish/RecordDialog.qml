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

Dialog {
    id: recordDialog

    function reject(){}

    onStatusChanged: {
        if(status === DialogStatus.Opening) {
            console.log("Connecting audio...")
            vuMeter.value = 0
            fileName.text = ""
            startRecordButton.enabled = false
//            recorder.connectAudio(0)
        }else if(status === DialogStatus.Closing){
            console.log("Disconnecting audio...")
//            recorder.disconnectAudio()
            vuMeter.value = 0
        }
    }

    Connections {
        target: recorder
        onVuMeterValueUpdate: {
//            console.log("VU-meter value updated: " + value)
            vuMeter.value = value
        }
    }

    Item {
        anchors.fill: parent

        Text {
            anchors {
                left: parent.left
                right: parent.right
                bottom: vuMeter.top
                bottomMargin: 50
            }

            color: "white"

            text: "Record Sound"

            font.pixelSize: 40
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle {
            id: vuMeter

            property bool recording: false
            property real value: 0

            color: "lightgray"

            anchors {
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
                bottom: fileName.top
                bottomMargin: 20
            }
            height: 50

            border {
                color: recording ? "red" : "green"
                width: 6
            }

            Rectangle {
                id: indicator

                color: "blue"

                anchors {
                    left: parent.left
                    leftMargin: 6
                    top: parent.top
                    topMargin: 6
                    bottom: parent.bottom
                    bottomMargin: 6
                }
            }

            onValueChanged: {
                var val = parent.width * vuMeter.value * 3
                if (val >= parent.width - 12) {
                    indicator.width = parent.width - 12
                } else {
                    indicator.width = val
                }
            }
        }

        TextField {
            id: fileName
            text: ""

            anchors.centerIn: parent
            width: parent.width

            onTextChanged: {
                if (text && text !== "") {
                    startRecordButton.enabled = true
                }
            }

            placeholderText: "Please enter a name (without .ogg)."
        }

        Row {
            id: recordButtons

            anchors {
                top: fileName.bottom
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }

            Button {
                id: startRecordButton

                text: "Record"

                onClicked: {
                    vuMeter.recording = true
                    closeButton.enabled = false
                    startRecordButton.enabled = false
                    stopRecordButton.enabled = true
                    recorder.startRecord(fileSystemHelper.getHomePath() + "/.stultitiaSimplex/sounds/" + fileName.text + ".ogg")
                }
            }

            Button {
                id: stopRecordButton
                enabled: false

                text: "Stop"

                onClicked: {
                    recorder.stopRecord()
                    stopRecordButton.enabled = false
                    startRecordButton.enabled = true
                    closeButton.enabled = true
                    vuMeter.recording = false
                    vuMeter.value = 0
                }
            }
        }

        Button {
            id: closeButton

            anchors {
                top: recordButtons.bottom
                topMargin: 50
                horizontalCenter: parent.horizontalCenter
            }

            text: "Close"
            onClicked: close()
        }
    }
}
