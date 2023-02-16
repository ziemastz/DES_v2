QT -= gui

TEMPLATE = lib
DEFINES += WRAPPERENSDF_LIBRARY
CONFIG += staticlib
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alpharecord.cpp \
    betarecord.cpp \
    ecrecord.cpp \
    ensdf.cpp \
    gammarecord.cpp \
    identificationrecord.cpp \
    levelrecord.cpp \
    normalizationrecord.cpp \
    parentrecord.cpp \
    productionnormalizationrecord.cpp \
    recordensdf.cpp \
    wrapperensdf.cpp

HEADERS += \
    WrapperENSDF_global.h \
    alpharecord.h \
    betarecord.h \
    ecrecord.h \
    ensdf.h \
    gammarecord.h \
    identificationrecord.h \
    levelrecord.h \
    normalizationrecord.h \
    parentrecord.h \
    productionnormalizationrecord.h \
    recordensdf.h \
    wrapperensdf.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
