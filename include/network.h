/* 
 * File:   network.h
 * Author: arseniuss
 *
 * Created on trešdiena, 2013, 30 oktobris, 16:03
 */

#pragma once

#include "config.h"

class Address {
private:
    unsigned int address;
    unsigned short port;
public:
    Address() : address(0), port(0) {};
    ~Address() {};
    Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d,
            unsigned short port);
    Address(unsigned int address, unsigned short port);
    Address(const char *address);
    unsigned int GetAddress() const;
    unsigned short GetPort() const;
    bool operator ==(const Address & other) const;
    bool operator != (const Address & other) const;
};

class Socket {
private:
    int handle;
public:
    Socket();
    ~Socket();
    bool Open(unsigned short port);
    bool Close();
    bool IsOpen() const;
    bool Send(const Address & dest, const void * data, int size);
    int Recv(Address & src, void * data, int size);
};
