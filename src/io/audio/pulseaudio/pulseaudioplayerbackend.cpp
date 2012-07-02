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

#include "pulseaudioplayerbackend.h"

#ifndef MEEGO_EDITION_HARMATTAN
#include "src/ui/dialog/settingsdialog.h"
#endif

#include <pulse/simple.h>
#include <pulse/error.h>
#include "src/constants.h"

#include <QSettings>

PulseAudioPlayerBackend::PulseAudioPlayerBackend() : AbstractAudioPlayerBackend()
{
    qDebug("Using PulseAudio player-backend...");
}

void PulseAudioPlayerBackend::run(){
    abort = false;
    int *buffer;
    int err;
    int read_count;

    pa_sample_spec sample_spec;
    sample_spec.channels = fileHandle->channels();
    sample_spec.format = PA_SAMPLE_S16LE;
    sample_spec.rate = fileHandle->samplerate();

    pa_simple *simple_api = NULL;
    simple_api = pa_simple_new(NULL,
/*
 * FIXME: Quite a crude hack to get audio output in silent mode.
 */
#ifdef Q_WS_MAEMO_5
                              "FMRadio",
#else
                              "StultitiaSimplex",
#endif
                              PA_STREAM_PLAYBACK,
                              NULL,
                              "Output",
                              &sample_spec,
                              NULL,
                              NULL,
                              &err);
    if(simple_api == NULL){
        qDebug("Error creating audio output:\n %s", pa_strerror(err));
        goto finish;
    }

    setVolume();

    buffer = new int[BUFFER_SIZE];

    read_count = fileHandle->readRaw(buffer, BUFFER_SIZE);
    while(read_count > 0){
        if(abort){
            qDebug("Aborting audio output...");
            goto finish;
        }

        int count = pa_simple_write(simple_api, buffer, read_count, &err);
        if(count < 0){
            qDebug("Error playing audio:\n %s", pa_strerror(err));
            goto finish;
        }

        read_count = fileHandle->readRaw(buffer, BUFFER_SIZE);
    }

finish:
    pa_simple_free(simple_api);

    if(volumeOverride){
#ifdef Q_WS_MAEMO_5
        set_stream_volume("sink-input-by-media-role:x-maemo", oldVolume);
#else
        set_volume(0, oldVolume);
#endif
    }
}

void PulseAudioPlayerBackend::setVolume(){
    QSettings settings;

    volumeOverride = settings.value(Constants::VOLUME_OVERRIDE, false).toBool();

    if(volumeOverride){
        int vol = settings.value(Constants::VOLUME, 0).toInt();
        pa_volume_t newVolume = pa_sw_volume_from_linear(((double) vol)/100.0
                                                         );
#ifdef Q_WS_MAEMO_5
        oldVolume = get_stream_volume("sink-input-by-media-role:x-maemo");
#else
        oldVolume = get_volume();
#endif
        qDebug("Got volume: %u", oldVolume);
        qDebug("Setting volume: %u", newVolume);
#ifdef Q_WS_MAEMO_5
        set_stream_volume("sink-input-by-media-role:x-maemo", newVolume);
#else
        set_volume(0, newVolume);
#endif
    }
}
