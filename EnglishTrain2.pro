QT       += core gui\
            xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EnglishTrain2
TEMPLATE = app


SOURCES += main.cpp \
    translation.cpp \
    presentW.cpp \
    translationApp.cpp \
    checkW.cpp \
    errorW.cpp

HEADERS  += \
    translation.h \
    presentW.h \
    translationApp.h \
    checkW.h \
    errorW.h


FORMS    += \
    checkW.ui \
    errorW.ui \
    translateW.ui


QT += network
