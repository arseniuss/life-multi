/* 
 * File:   StateGame.cpp
 * Author: arseniuss
 *
 * Created on otrdiena, 2013, 30 oktobris, 16:12
 */

#include <assert.h>

#if PLATFORM == PLATFORM_UNIX
#    include <fcntl.h>
#    include <netinet/in.h>
#    include <cstdlib>
#    include <sys/socket.h>
#    include <ios>
#endif

#include "config.h"
#include "debug.h"
#include "network.h"

Address::Address(unsigned char a, unsigned char b, unsigned char c,
        unsigned char d, unsigned short port) {
    this->address = (a << 24) | (b << 16) | (c << 8) | d;
    this->port = port;
}

Address::Address(unsigned int address, unsigned short port) {
    this->address = address;
    this->port = port;
}

Address::Address(const char* address) {
    //TODO: parse string, format "XXX.XXX.XXX.XXX:XXXX"
    throw "Not yet implemented!";
}

unsigned int Address::GetAddress() const {
    return this->address;
}

unsigned short Address::GetPort() const {
    return this->port;
}

bool Address::operator ==(const Address& other) const {
    return address == other.address && port == other.port;
}

bool Address::operator !=(const Address& other) const {
    return !(*this == other);
}

Socket::Socket() {
    handle = 0;
}

bool Socket::Open(unsigned short port) {
    assert(!IsOpen());

    //izveido soketu
    handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (handle <= 0) {
        log("Failed to create socket!\n");
        Close();

        return false;
    }

    //pievieno soketam portu, kuru klausīties
    sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(handle, (sockaddr *) & addr, sizeof (sockaddr_in)) < 0) {
        log("Failed to bind port to socket!\n");
        Close();

        return false;
    }

#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    int nonBlocking = 1;

    //uzliek, lai gaidot paketi netiktu apstrādināta spēle
    if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
        log("Failed to set socket to nonblocking type!\n");
        Close();

        return false;
    }

    return true;
#elif PLATFORM == PLATFORM_WINDOWS
    //TODO: debug
    DWORD nonBlocking = 1;
    if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0) {
        log("Failed to set socket to nonblocking type!\n");
        Close();

        return false;
    }
#else
    return false;
#endif
}

bool Socket::IsOpen() const {
    return handle != 0;
}

bool Socket::Close() {
    if (handle != 0) {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
        close(handle);
#elif PLATFORM == PLATFORM_WINDOWS
        closesocket(handle);
#endif
        handle = 0;
    }

    return true;
}

bool Socket::Send(const Address& dest, const void* data, int size) {
    assert(data);
    assert(size > 0);

    if (handle == 0)
        return false;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(dest.GetAddress());
    address.sin_port = htons((unsigned short) dest.GetPort());

    int sent_bytes = sendto(handle, (const char*) data, size, 0, (sockaddr*) & address, sizeof (sockaddr_in));

    return sent_bytes == size;
}

int Socket::Recv(Address& src, void* data, int size) {
    assert(data);
    assert(size > 0);

    if (handle == 0)
        return false;

#if PLATFORM == PLATFORM_WINDOWS
    typedef int socklen_t;
#endif

    sockaddr_in from;
    socklen_t fromLength = sizeof ( from);

    int received_bytes = recvfrom(handle, (char*) data, size, 0, (sockaddr*) & from, &fromLength);

    if (received_bytes <= 0)
        return 0;

    unsigned int address = ntohl(from.sin_addr.s_addr);
    unsigned int port = ntohs(from.sin_port);

    src = Address(address, port);

    return received_bytes;
}

Socket::~Socket() {
    Close();
}
