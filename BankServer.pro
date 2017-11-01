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
    Server/Server.cpp \
    BankSystem/PaymentService.cpp \
    DataBase/testingdb.cpp \
    DataBase/connection.cpp \
    DataBase/Objects/withdraw.cpp \
    DataBase/Objects/transfer.cpp \
    DataBase/Access/transfer_table.cpp \
    BankSystem/BankManager.cpp \
    Protocol/Packets/UserAuthPacket.cpp \
    Server/PacketStorage.cpp \
    Server/ServerConfiguration.cpp \
    Server/PacketBuilder.cpp \
    Protocol/Processors/UserAuthProcessor.cpp \
    Server/PacketProcessorCenter.cpp

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
    Server/Server.h \
    BankSystem/PaymentService.h \
    DataBase/connection.h \
    DataBase/testingdb.h \
    DataBase/Objects/withdraw.h \
    DataBase/Objects/transfer.h \
    DataBase/Objects/payment.h \
    DataBase/Access/transfer_table.h \
    BankSystem/BankManager.h \
    BankSystem/UserService.h \
    Protocol/Packets/UserAuthPacket.h \
    Server/PacketStorage.h \
    Server/ServerConfiguration.h \
    Server/PacketBuilder.h \
    Protocol/PacketProcessor.h \
    Protocol/Processors/UserAuthProcessor.h \
    Server/PacketProcessorCenter.h

DISTFILES += \
    .gitignore \
    .travis.yml
