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

#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include <QStringList>

#include "src/io/audio/abstractaudiorecorderbackend.h"

namespace Ui {
    class RecordDialog;
}

class RecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordDialog(QWidget *parent = 0);
    ~RecordDialog();

private slots:
    void fileDialog();
    void fileSelected(QString fileName);
    void recordPushed();
    void setVuMeter(float volume);
    void sourceChanged(int index);

private:
    Ui::RecordDialog *ui;

    AbstractAudioRecorderBackend *backend;

    bool recording;
    QStringList *sources;
};

#endif // RECORDDIALOG_H
