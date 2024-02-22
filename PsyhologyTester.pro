QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../CustomWidgets/QQuestionWidget/qquestionwidget.cpp \
    ../CustomWidgets/ReportWidget/reportwidget.cpp \
    file_data.cpp \
    jsoncontroller.cpp \
    main.cpp \
    menuwindow.cpp \
    testreport.cpp

HEADERS += \file_data.h \
    ../CustomWidgets/QQuestionWidget/qquestionwidget.h \
    ../CustomWidgets/ReportWidget/reportwidget.h \
    jsoncontroller.h \
    menuwindow.h \
    testreport.h

FORMS += \
    ../CustomWidgets/QQuestionWidget/qquestionwidget.ui \
    ../CustomWidgets/ReportWidget/reportwidget.ui \
    menuwindow.ui
# win32:RC_FILE = recourse.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
