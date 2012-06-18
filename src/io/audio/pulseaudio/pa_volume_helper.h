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

#ifndef PA_VOLUME_HELPER_H
#define PA_VOLUME_HELPER_H

#include <pulse/introspect.h>
#include <pulse/ext-stream-restore.h>

extern pa_volume_t volume;
extern bool got_volume;

pa_volume_t get_stream_volume(const char *stream_name);
pa_volume_t get_volume(int index = 0);

void get_stream_volume_callback(pa_context *context, const pa_ext_stream_restore_info *stream_info, int eol, void *data);
void get_volume_callback(pa_context *context, const pa_sink_info *sink_info, int eol, void *data);

void set_stream_volume(const char *stream_name, pa_volume_t vol);
void set_stream_volume_callback(pa_context *context, int success, void *data);
void set_volume(int index, pa_volume_t vol);
void set_volume_callback(pa_context *context, int success, void *data);

#endif // PA_VOLUME_HELPER_H
