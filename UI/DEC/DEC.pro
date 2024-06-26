QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controllers/atomicdatacontroller.cpp \
    Controllers/basecontroller.cpp \
    Controllers/branchcontroller.cpp \
    Controllers/nuclidecontroller.cpp \
    Decay/betasimulator.cpp \
    Decay/betaspectra.cpp \
    Decay/cesimulation.cpp \
    Decay/datavector.cpp \
    Decay/decaysimulator.cpp \
    Decay/ecsimulation.cpp \
    Decay/random.cpp \
    Models/alphatransitionmodel.cpp \
    Models/atomicdatamodel.cpp \
    Models/atomicsubshellmodel.cpp \
    Models/betatransitionmodel.cpp \
    Models/branchmodel.cpp \
    Models/decayschememodel.cpp \
    Models/ecmodel.cpp \
    Models/gammamodel.cpp \
    Models/levelmodel.cpp \
    Models/nuclidemodel.cpp \
    atomicdatadialog.cpp \
    atomicsubshelldialog.cpp \
    editbranchdialog.cpp \
    editgammadialog.cpp \
    formnuclide.cpp \
    generatespectrumdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Controllers/atomicdatacontroller.h \
    Controllers/basecontroller.h \
    Controllers/branchcontroller.h \
    Controllers/nuclidecontroller.h \
    Decay/betasimulator.h \
    Decay/betaspectra.h \
    Decay/cesimulation.h \
    Decay/datavector.h \
    Decay/decaysimulator.h \
    Decay/ecsimulation.h \
    Decay/random.h \
    Models/alphatransitionmodel.h \
    Models/atomicdatamodel.h \
    Models/atomicsubshellmodel.h \
    Models/betatransitionmodel.h \
    Models/branchmodel.h \
    Models/decayschememodel.h \
    Models/ecmodel.h \
    Models/gammamodel.h \
    Models/levelmodel.h \
    Models/nuclidemodel.h \
    atomicdatadialog.h \
    atomicsubshelldialog.h \
    editbranchdialog.h \
    editgammadialog.h \
    formnuclide.h \
    generatespectrumdialog.h \
    mainwindow.h

FORMS += \
    atomicdatadialog.ui \
    atomicsubshelldialog.ui \
    editbranchdialog.ui \
    editgammadialog.ui \
    formnuclide.ui \
    generatespectrumdialog.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE += \
    icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/WrapperENSDF/release/ -lWrapperENSDF
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/WrapperENSDF/debug/ -lWrapperENSDF
else:unix: LIBS += -L$$OUT_PWD/../../lib/WrapperENSDF/ -lWrapperENSDF

INCLUDEPATH += $$PWD/../../lib/WrapperENSDF
DEPENDPATH += $$PWD/../../lib/WrapperENSDF

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/ToolWidget/release/ -lToolWidget
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/ToolWidget/debug/ -lToolWidget
else:unix: LIBS += -L$$OUT_PWD/../../lib/ToolWidget/ -lToolWidget

INCLUDEPATH += $$PWD/../../lib/ToolWidget
DEPENDPATH += $$PWD/../../lib/ToolWidget

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/ToolWidget/release/libToolWidget.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/ToolWidget/debug/libToolWidget.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/ToolWidget/release/ToolWidget.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/ToolWidget/debug/ToolWidget.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/ToolWidget/libToolWidget.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/Database/release/ -lDatabase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/Database/debug/ -lDatabase
else:unix: LIBS += -L$$OUT_PWD/../../lib/Database/ -lDatabase

INCLUDEPATH += $$PWD/../../lib/Database
DEPENDPATH += $$PWD/../../lib/Database

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/Database/release/libDatabase.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/Database/debug/libDatabase.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/Database/release/Database.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/Database/debug/Database.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/Database/libDatabase.a
