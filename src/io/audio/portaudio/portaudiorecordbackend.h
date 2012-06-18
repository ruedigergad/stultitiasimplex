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

#ifndef PORTAUDIORECORDBACKEND_H
#define PORTAUDIORECORDBACKEND_H

#include "src/io/audio/abstractaudiorecorderbackend.h"
#include "portaudiorecordthread.h"

#include <portaudio.h>
#include <QTimer>

#define BUFFER_SIZE 1024

class PortAudioRecordBackend : public AbstractAudioRecorderBackend
{
    Q_OBJECT

public:
    PortAudioRecordBackend();
    ~PortAudioRecordBackend();

protected:
    void startRecordHook();
    void stopRecordHook();

private:
    void closeAudio();
    int closeRecordStream();
    int closeVuMeterStream();
    int createRecordStream();
    int createVuMeterStream();
    int initAudio();

    int deviceId;
    PaStream *recordStream;
    PortAudioRecordThread *recordThread;
    PaStream *vuMeterStream;
    QTimer *vuMeterTimer;

private slots:
    void vuMeterTimerSlot();
};

#endif // PORTAUDIORECORDBACKEND_H
