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

Sheet{
    id: editSoundFileSheet
    anchors.fill: parent
    visualParent: mainPage

    property alias category: categoryTextField.text
    property alias description: descriptionTextField.text
    property alias fileName: fileNameButton.text

    property bool edit: false

    onAccepted: {
        console.log("Accepted.")
        if(edit){
            console.log("Setting new values.")
            var itm = soundFileList.at(soundFileListView.currentIndex)
            itm.category = category
            itm.description = description
            itm.fileName = fileName
        }else{

        }
    }

    onRejected: {
        console.log("Rejected.")
    }

//    Dialog{
//        id: noTextGivenDialog
//        anchors.fill: parent

//        content: Text {
//            anchors.centerIn: parent
//            width: parent.width
//            text: "Please enter a text."
//            font.pointSize: 30
//            color: "white"
//            horizontalAlignment: Text.AlignHCenter; wrapMode: Text.Wrap
//        }

//        onRejected: {
//            textInput.focus = true
//        }
//    }

    acceptButtonText: "Save"
    rejectButtonText: "Cancel"

//    buttons: Item {
//        anchors.fill: parent
//        SheetButton{
//            id: rejectButton
//            anchors.left: parent.left
//            anchors.leftMargin: 16
//            anchors.verticalCenter: parent.verticalCenter
//            text: "Cancel"
//            onClicked: editToDoSheet.reject();
//        }

//        SheetButton{
//            id: acceptButton
//            anchors.right: parent.right
//            anchors.rightMargin: 16
//            anchors.verticalCenter: parent.verticalCenter
//            platformStyle: SheetButtonAccentStyle { }
//            text: "OK"
//            onClicked: {
//                if(textInput.text === ""){
//                    noTextGivenDialog.open()
//                }else{
//                    editToDoSheet.accept()
//                }
//            }
//        }
//    }

    content: Flickable {
        anchors.fill: parent
        contentHeight: sheetContent.height

        Column {
            id: sheetContent
            spacing: 12

            anchors{top: parent.top; left: parent.left; right: parent.right; margins: 15}

            Row{
                Text{
                    text: "Description"
                    font.pixelSize: 30
                }
                TextArea{
                    id: descriptionTextField
                }
            }

            Row{
                Text{
                    text: "Category"
                    font.pixelSize: 30
                }
                TextField{
                    id: categoryTextField
                }
            }
            Row{
                Text{
                    text: "File Name"
                    font.pixelSize: 30
                }
                Button{
                    id: fileNameButton

                    onClicked: {
                        var soundFiles = fileSystemHelper.getWavFiles().split("/")
                        console.log(soundFiles)

                        fileNameModel.clear()
                        for(var i = 0; i < soundFiles.length; i++){
                            fileNameModel.append({"fileName": soundFiles[i]})
                        }

                        fileNameSelectionDialog.model = fileNameModel
                        fileNameSelectionDialog.open()
                    }
                }
            }
        }
    }

    ListModel{
        id: fileNameModel
    }

    SelectionDialog {
        id: fileNameSelectionDialog
        titleText: "Select Sound File"
        onAccepted: {
            fileName = fileNameModel.get(selectedIndex).fileName
        }
    }
}

