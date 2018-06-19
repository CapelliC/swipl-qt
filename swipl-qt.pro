#--------------------------------------------------
# swipl-win.pro: SWI-Prolog / QT interface
#--------------------------------------------------
#
# REPL in QTextEdit on a background logic processor
#--------------------------------------------------
# Ing. Capelli Carlo - Brescia 2013

#-------------------------------------------------
# Project created by QtCreator 2013-07-10T10:26:52
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx {
    QT_CONFIG -= no-pkg-config
    CONFIG += c++11
    ICON = swipl.icns
    QMAKE_MACOS_DEPLOYMENT_TARGET = 10.6
    QMAKE_MAC_SDK = macosx10.12
}

TARGET = swipl-win
TEMPLATE = app

# please, not obsolete compiler
QMAKE_CXXFLAGS += -std=c++0x

# provide appropriate linking mode for
# static compilation of pqConsole source files
DEFINES += PQCONSOLE_STATIC

# remove old defines in foreign predicates params
# due to conflicting Qt5 template arguments
DEFINES += PL_SAFE_ARG_MACROS

# QPlainTextEdit vs QTextEdit : faster lightweight format
# TBD evaluate timing difference
DEFINES += PQCONSOLE_NO_HTML

# reactive interface
# TBD as above
DEFINES += PQCONSOLE_BROWSER

# disable message hoovering and feedback, leave to reactive HTML
DEFINES += PQCONSOLE_HANDLE_HOOVERING

# added code from https://github.com/CapelliC/loqt/tree/master/lqUty
# to handle highlighting of selected text in console
DEFINES += LQUTY_STATIC
INCLUDEPATH += lqUty

DEFINES += PQUTY_STATIC
INCLUDEPATH += pqConsole

DEFINES += PQSOURCE_STATIC
INCLUDEPATH += pqSource

unix {
    # because SWI-Prolog is built from source
    CONFIG += link_pkgconfig
    PKGCONFIG += swipl
}

windows {
    SwiPl = "C:\Program Files\pl"
    INCLUDEPATH += $$SwiPl\include
    LIBS += -L$$SwiPl\bin -lswipl
}

mingw {
    SWIPL_BASE  = "../../"
    INCLUDEPATH += $$SWIPL_BASE/include ../cpp
    LIBS += -L$$SWIPL_BASE/lib/x64-win64 -lswipl
}

SOURCES += main.cpp \
    SwiPrologEngine.cpp \
    Swipl_IO.cpp \
    Preferences.cpp \
    pqMainWindow.cpp \
    pqConsole.cpp \
    FlushOutputEvents.cpp \
    ConsoleEdit.cpp \
    Completion.cpp \
    swipl_win.cpp \
    pqSource/pqSyntaxData.cpp \
    pqSource/pqSource.cpp \
    pqSource/pqHighlighter.cpp \
    pqSource/pqTextAttributes.cpp \
    pqConsole/pqMiniSyntax.cpp \
    lqUty/framedTextAttr.cpp \
    lqUty/foldedTextAttr.cpp \
    lqUty/ParenMatching.cpp

RESOURCES += \
    swipl-win.qrc

OTHER_FILES += \
    README.md \
    MINGW.md

HEADERS += \
    SwiPrologEngine.h \
    Swipl_IO.h \
    Preferences.h \
    PREDICATE.h \
    pqMainWindow.h \
    pqConsole.h \
    FlushOutputEvents.h \
    do_events.h \
    ConsoleEdit.h \
    Completion.h \
    swipl_win.h \
    blockSig.h \
    pqSource/pqTextAttributes.h \
    pqSource/pqSyntaxData.h \
    pqSource/pqSource_global.h \
    pqSource/pqSource.h \
    pqSource/pqHighlighter.h \
    pqConsole/pqMiniSyntax.h \
    pqConsole/pqConsole_global.h \
    lqUty/lqUty_global.h \
    lqUty/ParenMatching.h \
    lqUty/framedTextAttr.h \
    lqUty/foldedTextAttr.h \
    lqUty/thousandsDots.h \
    lqUty/file2string.h

DISTFILES += \
    pqSource/syncol.pl
