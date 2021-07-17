#-------------------------------------------------
#
# Project created by QtCreator 2021-07-17T16:15:59
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = music_player
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

CONFIG += mobility
CONFIG += resources_big

MOBILITY = 

RESOURCES += \
    musics.qrc \
    images.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

