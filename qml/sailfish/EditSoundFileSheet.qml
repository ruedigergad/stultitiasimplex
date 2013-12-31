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

    canAccept: category !== "Please chose a category." && category !== ""
               && fileName !== "Please select a sound file." && fileName !== ""
               && description !== ""

    onAccepted: {
        console.log("Accepted.")
        if (edit) {
            console.log("Setting new values.")
            soundFileList.update(soundFileListView.currentIndex, description, fileName, category)
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

            PageHeader {
                title: "Edit Sound File"
            }

            Text {
                text: "Description"
                color: Theme.primaryColor
                font.pixelSize: 30
                verticalAlignment: Text.AlignVCenter
                width: parent.width
            }

            Row {
                width: parent.width
                spacing: 10

                TextField {
                    id: descriptionTextField
                    placeholderText: "Please add a description."
                    width: parent.width
                }
            }

            Text {
                id: categoryText
                color: Theme.primaryColor
                text: "Category"
                font.pixelSize: 30
                verticalAlignment: Text.AlignVCenter
                width: parent.width
            }

            Row {
                id: categoryRow
                width: parent.width
                spacing: 10

                Button {
                    id: categoryButton
                    width: categoryRow.width - addCategoryButton.width
                    onClicked: {
                        categoryModel.clear()
                        var alreadyAdded = []

                        console.log("Already added: " + alreadyAdded)

                        for (var i = 0; i < soundFileList.count; i++) {
                            var current = soundFileList.get(i).category

                            if (alreadyAdded.indexOf(current) < 0) {
                                console.log("Adding: " + current)
                                categoryModel.append({"name": current})
                                alreadyAdded.push(current)
                            }
                        }

                        categorySelectionDialog.open()
                    }
                }
                Button {
                    id: addCategoryButton
                    text: "+"
                    width: 75
                    onClicked: addCategoryDialog.open()
                }
            }

            Text {
                color: Theme.primaryColor
                text: "File Name"
                font.pixelSize: 30
                verticalAlignment: Text.AlignVCenter
                width: parent.width
            }

            Button {
                id: fileNameButton

                width: parent.width

                onClicked: {
                    var soundFiles = fileSystemHelper.getWavFiles().split("/")
                    console.log(soundFiles)

                    fileNameModel.clear()
                    for (var i = 0; i < soundFiles.length; i++) {
                        fileNameModel.append({"name": soundFiles[i]})
                    }

                    fileNameSelectionDialog.open()
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
            fileName = fileNameModel.get(selectedIndex).name
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
            category = categoryModel.get(selectedIndex).name
        }
    }

    Dialog {
        id: addCategoryDialog

        canAccept: newCategoryTextField !== ""

        TextField {
            id: newCategoryTextField
            anchors.centerIn: parent
            placeholderText: "Please enter a category name."
            width: parent.width * 0.9
        }

        onAccepted: {
            category = newCategoryTextField.text
            newCategoryTextField.text = ""
        }

        onRejected: {
            newCategoryTextField.text = ""
        }

        onStatusChanged: {
            if (status === DialogStatus.Opening) {
                newCategoryTextField.text = ""
            }
        }
    }
}

