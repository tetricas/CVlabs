#-------------------------------------------------
#
# Project created by QtCreator 2017-10-11T09:52:28
#
#-------------------------------------------------

QT += core gui widgets opengl quickwidgets qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CVlabs
TEMPLATE = app

DESTDIR = $$PWD/../bin/CVlabs/debug

INCLUDEPATH += ../include/

HEADERS += \
    ../include/Transformation/TransformationWidget.h \
    ../include/MainWindow.h \
    ../include/Transformation/TransformationBase.h \
    ../include/Transformation/TransformationHomogeneous.h \
    ../include/Transformation/TransformationNormal.h \
    ../include/Segments/SegmentsWidget.h \
    ../include/Segments/SegmentsFieldWidget.h \
    ../include/Fractals/FractalsWidget.h

SOURCES += \
    ../src/main.cpp \
    ../src/Transformation/TransformationWidget.cpp \
    ../src/MainWindow.cpp \
    ../src/Transformation/TransformationBase.cpp \
    ../src/Transformation/TransformationHomogeneous.cpp \
    ../src/Transformation/TransformationNormal.cpp \
    ../src/Segments/SegmentsWidget.cpp \
    ../src/Segments/SegmentsFieldWidget.cpp \
    ../src/Fractals/FractalsWidget.cpp

FORMS += \
        ../rc/ui/mainwindow.ui \
        ../rc/ui/TransformationWidget.ui \
        ../rc/ui/SegmentsWidget.ui

RESOURCES += \
    ../rc/images.qrc \
    ../rc/qml.qrc

LIBS += -lOpenGL32 -lglu32
