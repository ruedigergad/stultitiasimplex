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

#include "portaudioplayerbackend.h"

PortAudioPlayerBackend::PortAudioPlayerBackend() : AbstractAudioPlayerBackend()
{
    qDebug("Using PortAudio player-backend...");
}

void PortAudioPlayerBackend::closeAudio(){
    int err;

    if(outStream != NULL){
        err = Pa_StopStream(outStream);
        if(err != paNoError){
            qDebug("Error stopping stream:\n %s", Pa_GetErrorText(err));
        }

        err = Pa_CloseStream(outStream);
        if(err != paNoError){
            qDebug("Error closing stream:\n %s", Pa_GetErrorText(err));
        }
    }
    err = Pa_Terminate();
    if(err != paNoError){
        qDebug("Error terminating port audio:\n %s", Pa_GetErrorText(err));
    }
}

int PortAudioPlayerBackend::initAudio(){
    int err;
    int devCount;
    int devId = 0;

    err = Pa_Initialize();
    if(err != paNoError){
        qDebug("Error initializing port audio:\n %s", Pa_GetErrorText(err));
        return -1;
    }

    devCount = Pa_GetDeviceCount();
    if(devCount < 0){
        qDebug("Got negative number of devices: %d", devCount);
        qDebug("Textual error message is:\n %s", Pa_GetErrorText(devCount));
        return -1;
    }

    for(int i = 0; i < devCount; i++){
        const PaDeviceInfo *devInfo = Pa_GetDeviceInfo(i);
        qDebug("Found device: %s", devInfo->name);
#ifdef WIN32
        if(strcmp("Microsoft Soundmapper - Output", devInfo->name) == 0){
            devId = i;
            qDebug("Using %s with id %d as output.", devInfo->name, devId);
        }
#else
        if(strcmp("default", devInfo->name) == 0){
            devId = i;
            qDebug("Using %s with id %d as output.", devInfo->name, devId);
        }
#endif
    }

    streamParams.device = devId;
    streamParams.channelCount = fileHandle->channels();
    streamParams.sampleFormat = paInt16;
    streamParams.suggestedLatency = Pa_GetDeviceInfo(streamParams.device)->defaultHighOutputLatency;
    streamParams.hostApiSpecificStreamInfo = NULL;

    err = Pa_IsFormatSupported(NULL, &streamParams, fileHandle->samplerate());
    if(err != paNoError){
        qDebug("Format not supported:\n %s", Pa_GetErrorText(err));
        return -1;
    }

    err = Pa_OpenStream(&outStream, NULL, &streamParams, fileHandle->samplerate(), 0, paNoFlag, NULL, NULL);
    if(err != paNoError){
        qDebug("Error opening stream:\n %s", Pa_GetErrorText(err));
        return -1;
    }

    err = Pa_StartStream(outStream);
    if(err != paNoError){
        qDebug("Error starting stream:\n %s", Pa_GetErrorText(err));
        return -1;
    }

    return 0;
}

void PortAudioPlayerBackend::run(){
    initAudio();

    int *buffer;
    buffer = new int[BUFFER_SIZE];

    int read_count;

    read_count = fileHandle->readRaw(buffer, BUFFER_SIZE);
    while(read_count > 0){
        int err = Pa_WriteStream(outStream, buffer, BUFFER_SIZE/2);
        if(err != paNoError){
            qDebug("Error writing to stream:\n %s", Pa_GetErrorText(err));
            break;
        }

        if(abort){
            break;
        }

        read_count = fileHandle->readRaw(buffer, BUFFER_SIZE);
    }

    closeAudio();
}
