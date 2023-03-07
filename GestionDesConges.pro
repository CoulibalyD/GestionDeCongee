QT       += core gui sql
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administrateur.cpp \
    conge.cpp \
    congemodel.cpp \
    dbaccess.cpp \
    directeurmodel.cpp \
    directeurrh.cpp \
    employemodel.cpp \
    flowcontroller.cpp \
    main.cpp \
    authentification.cpp \
    manager.cpp \
    managermodel.cpp \
    user.cpp \
    usermodel.cpp \
    windowemploye.cpp

HEADERS += \
    administrateur.h \
    authentification.h \
    conge.h \
    congemodel.h \
    dbaccess.h \
    directeurmodel.h \
    directeurrh.h \
    employemodel.h \
    flowcontroller.h \
    manager.h \
    managermodel.h \
    user.h \
    usermodel.h \
    windowemploye.h

FORMS += \
    administrateur.ui \
    authentification.ui \
    directeurrh.ui \
    manager.ui \
    windowemploye.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MesRessources.qrc


