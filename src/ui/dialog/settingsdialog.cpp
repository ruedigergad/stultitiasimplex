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

#include <QSettings>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#ifdef Q_WS_X11
#include "src/io/audio/pulseaudio/pa_utils.h"
#endif

QString SettingsDialog::COLUMNS = "ui/columns";
QString SettingsDialog::ROWS = "ui/rows";

QString SettingsDialog::VOLUME = "sound/volume";
QString SettingsDialog::VOLUME_OVERRIDE = "sound/volume_override";

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QSettings settings;

    ui->columnSpinBox->setValue(settings.value(SettingsDialog::COLUMNS).toInt());
    ui->rowSpinBox->setValue(settings.value(SettingsDialog::ROWS).toInt());

#ifdef WIN32
    ui->volumeLabel->close();
    ui->volumeOverrideCheckbox->close();
    ui->volumeOverrideLabel->close();
    ui->volumeOverrideWarningLabel->close();
    ui->volumeSlider->close();
    ui->volumeSpinBox->close();
#endif

#if defined(Q_WS_X11) && ! defined(Q_WS_MAEMO_5)
    if(pa_available()){
        ui->volumeOverrideCheckbox->setChecked(settings.value(SettingsDialog::VOLUME_OVERRIDE).toBool());
        ui->volumeSpinBox->setValue(settings.value(SettingsDialog::VOLUME).toInt());
    }else{
        ui->volumeLabel->close();
        ui->volumeOverrideCheckbox->close();
        ui->volumeOverrideLabel->close();
        ui->volumeOverrideWarningLabel->close();
        ui->volumeSlider->close();
        ui->volumeSpinBox->close();
    }
#endif

#ifdef Q_WS_MAEMO_5
    ui->volumeOverrideCheckbox->setChecked(settings.value(SettingsDialog::VOLUME_OVERRIDE).toBool());
    ui->volumeSpinBox->setValue(settings.value(SettingsDialog::VOLUME).toInt());
#endif
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept(){
    QSettings settings;

    settings.setValue(SettingsDialog::COLUMNS, ui->columnSpinBox->value());
    settings.setValue(SettingsDialog::ROWS, ui->rowSpinBox->value());

    settings.setValue(SettingsDialog::VOLUME_OVERRIDE, ui->volumeOverrideCheckbox->checkState());
    settings.setValue(SettingsDialog::VOLUME, ui->volumeSpinBox->value());

    settings.sync();

    done(1);
}
