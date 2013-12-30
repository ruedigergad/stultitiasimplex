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

#if !defined(MEEGO_EDITION_HARMATTAN) && !defined(MER_EDITION_SAILFISH)
#include "src/ui/dialog/settingsdialog.h"
#endif

#include <pulse/simple.h>
#include <pulse/error.h>
#include "src/constants.h"

#include <QDebug>
#include <QSettings>

void on_audio_resource_acquired(audioresource_t *audio_resource, bool acquired, void *user_data)
{
    if (acquired) {
        qDebug() << "Audio resource acquire.";
    } else {
        qDebug() << "Audio resource lost.";
    }
}


PulseAudioPlayerBackend::PulseAudioPlayerBackend() : AbstractAudioPlayerBackend()
{
    qDebug("Using PulseAudio player-backend...");
    m_audioResource = audioresource_init(AUDIO_RESOURCE_GAME, on_audio_resource_acquired, NULL);
}

PulseAudioPlayerBackend::~PulseAudioPlayerBackend() {
    audioresource_free(m_audioResource);
}

void PulseAudioPlayerBackend::run(){
    abort = false;
    int *buffer;
    int err;
    int read_count;

    audioresource_acquire(m_audioResource);

    pa_sample_spec sample_spec;
    sample_spec.channels = fileHandle->channels();
    sample_spec.format = PA_SAMPLE_S16LE;
    sample_spec.rate = fileHandle->samplerate();

    qDebug() << "Playback with " << sample_spec.channels << " at "
             <<  sample_spec.rate << " in " << sample_spec.format << " format.";

    pa_simple *simple_api = NULL;
    simple_api = pa_simple_new(NULL,
                              "StultitiaSimplex",
                              PA_STREAM_PLAYBACK,
                              NULL,
                              "Output",
                              &sample_spec,
                              NULL,
                              NULL,
                              &err);
    if(simple_api == NULL){
        qDebug("Error creating audio output:\n %s", pa_strerror(err));
        audioresource_release(m_audioResource);
        return;
    }

    setVolume();

    buffer = new int[BUFFER_SIZE];

    read_count = fileHandle->readRaw(buffer, BUFFER_SIZE);
    while (read_count > 0) {
        if (abort) {
            qDebug("Aborting audio output...");
            break;
        }

        int count = pa_simple_write(simple_api, buffer, read_count, &err);
        if (count < 0) {
            qDebug("Error playing audio:\n %s", pa_strerror(err));
            break;
        }

        read_count = fileHandle->readRaw(buffer, BUFFER_SIZE);
    }

    pa_simple_free(simple_api);

    restoreVolume();

    audioresource_release(m_audioResource);
}

void PulseAudioPlayerBackend::restoreVolume() {
    if (volumeOverride) {
#if defined(Q_WS_MAEMO_5) || defined(MEEGO_EDITION_HARMATTAN)
        set_stream_volume("sink-input-by-media-role:x-maemo", oldVolume);
#else
        set_volume(0, oldVolume);
#endif
    }
}

void PulseAudioPlayerBackend::setVolume() {
    QSettings settings;

    volumeOverride = settings.value(Constants::VOLUME_OVERRIDE, false).toBool();

    if (volumeOverride) {
        int vol = settings.value(Constants::VOLUME, 0).toInt();
        pa_volume_t newVolume = pa_sw_volume_from_linear(((double) vol)/100.0);
#if defined(Q_WS_MAEMO_5) || defined(MEEGO_EDITION_HARMATTAN)
        oldVolume = get_stream_volume("sink-input-by-media-role:x-maemo");
#else
        oldVolume = get_volume();
#endif
        qDebug("Got volume: %u", oldVolume);
        qDebug("Setting volume: %u", newVolume);

#if defined(Q_WS_MAEMO_5) || defined(MEEGO_EDITION_HARMATTAN)
        set_stream_volume("sink-input-by-media-role:x-maemo", newVolume);
#else
        set_volume(0, newVolume);
#endif
    }
}
