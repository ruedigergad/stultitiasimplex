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

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "src/io/audio/abstractaudioplayerbackend.h"

#include <QString>

class AudioPlayer : public QObject
{
    Q_OBJECT

public:
    AudioPlayer();
    ~AudioPlayer();

    void play(QString file);

signals:
    void finished();

private:
    void createAbortDialog();

    AbstractAudioPlayerBackend *backend;

private slots:
    void abortPlay(int ret);
};

#endif // AUDIOPLAYER_H
