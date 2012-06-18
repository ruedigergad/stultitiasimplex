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

#include "audioplayer.h"

#ifdef UNIX
#include "src/io/audio/pulseaudio/pulseaudioplayerbackend.h"
#endif

#ifdef WIN32
#include "src/io/audio/portaudio/portaudioplayerbackend.h"
#endif

AudioPlayer::AudioPlayer()
{
#ifdef WIN32
    backend = new PortAudioPlayerBackend();
#endif

#ifdef UNIX
    backend = new PulseAudioPlayerBackend();
#endif

    connect(backend, SIGNAL(playbackFinished()), this, SIGNAL(finished()), Qt::QueuedConnection);
}

AudioPlayer::~AudioPlayer(){
    disconnect(backend, SIGNAL(playbackFinished()), this, SIGNAL(finished()));
    delete backend;
}

void AudioPlayer::abortPlay(int ret){
    if(ret == QMessageBox::Ok){
        qDebug("Abort requested...");
        backend->abortPlay();
    }else{
        qDebug("abortPlay() got return code: %d", ret);
    }
}

void AudioPlayer::createAbortDialog(){
    abortDialog = new QMessageBox(0);
    abortDialog->setIcon(QMessageBox::Question);
    abortDialog->setDefaultButton(QMessageBox::Ok);
    abortDialog->setText("Abort play?");

    connect(this, SIGNAL(finished()), abortDialog, SLOT(close()), Qt::QueuedConnection);
    connect(abortDialog, SIGNAL(finished(int)), this, SLOT(abortPlay(int)), Qt::QueuedConnection);

    abortDialog->open();
}

void AudioPlayer::play(QString file){
    createAbortDialog();
    backend->play(file);
}

