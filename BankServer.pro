QT += core network sql
QT -= gui

CONFIG += c++11
#to support c++11 in travis ci
QMAKE_CXXFLAGS += -std=c++11

TARGET = BankServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Protocol/Packet.cpp \
    Protocol/Client/UserAuthPacket.cpp \
    Server/Server.cpp \
    BankSystem/PaymentManager.cpp \
    BankSystem/PaymentService.cpp \
    DBWork/testingdb.cpp \
    DBWork/connection.cpp \
    BankSystem/PaymentService.cpp \
    DataBase/Objects/Payment.cpp \
    DataBase/Objects/PaymentStub.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Protocol/Packet.h \
    Protocol/PacketsList.h \
    Protocol/Client/UserAuthPacket.h \
    Server/Server.h \
    BankSystem/PaymentManager.h \
    BankSystem/PaymentService.h \
    DBWork/connection.h \
    DBWork/testingdb.h \
    DataBase/Objects/Payment.h \
    DataBase/Objects/PaymentStub.h

DISTFILES += \
    .gitignore \
    .travis.yml
