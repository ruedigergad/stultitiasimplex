#-------------------------------------------------
#
# Project created by QtCreator 2010-09-19T10:19:11
#
#-------------------------------------------------

#unix:CONFIG += link_pkgconfig

#PKGCONFIG += sndfile audioresource

win32:PKGCONFIG += portaudio-2.0
#unix:PKGCONFIG += libpulse libpulse-simple

win32:INCLUDEPATH += lib_include
win32:LIBS += -Llib -llibportaudio-2 -llibsndfile-1

win32:RC_FILE = res/windows/StultitiaSimplex.rc

QT += core gui multimedia

TARGET = StultitiaSimplex
TEMPLATE = app

RESOURCES = res/StultitiaSimplex.qrc


SOURCES += \
    src/constants.cpp \
    src/main.cpp\
    src/data/soundfile.cpp \
    src/data/soundfilelist.cpp \
    src/qml/filesystemhelper.cpp \
    src/qml/qmlsettingsadapter.cpp \
    src/qml/soundfilelistsortfilterproxymodel.cpp \
    src/io/audio/qtmultimedia/qmultimediaaudiorecorder.cpp \
    src/io/audio/qtmultimedia/qmultimediavumeterbackend.cpp

#    src/io/audio/audioplayer.cpp \
#    src/io/audio/abstractaudioplayerbackend.cpp \
#    src/io/audio/abstractaudiorecorderbackend.cpp \
#    src/qml/qmlaudioplayer.cpp \
#    src/qml/qmlaudiorecorder.cpp \

#unix:SOURCES += \
#    src/io/audio/pulseaudio/pa_context_helper.cpp \
#    src/io/audio/pulseaudio/pa_streams_helper.cpp \
#    src/io/audio/pulseaudio/pa_utils.cpp \
#    src/io/audio/pulseaudio/pa_volume_helper.cpp \
#    src/io/audio/pulseaudio/pulseaudioplayerbackend.cpp \
#    src/io/audio/pulseaudio/pulseaudiorecordbackend.cpp \


win32:SOURCES += \
    src/io/audio/portaudio/portaudioplayerbackend.cpp \
    src/io/audio/portaudio/portaudiorecordbackend.cpp \
    src/io/audio/portaudio/portaudiorecordthread.cpp \


HEADERS += \
    src/constants.h \
    src/data/soundfile.h \
    src/data/soundfilelist.h \
    src/qml/filesystemhelper.h \
    src/qml/qmlsettingsadapter.h \
    src/qml/soundfilelistsortfilterproxymodel.h \
    src/io/audio/qtmultimedia/qmultimediaaudiorecorder.h \
    src/io/audio/qtmultimedia/qmultimediavumeterbackend.h

#    src/io/audio/audioplayer.h \
#    src/io/audio/abstractaudioplayerbackend.h \
#    src/io/audio/abstractaudiorecorderbackend.h \
#    src/qml/qmlaudioplayer.h \
#    src/qml/qmlaudiorecorder.h \

#unix:HEADERS += \
#    src/io/audio/pulseaudio/pa_context_helper.h \
#    src/io/audio/pulseaudio/pa_streams_helper.h \
#    src/io/audio/pulseaudio/pa_utils.h \
#    src/io/audio/pulseaudio/pa_volume_helper.h \
#    src/io/audio/pulseaudio/pulseaudioplayerbackend.h \
#    src/io/audio/pulseaudio/pulseaudiorecordbackend.h \


win32:HEADERS += \
    src/io/audio/portaudio/portaudioplayerbackend.h \
    src/io/audio/portaudio/portaudiorecordbackend.h \
    src/io/audio/portaudio/portaudiorecordthread.h \


win32:FORMS += \
    forms/aboutdialog.ui \
    forms/editbuttondialog.ui \
    forms/recorddialog.ui \
    forms/reorderdialog.ui \
    forms/settingsdialog.ui \
    forms/soundfilelistdialog.ui \

exists("/usr/lib/qt5/qml/Sailfish/Silica/SilicaGridView.qml"): {
    message(SailfishOS build)

    TARGET = harbour-stultitiasimplex

    DEFINES += QDECLARATIVE_BOOSTER
    DEFINES += MER_EDITION_SAILFISH
    DEFINES += SYNC_TO_IMAP_SUPPORT
    MER_EDITION = sailfish

#    CONFIG += link_pkgconfig
#    PKGCONFIG += sailfishapp

    QT += quick qml

    # enable booster
    CONFIG += qdeclarative-boostable
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic

    target.path = /usr/bin
    desktop.files += res/sailfish/harbour-stultitiasimplex.desktop
    desktop.path = /usr/share/applications
    icon.files += res/sailfish/harbour-stultitiasimplex.png
    icon.path = /usr/share/icons/hicolor/86x86/apps
    qml.files += qml/sailfish/*
    qml.path = /usr/share/harbour-stultitiasimplex/qml

    INSTALLS += target desktop icon qml
} else:exists($$QMAKE_INCDIR_QT"/../applauncherd/MDeclarativeCache"): {
    MEEGO_VERSION_MAJOR     = 1
    MEEGO_VERSION_MINOR     = 2
    MEEGO_VERSION_PATCH     = 0
    MEEGO_EDITION           = harmattan

    DEFINES += MEEGO_EDITION_HARMATTAN NFC_ENABLED

    QT += declarative

    # enable booster
    CONFIG += qdeclarative-boostable
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic

    target.path = /opt/stultitiasimplex/bin
    desktop.files += res/meego/usr/share/applications/stultitiasimplex.desktop
    desktop.path = /usr/share/applications
    icon.files += res/meego/usr/share/icons/hicolor/64x64/apps/stultitiasimplex.png
    icon.path = /usr/share/icons/hicolor/64x64/apps
    qml.files += qml/meego/*
    qml.path = /opt/stultitiasimplex/qml
    splash.path = /opt/stultitiasimplex
    splash.files += res/svg/splash.png

    INSTALLS += target desktop icon qml splash
} else:unix {
    SOURCES += src/ui/dialog/editbuttondialog.cpp \
        src/ui/mainwindow.cpp \
        src/ui/soundbutton.cpp \
        src/ui/dialog/aboutdialog.cpp \
        src/ui/dialog/recorddialog.cpp \
        src/ui/dialog/reorderdialog.cpp \
        src/ui/dialog/settingsdialog.cpp \
        src/ui/dialog/soundfilelistdialog.cpp \

    HEADERS +=     src/ui/dialog/editbuttondialog.h \
        src/ui/mainwindow.h \
        src/ui/soundbutton.h \
        src/ui/dialog/aboutdialog.h \
        src/ui/dialog/recorddialog.h \
        src/ui/dialog/reorderdialog.h \
        src/ui/dialog/settingsdialog.h \
        src/ui/dialog/soundfilelistdialog.h \

    FORMS += \
        forms/aboutdialog.ui \
        forms/editbuttondialog.ui \
        forms/recorddialog.ui \
        forms/reorderdialog.ui \
        forms/settingsdialog.ui \
        forms/soundfilelistdialog.ui \

    target.path = /opt/maemo/usr/bin
    desktop.path = /usr/share/applications/hildon
    desktop.files += res/maemo/usr/share/applications/hildon/stultitiasimplex.desktop
    icon48.path = /usr/share/icons/hicolor/48x48/apps
    icon48.files += res/maemo/usr/share/icons/hicolor/48x48/hildon/stultitiasimplex.png

    INSTALLS += target desktop icon48
}

unix:DEFINES += UNIX

OTHER_FILES += \
    res/meego/usr/share/icons/hicolor/64x64/apps/stultitiasimplex.png \
    res/meego/usr/share/applications/stultitiasimplex.desktop \
    qml/meego/main.qml \
    qml/meego/FastScroll.qml \
    qml/meego/FastScrollStyle.qml \
    qml/meego/FastScroll.js \
    qml/meego/SoundFileListView.qml \
    qml/meego/AboutDialog.qml \
    qml/meego/EditSoundFileSheet.qml \
    qml/meego/SettingsSheet.qml \
    qml/meego/RecordDialog.qml \
    qml/sailfish/main.qml \
    qml/sailfish/FastScroll.qml \
    qml/sailfish/FastScroll.js \
    qml/sailfish/SoundFileListView.qml \
    qml/sailfish/AboutDialog.qml \
    qml/sailfish/EditSoundFileSheet.qml \
    qml/sailfish/SettingsSheet.qml \
    qml/sailfish/SelectionDialog.qml \
    qml/sailfish/RecordDialog.qml

