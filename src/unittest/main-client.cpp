//TODO: create public header directory
#include <client/ClientConnection.h>
#include <client/ClientMessages.h>
#include <util/Datagram.h>
#include <util/DatagramIterator.h>
#include <string>
#include <thread>
#include <objects/ObjectRepository.h>

std::vector<std::string> dcFiles = { "unittest.dc" };

class CustomClient : public astron::ClientConnection {
public:
    bool mShouldRun = true;
    std::thread mThread;
    CustomClient() : ClientConnection() {

    }
    ~CustomClient(){

    }
    void login(std::string addr, uint32_t dc_hash, std::string version){
        ClientConnection::connect(addr, dc_hash, version);
    }
    void logout(){
        ClientConnection::disconnect();
    }
    void handle_datagram(const astron::Datagram& dg){
        astron::DatagramIterator dgi(dg);
        dgi.seek(0);
        //Cannot use get_msg_type for as it is for server messages
        uint16_t msg_type = dgi.read_uint16();
        switch(msg_type){
            case(CLIENT_HELLO_RESP): {
                std::cout << "Client is connected!" << std::endl;
                break;

            }
            case(CLIENT_EJECT): {
                uint16_t reason = dgi.read_uint16();
                std::string reason_string = dgi.read_string();
                std::cerr << "Client was ejected for error code: " << reason << std::endl;
                std::cerr << reason_string << std::endl;
                mShouldRun = false;
                break;
            }

            default:{
                std::cout << "Unknown message type:" << msg_type << std::endl;
            }
        }

    }
    void poll(){
        while(mShouldRun){
            astron::Datagram *dg = new astron::Datagram();
            if(poll_datagram(*dg)){
                handle_datagram(*dg);
            }
            delete dg;

        }
    }
     void run(){
        astron::ObjectRepository objectRepository(dcFiles);
        login("localhost:7199",objectRepository.getDcHash(),"Unittest");
        mThread = std::thread(&CustomClient::poll,this);
        //mThread.detach();

    }
    void stop(){
        mShouldRun = false;
        mThread.join();

        logout();
    }
};

std::thread DatagramReciever;
int main(int argc, char **argv){
    CustomClient cg;
    cg.run();

    std::this_thread::sleep_for(std::chrono::seconds(15));
    cg.stop();
}