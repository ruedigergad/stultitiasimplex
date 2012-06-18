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
#include <math.h>

PortAudioRecordBackend::PortAudioRecordBackend(){
    qDebug("Using PortAudio record backend...");

    initAudio();
    createVuMeterStream();

    vuMeterTimer = new QTimer(this);
    connect(vuMeterTimer, SIGNAL(timeout()), this, SLOT(vuMeterTimerSlot()));
    vuMeterTimer->start(40);

    recordThread = new PortAudioRecordThread();
}

PortAudioRecordBackend::~PortAudioRecordBackend(){
    delete recordThread;
    closeAudio();
}

void PortAudioRecordBackend::closeAudio(){
    int err;

    closeVuMeterStream();

    err = Pa_Terminate();
    if(err != paNoError){
        qDebug("Error terminating port audio:\n %s", Pa_GetErrorText(err));
    }
}

int PortAudioRecordBackend::closeRecordStream(){
    int err;

    if(recordStream != NULL){
        err = Pa_StopStream(recordStream);
        if(err != paNoError){
            qDebug("Error stopping stream:\n %s", Pa_GetErrorText(err));
            return -1;
        }

        err = Pa_CloseStream(recordStream);
        if(err != paNoError){
            qDebug("Error closing stream:\n %s", Pa_GetErrorText(err));
            return -2;
        }

        recordStream = NULL;
    }

    return 0;
}

int PortAudioRecordBackend::closeVuMeterStream(){
    int err;

    if(vuMeterStream != NULL){
        err = Pa_StopStream(vuMeterStream);
        if(err != paNoError){
            qDebug("Error stopping stream:\n %s", Pa_GetErrorText(err));
            return -1;
        }

        err = Pa_CloseStream(vuMeterStream);
        if(err != paNoError){
            qDebug("Error closing stream:\n %s", Pa_GetErrorText(err));
            return -2;
        }

        vuMeterStream = NULL;
    }

    return 0;
}

int PortAudioRecordBackend::createRecordStream(){
    int err;
    PaStreamParameters streamParams;

    streamParams.device = deviceId;
    streamParams.channelCount = sndFileHandle->channels();
    streamParams.sampleFormat = paInt16;
    streamParams.suggestedLatency = Pa_GetDeviceInfo(streamParams.device)->defaultHighOutputLatency;
    streamParams.hostApiSpecificStreamInfo = NULL;

    err = Pa_IsFormatSupported(&streamParams, NULL, sndFileHandle->samplerate());
    if(err != paNoError){
        qDebug("Format not supported:\n %s", Pa_GetErrorText(err));
        return -1;
    }

    err = Pa_OpenStream(&recordStream, &streamParams, NULL, sndFileHandle->samplerate(), 0, paNoFlag, NULL, NULL);
    if(err != paNoError){
        qDebug("Error opening stream:\n %s", Pa_GetErrorText(err));
        return -2;
    }

    err = Pa_StartStream(recordStream);
    if(err != paNoError){
        qDebug("Error starting stream:\n %s", Pa_GetErrorText(err));
        return -3;
    }

    return 0;
}

int PortAudioRecordBackend::createVuMeterStream(){
    int err;
    PaStreamParameters streamParams;

    streamParams.device = deviceId;
    streamParams.channelCount = 1;
    streamParams.sampleFormat = paFloat32;
    streamParams.suggestedLatency = Pa_GetDeviceInfo(streamParams.device)->defaultHighOutputLatency;
    streamParams.hostApiSpecificStreamInfo = NULL;

    err = Pa_IsFormatSupported(&streamParams, NULL, 11025);
    if(err != paNoError){
        qDebug("Format not supported:\n %s", Pa_GetErrorText(err));
        return -1;
    }

    err = Pa_OpenStream(&vuMeterStream, &streamParams, NULL, 11025, 0, paNoFlag, NULL, NULL);
    if(err != paNoError){
        qDebug("Error opening stream:\n %s", Pa_GetErrorText(err));
        return -2;
    }

    err = Pa_StartStream(vuMeterStream);
    if(err != paNoError){
        qDebug("Error starting stream:\n %s", Pa_GetErrorText(err));
        return -3;
    }

    return 0;
}

int PortAudioRecordBackend::initAudio(){
    int err;
    int devCount;
    deviceId = 0;

    err = Pa_Initialize();
    if(err != paNoError){
        qDebug("Error initializing port audio:\n %s", Pa_GetErrorText(err));
        return -1;
    }

    devCount = Pa_GetDeviceCount();
    if(devCount < 0){
        qDebug("Got negative number of devices: %d", devCount);
        qDebug("Textual error message is:\n %s", Pa_GetErrorText(devCount));
        return -2;
    }

    for(int i = 0; i < devCount; i++){
        const PaDeviceInfo *devInfo = Pa_GetDeviceInfo(i);
        qDebug("Found device: %s", devInfo->name);
#ifdef WIN32
        if(strcmp("Microsoft Soundmapper - Input", devInfo->name) == 0){
            deviceId = i;
            qDebug("Using %s with id %d as input.", devInfo->name, deviceId);
        }
#else
        if(strcmp("default", devInfo->name) == 0){
            deviceId = i;
            qDebug("Using %s with id %d as input.", devInfo->name, deviceId);
        }
#endif
    }

    return 0;
}

void PortAudioRecordBackend::startRecordHook(){
    vuMeterTimer->stop();
    closeVuMeterStream();
    createRecordStream();
    recordThread->startRecording(recordStream, sndFileHandle);
}

void PortAudioRecordBackend::stopRecordHook(){
    recordThread->stopRecording();
    closeRecordStream();
    createVuMeterStream();
    vuMeterTimer->start(40);
}

void PortAudioRecordBackend::vuMeterTimerSlot(){
    int err;
    signed long availableFrames;
    float volume;

    volume = 0;
    availableFrames = Pa_GetStreamReadAvailable(vuMeterStream);

    if(availableFrames > 0){
        float *buffer = new float[availableFrames];
        err = Pa_ReadStream(vuMeterStream, buffer, availableFrames);

        if(err != paNoError){
            qDebug("Error reading from vuMeter stream:\n %s", Pa_GetErrorText(err));
            updateVuMeter(&volume);
            return;
        }

        for(int i = 0; i < availableFrames; i++){
            volume = fmax(volume, fabs(buffer[i]));
        }

        if(volume < 0){
            volume = 0;
        }

        if(volume > 1){
            volume = 1;
        }

        updateVuMeter(&volume);

    }else{
        updateVuMeter(&volume);

#ifndef WIN32
        /*
         * FIXME:
         * Quite a hack to resolve an issue where the stream unexpectedly aborted.
         * Here we simply restart the whole shebang to resolve this situation.
         * This problem does not seem to occur in Windows.
         */
        closeVuMeterStream();
        createVuMeterStream();
#endif
    }
}
