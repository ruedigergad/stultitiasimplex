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

#ifndef PORTAUDIOPLAYERBACKEND_H
#define PORTAUDIOPLAYERBACKEND_H

#include "src/io/audio/abstractaudioplayerbackend.h"

#include <portaudio.h>

#define BUFFER_SIZE 1024

class PortAudioPlayerBackend : public AbstractAudioPlayerBackend
{
public:
    PortAudioPlayerBackend();

    void run();

private:
    void closeAudio();
    int initAudio();

    PaStream *outStream;
    PaStreamParameters streamParams;

};

#endif // PORTAUDIOPLAYERBACKEND_H
