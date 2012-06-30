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

    Page {
        id: mainPage

        Rectangle{
            anchors.fill: parent
            color: "lightgray"

            Rectangle {
                id: header
                height: 72
                color: "#0c61a8"
                anchors{left: parent.left; right: parent.right; top: parent.top}
                z: 48

                Text {
                    text: "Stultitia Simplex"
                    color: "white"
                    font{pixelSize: 32; family: "Nokia Pure Text Light"}
                    anchors{left: parent.left; leftMargin: 20; verticalCenter: parent.verticalCenter}
                }
            }

            ListView{
                id: soundFileListView

                model: soundFileList

                anchors{top: header.bottom; left: parent.left; right: parent.right; bottom: parent.bottom}
                clip: true

                delegate: Item{
                    anchors{left: parent.left; right: parent.right}
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
                        horizontalAlignment: Text.AlignHCenter
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
                    /*
                     * Set z to a seemingly insane high value. For some strange/unknown reason the
                     * the highlight is not shown at all with z=0. For z=1 the highligh is shown but
                     * disappears for parts that had been at least once out of the screen bounds
                     * (i.e. had not been visible in the list). Hence, just in case set z=32.
                     */
                    z:32
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
                            font.pixelSize: 30
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

            FastScroll {
                id: sectionScroller
                listView: soundFileListView
            }
        }
    }

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
