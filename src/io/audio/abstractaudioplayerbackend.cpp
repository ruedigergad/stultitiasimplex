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

#include "abstractaudioplayerbackend.h"

AbstractAudioPlayerBackend::AbstractAudioPlayerBackend()
{
    connect(this, SIGNAL(finished()), this, SLOT(cleanUp()), Qt::QueuedConnection);
}

void AbstractAudioPlayerBackend::abortPlay(){
    abort = true;
}

void AbstractAudioPlayerBackend::closeFile(){
    delete fileHandle;
}

void AbstractAudioPlayerBackend::openFile(){
    fileHandle = new SndfileHandle(fileName.toLocal8Bit().constData(), SFM_READ, 0, 0, 0);
}

void AbstractAudioPlayerBackend::play(QString file){
    abort = false;
    fileName = file;
    openFile();

    qDebug("Starting playback thread...");
    start();
}

void AbstractAudioPlayerBackend::cleanUp(){
    closeFile();
    emit playbackFinished();
}
