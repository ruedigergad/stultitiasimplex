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

QueryDialog{
    id: recordDialog

    function reject(){}

    onStatusChanged:{
        if(status === DialogStatus.Opening){
            console.log("Connecting audio...")
            vuMeter.value = 0
            fileName.text = ""
            recorder.connectAudio(0)
        }else if(status === DialogStatus.Closing){
            console.log("Disconnecting audio...")
            recorder.disconnectAudio()
            vuMeter.value = 0
        }
    }

    Connections{
        target: recorder
        onVuMeterValueUpdate: {
//            console.log("VU-meter value updated: " + value)
            vuMeter.value = value
        }
    }

    content: Item{
        anchors.fill: parent

        Text{
            anchors{
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

        Rectangle{
            id: vuMeter

            property bool recording: false
            property real value: 0

            color: "lightgray"

            anchors{
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
                bottom: fileName.top
                bottomMargin: 20
            }
            height: 50

            border{
                color: recording ? "red" : "green"
                width: 3
            }

            Rectangle{
                id: indicator

                color: "blue"

                anchors{
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                }

                width: parent.width * vuMeter.value
            }
        }

        TextField{
            id: fileName
            text: ""

            anchors.centerIn: parent
            width: parent.width
        }

        ButtonRow{
            id: recordButtons

            anchors{
                top: fileName.bottom
                topMargin: 20
                left: parent.left
                right: parent.right
            }

            Button{
                id: startRecordButton

                text: "Record"

                onClicked: {
                    vuMeter.recording = true
                    closeButton.enabled = false
                    startRecordButton.enabled = false
                    stopRecordButton.enabled = true
                    recorder.startRecord(fileName.text)
                }
            }

            Button{
                id: stopRecordButton
                enabled: false

                text: "Stop"

                onClicked: {
                    recorder.stopRecord()
                    stopRecordButton.enabled = false
                    startRecordButton.enabled = true
                    closeButton.enabled = true
                    vuMeter.recording = false
                }
            }
        }

        Button{
            id: closeButton

            anchors{
                top: recordButtons.bottom
                topMargin: 50
                horizontalCenter: parent.horizontalCenter
            }

            text: "Close"
            onClicked: close()
        }
    }
}
