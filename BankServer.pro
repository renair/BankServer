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
    DataBase/testingdb.cpp \
    DataBase/connection.cpp \
    DataBase/Objects/withdraw.cpp \
    DataBase/Objects/transfer.cpp \
    DataBase/Access/transfer_table.cpp \
    DataBase/Objects/user.cpp \
    DataBase/Access/user_table.cpp \
    Protocol/Packets/UserAuthPacket.cpp \
    Server/PacketStorage.cpp \
    Server/ServerConfiguration.cpp \
    Server/PacketBuilder.cpp \
    Server/PacketProcessor.cpp \
    DataBase/Access/withdraw_table.cpp \
    DataBase/Objects/account.cpp \
    DataBase/Objects/session.cpp \
    DataBase/Access/account_table.cpp \
    Protocol/Packets/MakePaymentPacket.cpp \
    Protocol/Packets/MakePaymentResponsePacket.cpp \
    Protocol/Packets/GetPaymentsPacket.cpp \
    Protocol/Packets/GetPaymentsResponsePacket.cpp \
    Protocol/Packets/GetAccountMoneyPacket.cpp \
    Protocol/Packets/GetAccountMoneyResponsePacket.cpp \
    Protocol/Packets/GetCardsPacket.cpp \
    Protocol/Packets/GetCardsResponsePacket.cpp \
    DataBase/Access/session_table.cpp \
    DataBase/Objects/atm.cpp \
    DataBase/Access/atm_table.cpp \
    Protocol/Packets/ErrorPacket.cpp \
    Protocol/Packets/UserAuthResponsePacket.cpp \
    BankSystem/TasksPool.cpp

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
    DataBase/connection.h \
    DataBase/testingdb.h \
    DataBase/Objects/withdraw.h \
    DataBase/Objects/transfer.h \
    DataBase/Access/transfer_table.h \
    DataBase/Objects/user.h \
    DataBase/Access/user_table.h \
    Protocol/Packets/UserAuthPacket.h \
    Server/PacketStorage.h \
    Server/ServerConfiguration.h \
    Server/PacketBuilder.h \
    Server/PacketProcessor.h \
    DataBase/Access/withdraw_table.h \
    DataBase/Objects/account.h \
    DataBase/Objects/session.h \
    DataBase/Access/account_table.h \
    Protocol/Packets/MakePaymentPacket.h \
    Protocol/Packets/MakePaymentResponsePacket.h \
    Protocol/Packets/GetPaymentsPacket.h \
    Protocol/Packets/GetPaymentsResponsePacket.h \
    Protocol/Packets/GetAccountMoneyPacket.h \
    Protocol/Packets/GetAccountMoneyResponsePacket.h \
    Protocol/Packets/GetCardsPacket.h \
    Protocol/Packets/GetCardsResponsePacket.h \
    DataBase/Access/session_table.h \
    DataBase/Objects/atm.h \
    DataBase/Access/atm_table.h \
    Protocol/Packets/ErrorPacket.h \
    Protocol/Packets/UserAuthResponsePacket.h \
    BankSystem/TasksPool.h \
    BankSystem/AbstractTask.h

DISTFILES += \
    .gitignore \
    .travis.yml
