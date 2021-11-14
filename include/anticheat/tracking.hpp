#pragma once
#include "imports.hpp"

class tracking : public c_singleton<tracking>
{
private:
	uint32_t get_tracking_id_by_file();
public:
	
};