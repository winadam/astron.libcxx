#include "ClientConnection.h"
#include "ClientMessages.h"
namespace astron   // open namespace
{

// connect starts a connection to the server, negotiates Hello and starts sending
// heartbeats periodically. It returns after negotiation is complete.

ClientConnection::ClientConnection() : Connection() {

}

void ClientConnection::disconnect() {
    //Datagram dg(CLIENT_DISCONNECT);
    //Creates a ServerDatagram
    Datagram dg;
    dg.add_uint16(CLIENT_DISCONNECT);
    send_datagram(dg);
    Connection::disconnect();
}

void ClientConnection::connect(std::string uri, uint32_t dc_hash, std::string version) {
    Connection::connect(uri);
    //Datagram dg(CLIENT_HELLO);
    //Creates a ServerDatagram
    Datagram dg;
    dg.add_uint16(CLIENT_HELLO);
    dg.add_uint32(dc_hash);
    dg.add_string(version);
    send_datagram(dg);
}

} // close namespace