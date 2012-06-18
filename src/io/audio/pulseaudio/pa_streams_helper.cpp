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

#include "pa_streams_helper.h"
#include "pa_utils.h"

pa_stream *streams[2] = {NULL, NULL};


void connect_to_record_stream(const char* source, AbstractAudioRecorderBackend *backend){
    record_settings *settings;

    pa_buffer_attr attr;
    attr.maxlength = (uint32_t) -1;
    attr.fragsize = (uint32_t) -1;

    pa_sample_spec sample_specification;
    sample_specification.format = PA_SAMPLE_S16LE;
    sample_specification.rate = 22050;
    sample_specification.channels = 1;

    settings = new record_settings;
    settings->backend = backend;
    settings->method = 0;

    qDebug("Connecting to record stream...");
    streams[settings->method] = pa_stream_new(context, "Record Stream", &sample_specification, NULL);

    pa_stream_set_state_callback(streams[settings->method], stream_state_callback, settings);
    pa_stream_connect_record(streams[settings->method],
                             source, &attr,
                             (pa_stream_flags_t) (PA_STREAM_START_UNMUTED) );
}

void connect_to_vu_meter_stream(const char* source, AbstractAudioRecorderBackend *backend){
    record_settings *settings;

    pa_buffer_attr attr;
    attr.fragsize = sizeof(float);
    attr.maxlength = (uint32_t) -1;

    pa_sample_spec sample_specification;
    sample_specification.format = PA_SAMPLE_FLOAT32;
    sample_specification.rate = 25;
    sample_specification.channels = 1;

    settings = new record_settings;
    settings->backend = backend;
    settings->method = 1;

    qDebug("Connecting to VU meter stream...");
    streams[settings->method] = pa_stream_new(context, "VU Meter Stream", &sample_specification, NULL);

    pa_stream_set_state_callback(streams[settings->method], stream_state_callback, settings);
    pa_stream_connect_record(streams[settings->method], source, &attr, (pa_stream_flags_t) (PA_STREAM_DONT_MOVE|PA_STREAM_PEAK_DETECT|PA_STREAM_ADJUST_LATENCY));
}

void disconnect_record_stream(){
    if(streams[0] != NULL){
        pa_threaded_mainloop_lock(threaded_main_loop);
        pa_stream_disconnect(streams[0]);
        qDebug("Waiting for stream to terminate...");
        pa_threaded_mainloop_wait(threaded_main_loop);
        streams[0] = NULL;
        pa_threaded_mainloop_unlock(threaded_main_loop);
    }
}

void stream_read_callback(pa_stream *stream, size_t length, void *data){
    const void *audio_data;

    pa_stream_peek(stream, &audio_data, &length);
    pa_stream_drop(stream);

    record_settings *settings;
    settings = (record_settings *) data;

    if(settings->method == 0){
        settings->backend->processData(audio_data, length);
    }else if(settings->method == 1){
        settings->backend->updateVuMeter((const float*) audio_data);
    }
}

void stream_state_callback(pa_stream *stream, void *data){
    pa_stream_state state = pa_stream_get_state(stream);
    qDebug("Stream state changed: %d", state);

    switch(state){
    case PA_STREAM_READY:
        const pa_sample_spec *spec;
        spec = pa_stream_get_sample_spec(stream);
        qDebug("Sample Specification:\n %d, %d, %s ",
               spec->channels,
               spec->rate,
               pa_sample_format_to_string(spec->format));

        qDebug("Connecting read callback...");
        pa_stream_set_read_callback(stream, stream_read_callback, data);
        break;
    case PA_STREAM_TERMINATED:
        qDebug("Stream terminated. Cleaning up...");

        record_settings *rec_settings;
        rec_settings = (record_settings *) data;
        delete rec_settings;

        qDebug("Cleaning up finished. Sending signal...");
        pa_threaded_mainloop_signal(threaded_main_loop, 0);
        break;
    case PA_STREAM_FAILED:
        qDebug("Connecting to stream failed!");
        break;
    default:
        break;
    }
}
