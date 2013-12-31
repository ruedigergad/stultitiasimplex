/*
 *  Copyright 2013 Ruediger Gad
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

#include "qmultimediaaudiorecorder.h"

#include <QDebug>

QMultimediaAudioRecorder::QMultimediaAudioRecorder(QObject *parent) :
    QObject(parent)
{
    m_audioRecorder = new QAudioRecorder();
    m_audioInputs = m_audioRecorder->audioInputs();

    qDebug() << "Available audio inputs: " << m_audioInputs;

    foreach (QString input, m_audioInputs) {
        qDebug() << input << ": " << m_audioRecorder->audioInputDescription(input);
    }

    qDebug() << "Supported audio codecs: " << m_audioRecorder->supportedAudioCodecs();
    qDebug() << "Supported containers: " << m_audioRecorder->supportedContainers();
}

QMultimediaAudioRecorder::~QMultimediaAudioRecorder() {
    delete m_audioRecorder;
}

void QMultimediaAudioRecorder::connectAudio(int index) {

}

void QMultimediaAudioRecorder::disconnectAudio() {

}

void QMultimediaAudioRecorder::startRecord(QString fileName) {

}

void QMultimediaAudioRecorder::stopRecord() {

}

void QMultimediaAudioRecorder::updateVuMeter(QAudioBuffer aBuf) {

}
