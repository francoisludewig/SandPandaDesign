QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/cone.cpp \
    Model/disk.cpp \
    Model/elbow.cpp \
    Model/plan.cpp \
    Model/solid.cpp \
    Model/sphere.cpp \
    Model/stripeonsphere.cpp \
    Model/velocity.cpp \
    Presenter/conepresenter.cpp \
    Presenter/diskpresenter.cpp \
    Presenter/planpresenter.cpp \
    Presenter/velocitiespresenter.cpp \
    Presenter/velocitypresenter.cpp \
    Repository/containerrepository.cpp \
    Repository/sphererepository.cpp \
    conetablewidget.cpp \
    disktablewidget.cpp \
    plantablewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    myglwidget.cpp \
    velocitiestabwidget.cpp

HEADERS += \
    Model/cone.h \
    Model/disk.h \
    Model/elbow.h \
    Model/plan.h \
    Model/solid.h \
    Model/sphere.h \
    Model/stripeonsphere.h \
    Model/velocity.h \
    Presenter/conepresenter.h \
    Presenter/diskpresenter.h \
    Presenter/planpresenter.h \
    Presenter/velocitiespresenter.h \
    Presenter/velocitypresenter.h \
    Repository/containerrepository.h \
    Repository/sphererepository.h \
    conetablewidget.h \
    disktablewidget.h \
    plantablewidget.h \
    mainwindow.h \
    myglwidget.h \
    velocitiestabwidget.h

FORMS += \
    mainwindow.ui

LIBS += -lopengl32 -lglu32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
