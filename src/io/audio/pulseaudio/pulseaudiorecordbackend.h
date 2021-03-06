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

#ifndef PULSEAUDIORECORDBACKEND_H
#define PULSEAUDIORECORDBACKEND_H

#include <QObject>
#include <QString>

#include "src/io/audio/abstractaudiorecorderbackend.h"

class PulseAudioRecordBackend : public AbstractAudioRecorderBackend
{
public:
    PulseAudioRecordBackend(QString source);
    ~PulseAudioRecordBackend();

protected:
    void startRecordHook();
    void stopRecordHook();

private:
    QString *source;

};

#endif // PULSEAUDIORECORDBACKEND_H
