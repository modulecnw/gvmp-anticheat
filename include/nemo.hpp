#pragma once
#include "imports.hpp"

#define NETWORKING
using namespace std;

class nemo_ac : public c_singleton<nemo_ac>
{
public:
	struct nemo_local_player_t {
		std::string ingame_character_name;
		std::string ip_address;
	};

	nemo_local_player_t local_player;

	void run_service(HMODULE module);
	void shutdown_service();
};