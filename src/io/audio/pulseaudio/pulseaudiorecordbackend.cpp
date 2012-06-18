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

#include "pulseaudiorecordbackend.h"

#include "pa_utils.h"

PulseAudioRecordBackend::PulseAudioRecordBackend(QString source)
{
    qDebug("Using PulseAudio for recording...");
    context_create();

    this->source = new QString(source);
    qDebug("Recording from: %s", this->source->toLocal8Bit().constData());
    connect_to_vu_meter_stream(this->source->toLocal8Bit().constData(), this);
}

PulseAudioRecordBackend::~PulseAudioRecordBackend(){
    context_stop();
    delete source;
}

void PulseAudioRecordBackend::startRecordHook(){
    connect_to_record_stream(source->toLocal8Bit().constData(), this);
}

void PulseAudioRecordBackend::stopRecordHook(){
    disconnect_record_stream();
}
