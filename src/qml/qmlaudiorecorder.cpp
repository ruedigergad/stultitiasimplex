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

#include "qmlaudiorecorder.h"

#include "src/io/audio/pulseaudio/pa_utils.h"
#include "src/io/audio/pulseaudio/pulseaudiorecordbackend.h"

QmlAudioRecorder::QmlAudioRecorder(QObject *parent) :
    QObject(parent)
{
}

void QmlAudioRecorder::connectAudio(int index){
    disconnectAudio();

    switch(index){
    case 0:
        backend = new PulseAudioRecordBackend("source.hw0");
        break;
    case 1:
        backend = new PulseAudioRecordBackend("source.hw1");
        break;
    case 2:
        backend = new PulseAudioRecordBackend("sink.hw0.monitor");
        break;
    default:
        qDebug("Unknown source!");
    }

    connect(backend, SIGNAL(updateVuMeterSignal(float)), this, SIGNAL(vuMeterValueUpdate(float)), Qt::QueuedConnection);
}

void QmlAudioRecorder::disconnectAudio(){
    if(backend != NULL){
        delete backend;
        backend = NULL;
    }
}

void QmlAudioRecorder::startRecord(QString fileName){
    backend->startRecording(fileName);
}

void QmlAudioRecorder::stopRecord(){
    backend->stopRecording();
}
