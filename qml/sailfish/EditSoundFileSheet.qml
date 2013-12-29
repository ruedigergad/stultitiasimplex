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
    id: editSoundFileSheet

    property alias category: categoryButton.text
    property alias description: descriptionTextField.text
    property alias fileName: fileNameButton.text

    property bool edit: false

    onAccepted: {
        console.log("Accepted.")
        if (edit) {
            console.log("Setting new values.")
            var itm = soundFileList.get(soundFileListView.currentIndex)
            itm.category = category
            itm.description = description
            itm.fileName = fileName
        } else {
            console.log("Adding new entry...")
            soundFileList.add(description, fileName, category)
        }
    }

    onRejected: {
        console.log("Rejected.")
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: sheetContent.height

        Column {
            id: sheetContent
            spacing: 15

            anchors {top: parent.top; left: parent.left; right: parent.right; margins: 15}

            Row {
                width: parent.width
                spacing: 10

                Text {
                    text: "Description"
                    font.pixelSize: 30
                    verticalAlignment: Text.AlignVCenter
                }
                TextArea {
                    id: descriptionTextField
                }
            }

            Row {
                id: categoryRow
                width: parent.width
                spacing: 10

                Text {
                    id: categoryText
                    text: "Category"
                    font.pixelSize: 30
                    verticalAlignment: Text.AlignVCenter
                }
                Button {
                    id: categoryButton
                    width: categoryRow.width - categoryText.width - addCategoryButton.width
                    onClicked: {
                        categoryModel.clear()
                        var alreadyAdded = []

                        console.log("Already added: " + alreadyAdded)
                        for(var i = 0; i < soundFileList.count; i++){
                            var current = soundFileList.get(i).category
                            if(alreadyAdded.indexOf(current) < 0){
                                console.log("Adding: " + current)
                                categoryModel.append({"category": current})
                                alreadyAdded.push(current)
                            }
                        }

                        categorySelectionDialog.open()
                    }
                }
                Button {
                    id: addCategoryButton
                    text: "+"
                    onClicked: addCategoryDialog.open()
                }
            }
            Row {
                width: parent.width
                spacing: 10

                Text {
                    text: "File Name"
                    font.pixelSize: 30
                    verticalAlignment: Text.AlignVCenter
                }
                Button {
                    id: fileNameButton

                    onClicked: {
                        var soundFiles = fileSystemHelper.getWavFiles().split("/")
                        console.log(soundFiles)

                        fileNameModel.clear()
                        for (var i = 0; i < soundFiles.length; i++) {
                            fileNameModel.append({"fileName": soundFiles[i]})
                        }

                        fileNameSelectionDialog.open()
                    }
                }
            }
        }
    }

    ListModel {
        id: fileNameModel
    }

    SelectionDialog {
        id: fileNameSelectionDialog
//        titleText: "Select Sound File"
        model: fileNameModel
        onAccepted: {
            fileName = fileNameModel.get(selectedIndex).fileName
        }
    }

    ListModel {
        id: categoryModel
    }

    SelectionDialog {
        id: categorySelectionDialog
//        titleText: "Select Category"
        model: categoryModel
        onAccepted: {
            category = categoryModel.get(selectedIndex).category
        }
    }

    Dialog {
        id: addCategoryDialog

//        DialogHeader {
//            title: "Add Category"
//        }

        TextField {
            id: newCategoryTextField
            anchors.centerIn: parent
        }

        onAccepted: {
            category = newCategoryTextField.text
            newCategoryTextField.text = ""
        }

        onRejected: {
            newCategoryTextField.text = ""
        }
    }
}

