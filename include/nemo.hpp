#pragma once
#include "imports.hpp"

#define NETWORKING
using namespace std;

class nemo_ac : public c_singleton<nemo_ac>
{
public:
    void run_service();
    void shutdown_service();
};