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

#include <QMouseEvent>
#include <QMessageBox>
#include <Qt>

#include "soundbutton.h"
#include "src/ui/dialog/editbuttondialog.h"


SoundButton::SoundButton(QWidget *parent, SoundFile *soundFile) :
    QPushButton(parent)
{
    this->soundFile = soundFile;
    setText(soundFile->getDescription());

    addActions();
    addMenu();

    connect(this, SIGNAL(clicked()), this, SLOT(play()));
    connect(soundFile, SIGNAL(changed()), this, SLOT(fileChanged()));

    player = new AudioPlayer();
    connect(player, SIGNAL(finished()), this, SIGNAL(playingStopped()), Qt::QueuedConnection);
}

SoundButton::~SoundButton(){
    delete menu;
    delete deleteAction;
    delete editAction;
    delete player;
}

void SoundButton::addActions(){
    editAction = new QAction(tr("&Edit"), this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));

    deleteAction = new QAction(tr("&Delete"), this);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteSound()));
}

void SoundButton::addMenu(){
    menu = new QMenu(this);
    menu->addAction(editAction);
//    menu->addAction(deleteAction);
}

void SoundButton::deleteSound(){
    QMessageBox mb(this);
    mb.setText("Delete \"" + soundFile->getDescription() + "\"?");
    mb.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    if(mb.exec() == QMessageBox::Ok){
        SoundFileList *list = soundFile->getList();
        list->remove(soundFile);
    }
}

void SoundButton::edit(){
    qDebug("Entering SoundButton::edit()...");

    EditButtonDialog dialog(this, soundFile);
    dialog.exec();
}

void SoundButton::fileChanged(){
    setText(soundFile->getDescription());
}

void SoundButton::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton){
        qDebug("Right button pressed.");

        menu->exec(QCursor::pos());
    }else{
        QPushButton::mousePressEvent(e);
    }
}

void SoundButton::play(){
    qDebug("Entering SoundButton::play()...");
    emit playingStarted();
    player->play(soundFile->getFileName());
}
