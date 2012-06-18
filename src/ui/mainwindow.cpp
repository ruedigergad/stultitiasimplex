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
#include <QSettings>

#include "mainwindow.h"
#include "src/constants.h"
#include "src/ui/dialog/aboutdialog.h"
#include "src/ui/dialog/editbuttondialog.h"
#include "src/ui/dialog/recorddialog.h"
#include "src/ui/dialog/reorderdialog.h"
#include "src/ui/dialog/settingsdialog.h"
#include "src/ui/dialog/soundfilelistdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QCoreApplication::setOrganizationName("StultitiaSimplex");
    QCoreApplication::setOrganizationDomain("http://sourceforge.net/projects/stultitiasimple");
    QCoreApplication::setApplicationName("StultitiaSimplex");

    // Create work dir etc.
    QDir dir = QDir(Constants::WORK_DIR);
    if(! dir.exists()){
        dir.mkdir(Constants::WORK_DIR);
    }

    if(! dir.exists(Constants::SOUNDS_DIR)){
        dir.mkdir(Constants::SOUNDS_DIR);
    }

    // Create rest...
    soundFileList = new SoundFileList();
    connect(soundFileList, SIGNAL(changed()), this, SLOT(createContent()));

    buttons = new QList<SoundButton *>();
    mainLayout = 0;
    mainWidget = 0;
    nextButton = 0;
    prevButton = 0;
    page = 0;
    playing = false;

    getSettings();

    addActions();
    addMenu();

    createContent();
}

MainWindow::~MainWindow()
{
    qDebug("Cleaning up...");
    delete soundFileList;
    delete aboutDialogAction;
    delete addButtonAction;
    delete editButtonAction;
    delete recordSoundAction;
    delete settingsAction;
}

void MainWindow::addActions(){
    addButtonAction = new QAction(tr("&Add Button"), this);
    connect(addButtonAction, SIGNAL(triggered()), this, SLOT(addButton()));

    deleteSoundAction = new QAction(tr("&Delete Button"), this);
    connect(deleteSoundAction, SIGNAL(triggered()), this, SLOT(deleteButton()));

    editButtonAction = new QAction(tr("&Edit Button"), this);
    connect(editButtonAction, SIGNAL(triggered()), this, SLOT(editButton()));

    recordSoundAction = new QAction(tr("&Record Sound"), this);
    connect(recordSoundAction, SIGNAL(triggered()), this, SLOT(recordSound()));

    reorderAction = new QAction(tr("Re&order Buttons"), this);
    connect(reorderAction, SIGNAL(triggered()), this, SLOT(reorder()));

    settingsAction = new QAction(tr("&Settings"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(editSettings()));

    aboutDialogAction = new QAction(tr("A&bout"), this);
    connect(aboutDialogAction, SIGNAL(triggered()), this, SLOT(openAboutDialog()));
}

void MainWindow::addButton(){
    EditButtonDialog dialog(this);
    qDebug("Opening addButton...");
    if(dialog.exec()){
        qDebug("Adding new sound.");
        soundFileList->add(dialog.getFile());
    }
}

void MainWindow::addMenu(){
    mainMenu = menuBar()->addMenu(tr("&File"));
    mainMenu->addAction(addButtonAction);
    mainMenu->addAction(deleteSoundAction);
    mainMenu->addAction(editButtonAction);
    mainMenu->addAction(reorderAction);
    mainMenu->addAction(recordSoundAction);
    mainMenu->addAction(settingsAction);
    mainMenu->addAction(aboutDialogAction);
}

void MainWindow::cleanContent(){
    if(mainWidget != 0 && mainWidget->isVisible()){
        mainWidget->close();
    }

    if(buttons != 0){
        while(! buttons->isEmpty()){
            delete buttons->takeFirst();
        }
    }

    if(nextButton != 0){
        delete nextButton;
    }

    if(prevButton != 0){
        delete prevButton;
    }

    if(mainLayout != 0){
        delete mainLayout;
    }
}

void MainWindow::createContent(){
    qDebug("Entering MainWindow::createContent()...");
    cleanContent();

    const QList<SoundFile *> *files = soundFileList->getList();

    int itemsPerPage = getItemsPerPage();
    bool morePages = files->size() > (itemsPerPage * (page + 1));

    qDebug("Items per page: %d", itemsPerPage);
    qDebug("More pages: %d", morePages);

    mainLayout = new QGridLayout();

    for(int i = 0; i < rows; i++){
        int relativeIndex = (page * itemsPerPage) + (rows * i);

        qDebug("Index: %d; Length: %d", relativeIndex, files->length());
        if((relativeIndex) >= files->length()){
            break;
        }

        if(i < (rows-1)){
            for(int j = 0; j < columns; j++){
                relativeIndex = (page * itemsPerPage) + (columns * i) + j;
                qDebug("Index: %d; Length: %d", relativeIndex, files->length());

                if((relativeIndex) >= files->length()){
                    break;
                }

                SoundFile * file = files->at(relativeIndex);

                SoundButton *button = new SoundButton(0, file);
                connect(button, SIGNAL(playingStarted()), this, SLOT(disableButtons()));
                connect(button, SIGNAL(playingStopped()), this, SLOT(enableButtons()));
                button->setEnabled(! playing);
#ifndef Q_WS_MAEMO_5
                button->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
#endif

                mainLayout->addWidget(button, i, j);
                buttons->append(button);
            }
        }else{
            for(int j = 0; j < (columns - 2); j++){
                int relativeIndex = (page * itemsPerPage) + (columns * i) + j;

                if((relativeIndex) >= files->length()){
                    break;
                }

                SoundFile * file = files->at(relativeIndex);

                SoundButton *button = new SoundButton(0, file);
                connect(button, SIGNAL(playingStarted()), this, SLOT(disableButtons()));
                connect(button, SIGNAL(playingStopped()), this, SLOT(enableButtons()));
                button->setEnabled(! playing);
#ifndef Q_WS_MAEMO_5
                button->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
#endif

                mainLayout->addWidget(button, i, j+1);
                buttons->append(button);
            }
        }
    }

    nextButton = new QPushButton();
    nextButton->setText(tr(">"));
    nextButton->setEnabled(page != 0 || morePages);
#ifndef Q_WS_MAEMO_5
    nextButton->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
#endif
    connect(nextButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    mainLayout->addWidget(nextButton, rows-1, columns-1);

    prevButton = new QPushButton();
    prevButton->setText(tr("<"));
    prevButton->setEnabled(page != 0 || morePages);
#ifndef Q_WS_MAEMO_5
    prevButton->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
#endif
    connect(prevButton, SIGNAL(clicked()), this, SLOT(previousPage()));
    mainLayout->addWidget(prevButton, rows-1, 0);

    mainWidget = new QWidget();
    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainLayout);
}

void MainWindow::deleteButton(){
    SoundFileListDialog listDialog(0, soundFileList);
    if(listDialog.exec()){
        SoundFile *selection = listDialog.getSelection();

        QMessageBox mB(this);
        mB.setText("Delete \"" + selection->getDescription() + "\"?");
        mB.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        if(mB.exec() == QMessageBox::Ok){
            soundFileList->remove(selection);
        }
    }
}

void MainWindow::disableButtons(){
    qDebug("Disabling buttons...");
    for(int i = 0; i < buttons->count(); i++){
        buttons->at(i)->setEnabled(false);
    }
    nextButton->setEnabled(false);
    prevButton->setEnabled(false);

    playing = true;
}

void MainWindow::editSettings(){
    SettingsDialog dialog;
    if(dialog.exec()){
        getSettings();
        createContent();
    }
}

void MainWindow::enableButtons(){
    qDebug("Enabling buttons...");
    const QList<SoundFile *> *files = soundFileList->getList();
    int itemsPerPage = getItemsPerPage();
    bool morePages = files->size() > (itemsPerPage * (page + 1));

    for(int i = 0; i < buttons->length(); i++){
        buttons->at(i)->setEnabled(true);
    }

    nextButton->setEnabled(page != 0 || morePages);
    prevButton->setEnabled(page != 0 || morePages);

    playing = false;
}

void MainWindow::editButton(){
    SoundFileListDialog listDialog(0, soundFileList);
    if(listDialog.exec()){
        EditButtonDialog editDialog(this, listDialog.getSelection());
        editDialog.exec();
    }
}

int MainWindow::getItemsPerPage(){
    return (columns * rows) - 2;
}

void MainWindow::getSettings(){
    QSettings settings;
    columns = settings.value(SettingsDialog::COLUMNS).toInt();
    rows = settings.value(SettingsDialog::ROWS).toInt();

    // Set default values on first start.
    if(columns == 0 && rows == 0){
        columns = 3;
        rows = 2;
        settings.setValue(SettingsDialog::COLUMNS, columns);
        settings.setValue(SettingsDialog::ROWS, rows);
        settings.sync();
    }

    // There are always three cases:
    // best case, worst case, and just in case.
    if(columns < 2){
        columns = 2;
    }
    if(rows < 2){
        rows = 2;
    }
}

void MainWindow::nextPage(){
    qDebug("Entering nextPage...");
    page = (++page > (soundFileList->getList()->size() / getItemsPerPage())) ? 0 : page;
    createContent();
}

void MainWindow::openAboutDialog(){
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::previousPage(){
    qDebug("Entering previousPage...");
    page = (--page < 0) ? (soundFileList->getList()->size() / getItemsPerPage()) : page;
    createContent();
}

void MainWindow::recordSound(){
    RecordDialog dialog(this);
    dialog.exec();
}

void MainWindow::reorder(){
    ReorderDialog dialog(this, soundFileList);
    if(dialog.exec()){
        soundFileList->save();
        createContent();
    }
}
