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

#include <QFileDialog>

#include "recorddialog.h"
#include "ui_recorddialog.h"
#include "src/constants.h"

#ifdef UNIX
#include "src/io/audio/pulseaudio/pa_utils.h"
#include "src/io/audio/pulseaudio/pulseaudiorecordbackend.h"
#endif

#ifdef WIN32
#include "src/io/audio/portaudio/portaudiorecordbackend.h"
#endif

RecordDialog::RecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog)
{
    backend = NULL;
    sources = NULL;
    ui->setupUi(this);

    ui->fileEdit->setText(tr("Select File"));

    recording = false;
    ui->recordPushButton->setEnabled(false);

#ifdef WIN32
    backend = new PortAudioRecordBackend();
    ui->sourceLabel->close();
    ui->sourceComboBox->close();
    connect(backend, SIGNAL(updateVuMeterSignal(float)), this, SLOT(setVuMeter(float)), Qt::QueuedConnection);
#endif

#ifdef Q_WS_MAEMO_5
    sources = new QStringList();
    sources->append("Microphone");
    sources->append("Bluetooth");
    sources->append("Monitor");

    ui->sourceComboBox->addItems(*sources);
    ui->sourceComboBox->setCurrentIndex(2);
    connect(ui->sourceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sourceChanged(int)));
    sourceChanged(2);
#elif UNIX
    sources = (QStringList *) get_source_names();

    ui->sourceComboBox->addItems(*sources);
    connect(ui->sourceComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sourceChanged(int)));
    sourceChanged(0);
#endif
}

RecordDialog::~RecordDialog()
{
    delete backend;
    if(sources != NULL){
        delete sources;
    }
    delete ui;
}

void RecordDialog::fileDialog(){
    qDebug("Entering RecordDialog::fileDialog()...");

    QString selectedFile = ui->fileEdit->text();
    if(selectedFile == NULL || selectedFile.compare(tr("Select File")) == 0){
        selectedFile = Constants::SOUNDS_DIR;
    }

    QString newFile = QFileDialog::getSaveFileName(
            this,
            tr("Select audio file."),
            selectedFile,
            tr("Audio files (*.wav)"));

    if(newFile != NULL){
        fileSelected(newFile);
    }
}

void RecordDialog::fileSelected(QString fileName){
    if(fileName != NULL && fileName.compare(tr("Select File")) != 0){
        if(! fileName.endsWith(".wav")){
            fileName += ".wav";
        }

        ui->fileEdit->setText(fileName);
        ui->recordPushButton->setEnabled(true);
    }else{
        ui->recordPushButton->setEnabled(false);
    }
}

void RecordDialog::recordPushed(){
    qDebug("Entering RecordDialog::recordPushed()...");

    if(recording){
        recording = false;
        ui->recordPushButton->setText("Record");
        ui->buttonBox->setEnabled(true);

        backend->stopRecording();
    }else{
        recording = true;
        ui->recordPushButton->setText("Stop");
        ui->buttonBox->setEnabled(false);

        backend->startRecording(ui->fileEdit->text());
    }
}

void RecordDialog::setVuMeter(float volume){
    if(volume < 0){
        return;
    }

    ui->vuMeter->setValue(volume * 100);
}

void RecordDialog::sourceChanged(int index){
    if(backend != NULL){
        delete backend;
        backend = NULL;
    }

#ifdef Q_WS_MAEMO_5
    switch(index){
    case 0:
        backend = new PulseAudioRecordBackend("source.hw0");
        break;
    case 1:
        backend = new PulseAudioRecordBackend("source.hw1");
        break;
    case 2:
        backend = new PulseAudioRecordBackend("sink.hw0.monitor");
        break;
    default:
        qDebug("Unknown source!");
    }
#else
    backend = new PulseAudioRecordBackend(sources->at(index));
#endif
    connect(backend, SIGNAL(updateVuMeterSignal(float)), this, SLOT(setVuMeter(float)), Qt::QueuedConnection);
}
