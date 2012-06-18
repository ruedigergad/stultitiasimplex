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

#include "reorderdialog.h"
#include "ui_reorderdialog.h"

ReorderDialog::ReorderDialog(QWidget *parent, SoundFileList *list) :
    QDialog(parent),
    ui(new Ui::ReorderDialog)
{
    qDebug("Entering ReorderDialog::ReorderDialog()...");
    ui->setupUi(this);

    this->list = list;

    fillWidget(0);

    connect(list, SIGNAL(moved(int)), this, SLOT(fillWidget(int)));

    connect(ui->bottom, SIGNAL(clicked()), this, SLOT(moveBottom()));
    connect(ui->down, SIGNAL(clicked()), this, SLOT(moveDown()));
    connect(ui->down10, SIGNAL(clicked()), this, SLOT(moveTenDown()));
    connect(ui->up10, SIGNAL(clicked()), this, SLOT(moveTenUp()));
    connect(ui->up, SIGNAL(clicked()), this, SLOT(moveUp()));
    connect(ui->top, SIGNAL(clicked()), this, SLOT(moveTop()));
}

ReorderDialog::~ReorderDialog()
{
    delete ui;
}

void ReorderDialog::fillWidget(int selection){
    ui->listWidget->clear();

    QStringList strings;
    const QList<SoundFile *> *files = list->getList();
    QList<SoundFile *>::const_iterator iter;
    for(iter = files->begin(); iter != files->end(); iter++){
        SoundFile *file = *iter;
        strings << file->getDescription();
    }

    ui->listWidget->addItems(strings);
    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listWidget->setCurrentRow(selection);
}

int ReorderDialog::getSelectionIndex(){
    QListWidgetItem *item = ui->listWidget->selectedItems().takeFirst();
    return ui->listWidget->row(item);
}

void ReorderDialog::moveBottom(){
    int index = getSelectionIndex();
    list->move(index, list->getList()->size() - 1);
}

void ReorderDialog::moveDown(){
    int index = getSelectionIndex();
    list->move(index, index + 1);
}

void ReorderDialog::moveTenDown(){
    int index = getSelectionIndex();
    list->move(index, index + 10);
}

void ReorderDialog::moveTenUp(){
    int index = getSelectionIndex();
    list->move(index, index - 10);
}

void ReorderDialog::moveUp(){
    int index = getSelectionIndex();
    list->move(index, index - 1);
}

void ReorderDialog::moveTop(){
    int index = getSelectionIndex();
    list->move(index, 0);
}
