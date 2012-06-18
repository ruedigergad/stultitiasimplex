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

#include "portaudiorecordbackend.h"
#include "portaudiorecordthread.h"

PortAudioRecordThread::PortAudioRecordThread()
{
}

void PortAudioRecordThread::run(){
    int *buffer;
    int err;

    buffer = new int[BUFFER_SIZE];

    while(! abort){
        err = Pa_ReadStream(stream, buffer, BUFFER_SIZE);

        if(err != paNoError){
            qDebug("Error reading from record stream:\n %s", Pa_GetErrorText(err));
            break;
        }

        fileHandle->writeRaw(buffer, BUFFER_SIZE * 2);
    }
}

void PortAudioRecordThread::startRecording(PaStream *stream, SndfileHandle *fileHandle){
    this->stream = stream;
    this->fileHandle = fileHandle;
    abort = false;
    start();
}

void PortAudioRecordThread::stopRecording(){
    abort = true;
    this->wait();
}
