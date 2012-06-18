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

#include "soundfilelistdialog.h"
#include "ui_soundfilelistdialog.h"

SoundFileListDialog::SoundFileListDialog(QWidget *parent, SoundFileList *list) :
    QDialog(parent),
    ui(new Ui::SoundFileListDialog)
{
    qDebug("Entering SoundFileListDialog::SoundFileListDialog()...");
    ui->setupUi(this);

    this->list = list;

    QStringList strings;
    const QList<SoundFile *> *files = list->getList();
    QList<SoundFile *>::const_iterator iter;
    for(iter = files->begin(); iter != files->end(); iter++){
        SoundFile *file = *iter;
        strings << file->getDescription();
    }

    ui->listWidget->addItems(strings);
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accept()));
}

SoundFileListDialog::~SoundFileListDialog()
{
    delete ui;
}

void SoundFileListDialog::accept(){
    QListWidgetItem *item = ui->listWidget->selectedItems().takeFirst();
    selection = list->getList()->at(ui->listWidget->row(item));
    this->done(1);
}

SoundFile *SoundFileListDialog::getSelection(){
    return selection;
}
