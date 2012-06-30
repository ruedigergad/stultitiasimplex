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

#include "qmlaudioplayer.h"

#ifdef UNIX
#include "src/io/audio/pulseaudio/pulseaudioplayerbackend.h"
#endif

#ifdef WIN32
#include "src/io/audio/portaudio/portaudioplayerbackend.h"
#endif

QmlAudioPlayer::QmlAudioPlayer(QObject *parent) :
    QObject(parent)
{
#ifdef WIN32
    backend = new PortAudioPlayerBackend();
#endif

#ifdef UNIX
    backend = new PulseAudioPlayerBackend();
#endif

    connect(backend, SIGNAL(playbackFinished()), this, SIGNAL(finished()), Qt::QueuedConnection);
}

QmlAudioPlayer::~QmlAudioPlayer(){
    disconnect(backend, SIGNAL(playbackFinished()), this, SIGNAL(finished()));
    delete backend;
}

void QmlAudioPlayer::play(QString fileName){
    qDebug("Starting playback...");
    emit started(fileName);
    backend->play(fileName);
}
