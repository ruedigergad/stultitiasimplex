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

#ifndef PA_STREAMS_HELPER_H
#define PA_STREAMS_HELPER_H

#include "src/io/audio/abstractaudiorecorderbackend.h"

#include <pulse/context.h>
#include <pulse/proplist.h>
#include <pulse/stream.h>

struct record_settings{
    AbstractAudioRecorderBackend *backend;
    int method;
};

extern pa_stream *streams[2];

void disconnect_record_stream();

void connect_to_record_stream(const char *source, AbstractAudioRecorderBackend *backend);
void connect_to_vu_meter_stream(const char *source, AbstractAudioRecorderBackend *backend);

void stream_read_callback(pa_stream *stream, size_t length, void *data);
void stream_state_callback(pa_stream *stream, void *data);

#endif // PA_STREAMS_HELPER_H
