#-------------------------------------------------
#
# Project created by QtCreator 2013-05-29T00:24:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnicodeOrChinese
TEMPLATE = app


SOURCES += main.cpp\
        unicodeorchinese.cpp \
    YCodec.cpp

HEADERS  += unicodeorchinese.h \
    YCodec.h

FORMS    += unicodeorchinese.ui


RC_FILE = logo.rc
