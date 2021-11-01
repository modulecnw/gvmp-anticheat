#define ENET_IMPLEMENTATION
#include "networking/networking.hpp"

void networking::start()
{
	std::thread([&] {
		if (enet_initialize() != 0) return;

		this->client = enet_host_create(NULL, 1, 2, 0, 0);
		if (this->client == NULL) {
			Log::Error("[!] Networking", "Failed to create client.");
			return;
		}

		enet_address_set_host(&address, this->nemo_server_ip);
		address.port = 3004;

		peer = enet_host_connect(client, &address, 2, 0);
		if (peer == NULL) {
			Log::Error("[!] Networking >>", "Failed to connect to server.");
		}

		ENetEvent e;
		if (enet_host_service(client, &e, 5000) > 0 && e.type == ENET_EVENT_TYPE_CONNECT) {
			Log::Warning("[!] Networking >>", "Connected to server.");
		}
		else {
			enet_peer_reset(peer);
			Log::Error("[!] Networking >>", "Failed to connect to server.");
			Log::Info((uintptr_t)client->address.port);
		}

		/*ENetPacket* packet = enet_packet_create("REQUEST_LOGIN", strlen("test") + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);*/

		while (true) {
			this->pulse();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		}).detach();
}

void networking::pulse()
{
	ENetEvent e;

	while (enet_host_service(client, &e, 3000) > 0) {
		switch (e.type) {
		case ENET_EVENT_TYPE_RECEIVE:
			switch (e.packet->data[0]) {
				//TODO: add packet receive
			}

			enet_packet_destroy(e.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			Log::Error("[!] Networking >>", "Connection disconnected.");
			break;
		case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
			Log::Error("[!] Networking >>", "Connection timed out.");
			break;
		}
	}

	//enet_peer_reset(peer);
}

void networking::send_packet(Network::Packet buffer)
{
	ENetPacket* packet = enet_packet_create(buffer.GetData(), buffer.GetDataSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}