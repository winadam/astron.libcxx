#pragma once
#include "util/Connection.h"
namespace astron   // open namespace
{


// Implementation Notes:
//     If necessary connection can subclass another class (maybe NetworkClient for example);
//     However, any inherited virtual functions must be implemented. Subclasses of connection
//     should only be required to implement handle_datagram.
class ClientConnection : public Connection
{
	public:
		ClientConnection();


		void connect(std::string uri, uint32_t dc_hash, std::string version);

		// disconnect cleanly closes the connection.
		// Internally: Sends a CLIENT_DISCONNECT, and waits for connection to close.
		void disconnect();
};


} // close namespace
