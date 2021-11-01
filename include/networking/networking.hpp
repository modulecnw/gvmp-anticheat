#pragma once
#include "imports.hpp"

#include "networking/data/packet.h"
#include "networking/data/data.hpp"

class networking : public c_singleton<networking>
{
private:
    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;
    ENetHost* client;

    UserData* client_user_data;

    char* nemo_server_ip = "127.0.0.1";
    int nemo_server_port = 3005;

    // NETWORKING_PROTOCOL_TO_DEFINITION
    typedef enum _NetworkingMessageTypes {
        NETWORKING_ASK_CLIENT_USERNAME = 1,
        NETWORKING_RESPONSE_SERVER_USERNAME,
        NETWORKING_RESPONSE_CLIENT_LOGGED_IN,
        NETWORKING_ASK_SERVER_SEND_CHATMESSAGE,
        NETWORKING_BROADCAST_CHATMESSAGE,
    };
public:
    void start();
    void pulse();

    void send_packet(Network::Packet buffer);
};
