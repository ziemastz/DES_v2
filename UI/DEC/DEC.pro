QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Models/branchmodel.cpp \
    Models/decayschememodel.cpp \
    Models/gammamodel.cpp \
    Models/nuclidemodel.cpp \
    formnuclide.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Models/branchmodel.h \
    Models/decayschememodel.h \
    Models/gammamodel.h \
    Models/nuclidemodel.h \
    formnuclide.h \
    mainwindow.h

FORMS += \
    formnuclide.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/libENSDFReader/release/ -llibENSDFReader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/libENSDFReader/debug/ -llibENSDFReader
else:unix: LIBS += -L$$OUT_PWD/../../lib/libENSDFReader/ -llibENSDFReader

INCLUDEPATH += $$PWD/../../lib/libENSDFReader
DEPENDPATH += $$PWD/../../lib/libENSDFReader

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/libENSDFReader/release/liblibENSDFReader.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/libENSDFReader/debug/liblibENSDFReader.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/libENSDFReader/release/libENSDFReader.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/libENSDFReader/debug/libENSDFReader.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/libENSDFReader/liblibENSDFReader.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/WrapperENSDF/release/ -lWrapperENSDF
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/WrapperENSDF/debug/ -lWrapperENSDF
else:unix: LIBS += -L$$OUT_PWD/../../lib/WrapperENSDF/ -lWrapperENSDF

INCLUDEPATH += $$PWD/../../lib/WrapperENSDF
DEPENDPATH += $$PWD/../../lib/WrapperENSDF

RESOURCES += \
    resources.qrc
