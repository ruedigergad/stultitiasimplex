#-------------------------------------------------
#
# Project created by QtCreator 2010-09-19T10:19:11
#
#-------------------------------------------------

unix:CONFIG += link_pkgconfig


PKGCONFIG += sndfile

win32:PKGCONFIG += portaudio-2.0
unix:PKGCONFIG += libpulse libpulse-simple

win32:INCLUDEPATH += lib_include
win32:LIBS += -Llib -llibportaudio-2 -llibsndfile-1


win32:RC_FILE = res/windows/StultitiaSimplex.rc

QT       += core gui

TARGET = StultitiaSimplex
TEMPLATE = app

RESOURCES = res/StultitiaSimplex.qrc


SOURCES += \
    src/constants.cpp \
    src/main.cpp\
    src/data/soundfile.cpp \
    src/data/soundfilelist.cpp \
    src/io/audio/audioplayer.cpp \
    src/io/audio/abstractaudioplayerbackend.cpp \
    src/io/audio/abstractaudiorecorderbackend.cpp \
    src/ui/dialog/editbuttondialog.cpp \
    src/ui/mainwindow.cpp \
    src/ui/soundbutton.cpp \
    src/ui/dialog/aboutdialog.cpp \
    src/ui/dialog/recorddialog.cpp \
    src/ui/dialog/reorderdialog.cpp \
    src/ui/dialog/settingsdialog.cpp \
    src/ui/dialog/soundfilelistdialog.cpp \


unix:SOURCES += \
    src/io/audio/pulseaudio/pa_context_helper.cpp \
    src/io/audio/pulseaudio/pa_streams_helper.cpp \
    src/io/audio/pulseaudio/pa_utils.cpp \
    src/io/audio/pulseaudio/pa_volume_helper.cpp \
    src/io/audio/pulseaudio/pulseaudioplayerbackend.cpp \
    src/io/audio/pulseaudio/pulseaudiorecordbackend.cpp \


win32:SOURCES += \
    src/io/audio/portaudio/portaudioplayerbackend.cpp \
    src/io/audio/portaudio/portaudiorecordbackend.cpp \
    src/io/audio/portaudio/portaudiorecordthread.cpp \


HEADERS += \
    src/constants.h \
    src/data/soundfile.h \
    src/data/soundfilelist.h \
    src/io/audio/audioplayer.h \
    src/io/audio/abstractaudioplayerbackend.h \
    src/io/audio/abstractaudiorecorderbackend.h \
    src/ui/dialog/editbuttondialog.h \
    src/ui/mainwindow.h \
    src/ui/soundbutton.h \
    src/ui/dialog/aboutdialog.h \
    src/ui/dialog/recorddialog.h \
    src/ui/dialog/reorderdialog.h \
    src/ui/dialog/settingsdialog.h \
    src/ui/dialog/soundfilelistdialog.h \


unix:HEADERS += \
    src/io/audio/pulseaudio/pa_context_helper.h \
    src/io/audio/pulseaudio/pa_streams_helper.h \
    src/io/audio/pulseaudio/pa_utils.h \
    src/io/audio/pulseaudio/pa_volume_helper.h \
    src/io/audio/pulseaudio/pulseaudioplayerbackend.h \
    src/io/audio/pulseaudio/pulseaudiorecordbackend.h \


win32:HEADERS += \
    src/io/audio/portaudio/portaudioplayerbackend.h \
    src/io/audio/portaudio/portaudiorecordbackend.h \
    src/io/audio/portaudio/portaudiorecordthread.h \


FORMS += \
    forms/aboutdialog.ui \
    forms/editbuttondialog.ui \
    forms/recorddialog.ui \
    forms/reorderdialog.ui \
    forms/settingsdialog.ui \
    forms/soundfilelistdialog.ui \


unix {
   DEFINES += UNIX
   INSTALLS += target desktop icon48
   target.path = /opt/maemo/usr/bin
   desktop.path = /usr/share/applications/hildon
   desktop.files += res/maemo/usr/share/applications/hildon/stultitiasimplex.desktop
   icon48.path = /usr/share/icons/hicolor/48x48/apps
   icon48.files += res/maemo/usr/share/icons/hicolor/48x48/hildon/stultitiasimplex.png
}

