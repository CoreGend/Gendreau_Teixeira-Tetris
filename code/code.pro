QT       += core gui
QT       += widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    afficheur.cpp \
    bouton.cpp \
    globals.cpp \
    jeu.cpp \
    jeu_ai.cpp \
    liste_piece.cpp \
    main.cpp \
    part_piece.cpp \
    piece.cpp \
    serveur.cpp \
    tableau.cpp

HEADERS += \
    afficheur.h \
    bouton.h \
    globals.h \
    includers.h \
    jeu.h \
    jeu_ai.h \
    liste_piece.h \
    part_piece.hpp \
    piece.hpp \
    serveur.h \
    tableau.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md
