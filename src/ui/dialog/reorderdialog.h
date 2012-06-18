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

#ifndef REORDERDIALOG_H
#define REORDERDIALOG_H

#include <QDialog>
#include <QStringListModel>
#include "src/data/soundfilelist.h"

namespace Ui {
    class ReorderDialog;
}

class ReorderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReorderDialog(QWidget *parent = 0, SoundFileList *list = 0);
    ~ReorderDialog();

private slots:
    void fillWidget(int selection);

    void moveBottom();
    void moveDown();
    void moveTenDown();
    void moveTenUp();
    void moveTop();
    void moveUp();

private:
    int getSelectionIndex();

    Ui::ReorderDialog *ui;

    SoundFileList *list;
    SoundFile *selection;
};

#endif // REORDERDIALOG_H
