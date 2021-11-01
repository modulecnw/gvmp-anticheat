#pragma once
#include "imports.hpp"

#define ANTICHEAT
using namespace std;

class anticheat_main : public c_singleton<anticheat_main>
{
public:
	void run_service();
};