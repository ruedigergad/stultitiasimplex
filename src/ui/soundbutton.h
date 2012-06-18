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

#ifndef SOUNDBUTTON_H
#define SOUNDBUTTON_H

#include <QAction>
#include <QFile>
#include <QMenu>
#include <QPushButton>

#include "src/io/audio/audioplayer.h"
#include "src/data/soundfile.h"

class SoundButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SoundButton(QWidget *parent = 0, SoundFile *soundFile = 0);
    ~SoundButton();

signals:
    void playingStarted();
    void playingStopped();

public slots:
    void play();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    void addActions();
    void addMenu();

    SoundFile *soundFile;

    QMenu *menu;
    QAction *editAction;
    QAction *deleteAction;

    AudioPlayer *player;

private slots:
    void fileChanged();
    void edit();
    void deleteSound();

};

#endif // SOUNDBUTTON_H
