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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "src/ui/dialog/editbuttondialog.h"
#include "src/data/soundfilelist.h"
#include "src/ui/soundbutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createContent();
    void openAboutDialog();

    void addButton();
    void deleteButton();
    void editButton();
    void recordSound();
    void reorder();

    void editSettings();

    void nextPage();
    void previousPage();

    void disableButtons();
    void enableButtons();

private:
    void addActions();
    void addMenu();
    void cleanContent();
    void getSettings();

    int getItemsPerPage();

    QMenu *mainMenu;
    QWidget *mainWidget;

    QAction *aboutDialogAction;
    QAction *addButtonAction;
    QAction *deleteSoundAction;
    QAction *editButtonAction;
    QAction *recordSoundAction;
    QAction *reorderAction;
    QAction *settingsAction;

    QGridLayout *mainLayout;
    QList<SoundButton *> *buttons;
    QPushButton *nextButton;
    QPushButton *prevButton;

    SoundFileList *soundFileList;

    int columns;
    int rows;
    int page;
    bool playing;
};

#endif // MAINWINDOW_H
