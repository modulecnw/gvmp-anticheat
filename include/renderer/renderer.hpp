#pragma once
#include "imports.hpp"

#define RENDERER
using namespace std;

class renderer : public c_singleton<renderer>
{
private:
	typedef HRESULT(__stdcall* d3d11_present_t) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

private:
	DWORD_PTR* v_table_swap_chain = nullptr;
	DWORD_PTR* v_table_device = nullptr;
	DWORD_PTR* v_table_device_context = nullptr;

public:
	// needs to be public to get accessed
	d3d11_present_t o_d3d11_present = nullptr;

	bool already_initialized = false;

	ID3D11Device* ptr_device = nullptr;
	ID3D11DeviceContext* ptr_device_context = nullptr;
	IDXGISwapChain* ptr_swap_chain = nullptr;

	ID3D11RenderTargetView* target_view;
	IFW1FontWrapper* font_wrapper = NULL;

	void initialize();
};