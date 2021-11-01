#include <anticheat\anticheat.hpp>
#include <anticheat\detections.hpp>

// Cheat-Signatures:
// 0xCheats: E8 ? ? ? ? 41 52 49 89 E2

void anticheat_main::run_service()
{
	/*
	 * These are just basic tests (poc).
	 * TODO: create classes for hooking & other stuff.
	 */

	anticheat_detections::get().run_service();
}