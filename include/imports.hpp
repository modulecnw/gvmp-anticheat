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
#include <mutex> 

// nlohmann
#include <vendor/nlohmann/json.hpp>

// min_hook
#include <MinHook.h>

// fontwrapper
#include <vendor/fontwrapper/FW1FontWrapper.h>
#include <vendor/fontwrapper/FW1CompileSettings.h>
#include <vendor/fontwrapper/FW1Precompiled.h>
#include <vendor/fontwrapper/CFW1TextRenderer.h>
#include <vendor/fontwrapper/CFW1TextGeometry.h>
#include <vendor/fontwrapper/CFW1StateSaver.h>
#include <vendor/fontwrapper/CFW1Object.h>
#include <vendor/fontwrapper/CFW1GlyphVertexDrawer.h>
#include <vendor/fontwrapper/CFW1GlyphSheet.h>
#include <vendor/fontwrapper/CFW1GlyphRenderStates.h>
#include <vendor/fontwrapper/CFW1GlyphProvider.h>
#include <vendor/fontwrapper/CFW1GlyphAtlas.h>
#include <vendor/fontwrapper/CFW1FontWrapper.h>
#include <vendor/fontwrapper/CFW1Factory.h>
#include <vendor/fontwrapper/CFW1DWriteRenderTarget.h>
#include <vendor/fontwrapper/CFW1ColorRGBA.h>

//alt
#include <vendor/alt/alt-log.hpp>
using namespace alt;

#include <vendor/singleton.hpp>
#include <vendor/xor.hpp>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "networking/enet.h"

