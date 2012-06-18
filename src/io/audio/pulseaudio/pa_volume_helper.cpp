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

#include "pa_volume_helper.h"
#include "pa_utils.h"

pa_volume_t volume = 0;
bool got_volume = false;

pa_volume_t get_stream_volume(const char *stream_name){
    volume = 0;
    got_volume = false;

    context_create();

    pa_ext_stream_restore_read(context, get_stream_volume_callback, (void *) stream_name);
    do{
        pa_threaded_mainloop_lock(threaded_main_loop);
        pa_threaded_mainloop_wait(threaded_main_loop);
        qDebug("Received signal...");
    }while(! got_volume);
    pa_threaded_mainloop_unlock(threaded_main_loop);

    context_stop();

    return volume;
}

pa_volume_t get_volume(int index){
    volume = 0;
    got_volume = false;

    context_create();

    pa_context_get_sink_info_by_index(context, index, get_volume_callback, NULL);
    do{
        pa_threaded_mainloop_lock(threaded_main_loop);
        pa_threaded_mainloop_wait(threaded_main_loop);
        qDebug("Received signal...");
    }while(! got_volume);
    pa_threaded_mainloop_unlock(threaded_main_loop);

    context_stop();

    return volume;
}

void get_stream_volume_callback(pa_context *context, const pa_ext_stream_restore_info *stream_info, int eol, void *data){
    (void) context;

    const char *stream_name = (const char *) data;

    if(eol == 0){
        if(stream_info == NULL){
            qDebug("Stream info is NULL...");
            return;
        }

        if(! pa_cvolume_valid(&(stream_info->volume))){
            qDebug("Stream volume was invalid...");
            return;
        }

        qDebug("Stream: %s; Volume: %u; Channels: %d; ChannelMap: %d",
               stream_info->name,
               stream_info->volume.values[0],
               stream_info->channel_map.channels,
               stream_info->channel_map.map[0]);

        if(strcmp(stream_info->name, stream_name) == 0){
            volume = stream_info->volume.values[0];
            got_volume = true;
        }
    }else{
        qDebug("Sending signal...\n");
        if(! got_volume){
            qDebug("Error reading volume for stream: %s", stream_name);
            got_volume = true;
        }
        pa_threaded_mainloop_signal(threaded_main_loop, 0);
    }
}

void get_volume_callback(pa_context *context, const pa_sink_info *sink_info, int eol, void *data){
    (void) context;
    (void) eol;
    (void) data;

    if(! got_volume){
        volume = sink_info->volume.values[0];
        got_volume = true;

        qDebug("Volume: %u, Channels: %d", volume, sink_info->volume.channels);
        pa_threaded_mainloop_signal(threaded_main_loop, 0);
    }
}

void set_stream_volume(const char* stream_name, pa_volume_t vol){
    context_create();

    pa_cvolume volume;
    pa_cvolume_init(&volume);
    pa_cvolume_set(&volume, 1, vol);

    if(! pa_cvolume_valid(&volume)){
        qDebug("Invalid volume setting!");
        goto error;
    }

    pa_ext_stream_restore_info info;
    info.name = stream_name;
    info.volume = volume;
    info.channel_map.channels = 1;
    info.channel_map.map[0] = PA_CHANNEL_POSITION_MONO;
    info.mute = false;
    info.device = NULL;

    qDebug("Setting stream volume: %u", info.volume.values[0]);
    pa_ext_stream_restore_write(context,
                                PA_UPDATE_REPLACE,
                                &info, 1, TRUE,
                                set_stream_volume_callback,
                                (void *) stream_name);

    pa_threaded_mainloop_lock(threaded_main_loop);
    pa_threaded_mainloop_wait(threaded_main_loop);
    pa_threaded_mainloop_unlock(threaded_main_loop);

    error:
    context_stop();
}

void set_stream_volume_callback(pa_context *context, int success, void *data){
    (void) context;

    qDebug("Setting volume for stream \"%s\" returned: %d", (const char*) data, success);
    pa_threaded_mainloop_signal(threaded_main_loop, 0);
}

void set_volume(int index, pa_volume_t vol){
    context_create();

    pa_cvolume volume;
    pa_cvolume_init(&volume);
    pa_cvolume_set(&volume, 2, vol);

    if(! pa_cvolume_valid(&volume)){
        qDebug("Invalid volume setting!");
        goto error;
    }

    qDebug("Setting volume: %u", volume.values[0]);
    pa_context_set_sink_volume_by_index(context, index, &volume, set_volume_callback, NULL);

    pa_threaded_mainloop_lock(threaded_main_loop);
    pa_threaded_mainloop_wait(threaded_main_loop);
    pa_threaded_mainloop_unlock(threaded_main_loop);

    error:
    context_stop();
}

void set_volume_callback(pa_context *context, int success, void *data){
    (void) context;
    (void) data;

    qDebug("Setting volume returned: %d", success);
    pa_threaded_mainloop_signal(threaded_main_loop, 0);
}
