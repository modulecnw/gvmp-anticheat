#pragma once
#define WIN32_LEAN_AND_MEAN

#ifndef ENET_DEBUG
#define ENET_DEBUG
#endif

#include <windows.h>
#include <string>
#include <optional>
#include <vector>
#include <sstream>
#include <d3d11.h>
#include <functional>
#include <xmmintrin.h>
#include <iostream>
#include <thread>
#include <map>
#include <memory>

// nlohmann
#include <vendor/nlohmann/json.hpp>

// min_hook
#include <MinHook.h>

//alt
#include <vendor/alt/alt-log.hpp>
using namespace alt;

#include <vendor/singleton.hpp>
#include <vendor/xor.hpp>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "networking/enet.h"