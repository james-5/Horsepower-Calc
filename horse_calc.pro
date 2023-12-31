TEMPLATE = app
QT += widgets
SOURCES += main.cpp mainwindow.cpp engine_calculations.cpp # Add engine_calculations.cpp here
HEADERS += MainWindow.h
# Add the path to Qwt library if needed
INCLUDEPATH += /usr/include/qwt
# Link Qwt library
LIBS += -lqwt
