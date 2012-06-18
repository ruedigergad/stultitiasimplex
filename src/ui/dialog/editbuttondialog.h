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

#ifndef EDITBUTTONDIALOG_H
#define EDITBUTTONDIALOG_H

#include <QDialog>
#include "src/data/soundfilelist.h"

namespace Ui {
    class EditButtonDialog;
}

class EditButtonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditButtonDialog(QWidget *parent = 0, SoundFile *file = 0, SoundFileList *list = 0);
    ~EditButtonDialog();

    void accept();
    SoundFile *getFile();

private slots:
    void fileDialog();
    void updateFileText(QString text);
    void updateLabelText(QString text);

private:
    void updateButtons();

    Ui::EditButtonDialog *ui;

    SoundFile *file;
    SoundFileList *list;

    bool labelUpdated;
    bool fileUpdated;
};

#endif // EDITBUTTONDIALOG_H
