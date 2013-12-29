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

#include <QDir>

#include "constants.h"


QString Constants::CSV_SEPARATOR = ";";

#ifndef Q_WS_MAEMO_5
QString Constants::WORK_DIR = QDir::home().absolutePath() + "/.stultitiaSimplex";
#else
QString Constants::WORK_DIR = QDir::home().absolutePath() + "/.stultitiaSimplex";
#endif
QString Constants::SOUNDLIST_FILE = WORK_DIR + "/buttons.csv";
QString Constants::SOUNDS_DIR = WORK_DIR + "/sounds";
QString Constants::VERSION = "1.3.1";

QString Constants::VOLUME = "sound/volume";
QString Constants::VOLUME_OVERRIDE = "sound/volume_override";

Constants::Constants()
{
}
