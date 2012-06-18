/*
 *  Copyright 2010 Ruediger Gad
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

#include <QFileDialog>

#include "editbuttondialog.h"
#include "ui_editbuttondialog.h"
#include "src/constants.h"
#include "src/data/soundfilelist.h"

EditButtonDialog::EditButtonDialog(QWidget *parent, SoundFile *file, SoundFileList *list) :
    QDialog(parent),
    ui(new Ui::EditButtonDialog)
{
    this->file = file;
    this->list = list;
    ui->setupUi(this);

    ui->fileEdit->setText((file == 0) ? "Select File" : file->getFileName());
    ui->labelEdit->setText((file == 0) ? "Enter Label" : file->getDescription());
    labelUpdated = (file != 0);
    fileUpdated = (file != 0);
    updateButtons();
}

EditButtonDialog::~EditButtonDialog()
{
    delete ui;
}

void EditButtonDialog::accept(){
    qDebug("Entering EditButtonDialog::accept()...");

    if(file == 0){
        file = new SoundFile(0, list);
    }

    file->setDescription(ui->labelEdit->text());
    file->setFileName(ui->fileEdit->text());
    this->done(1);
}

void EditButtonDialog::fileDialog(){
    qDebug("Entering EditButtonDialog::fileDialog()...");

    QString selectedFile = ui->fileEdit->text();

    if(selectedFile == NULL || ! QFile::exists(selectedFile)){
        selectedFile = Constants::SOUNDS_DIR;
    }

    QString newFile = QFileDialog::getOpenFileName(
            this,
            tr("Select audio file."),
            selectedFile,
            tr("Audio files (*.wav)"));

    if(newFile != NULL){
        updateFileText(newFile);
    }
}

SoundFile *EditButtonDialog::getFile(){
    return file;
}

void EditButtonDialog::updateButtons(){
    QFile file(ui->fileEdit->text());

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(
            labelUpdated
            && fileUpdated
            && file.open(QFile::ReadOnly)
            && (! ui->labelEdit->text().contains(Constants::CSV_SEPARATOR))
            );

    file.close();
}

void EditButtonDialog::updateFileText(QString text){
    ui->fileEdit->setText(text);
    fileUpdated = true;
    updateButtons();
}

void EditButtonDialog::updateLabelText(QString text){
    ui->labelEdit->setText(text);
    labelUpdated = true;
    updateButtons();
}
