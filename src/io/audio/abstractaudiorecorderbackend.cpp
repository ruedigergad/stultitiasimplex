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

#include "abstractaudiorecorderbackend.h"

AbstractAudioRecorderBackend::AbstractAudioRecorderBackend()
{
}

void AbstractAudioRecorderBackend::processData(const void *data, size_t length){
//    qDebug("Entering RecordDialog::dataProcessed()...");

    sndFileHandle->writeRaw(data, length);

    if(sndFileHandle->error()){
        qDebug("Error writing to file:\n %s", sndFileHandle->strError());
    }

}

void AbstractAudioRecorderBackend::startRecording(QString fileName){
    qDebug("Entring RecordDialog::startRecording()...");

    const char *path = fileName.toLocal8Bit().constData();

    sndFileHandle = new SndfileHandle(path,
                                  SFM_WRITE,
                                  SF_FORMAT_PCM_16 | SF_FORMAT_WAV,
                                  1,
                                  22050);

    if(sndFileHandle->error()){
        qDebug("Error opening file:\n %s", sndFileHandle->strError());
    }else{
        startRecordHook();
    }
}

void AbstractAudioRecorderBackend::stopRecording(){
    qDebug("Entring RecordDialog::stopRecording()...");

    stopRecordHook();

    sndFileHandle->writeSync();
    delete sndFileHandle;
}

void AbstractAudioRecorderBackend::updateVuMeter(const float *data){
    float vol = *data;

    emit updateVuMeterSignal(vol);
}
