#include <renderer\renderer.hpp>
#include <DirectXPackedVector.h>
#include "pointers/pointers.hpp"

HRESULT __stdcall d3d11_present(IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags) {
	auto& renderer = renderer::get();

	std::call_once(renderer.already_initialized, [&]() {
		swap_chain->GetDevice(__uuidof(renderer.ptr_device), (void**)&renderer.ptr_device);
		renderer.ptr_device->GetImmediateContext(&renderer.ptr_device_context);

		IFW1Factory* font_factory = NULL;
		FW1CreateFactory(FW1_VERSION, &font_factory);

		if (font_factory != NULL && renderer.ptr_device != NULL) {
			font_factory->CreateFontWrapper(renderer.ptr_device, L"Hero Light", &renderer.font_wrapper);
			font_factory->Release();
		}

		ID3D11Texture2D* pBackBuffer = NULL;
		swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		if (pBackBuffer != NULL)
			renderer.ptr_device->CreateRenderTargetView(pBackBuffer, NULL, &renderer.target_view);
		});

	renderer.ptr_device_context->OMSetRenderTargets(1, &renderer.target_view, NULL);

	// TODO: add client & game-thread
	//		 add timeouts

	// COLOR FORMAT: 0xAARRGGBB
	if (IsValidPtr(pointers::get().ptr_gta_world_factory)) {
		auto local_world = pointers::get().ptr_gta_world_factory->world;
		if (IsValidPtr(local_world)) {
			renderer.font_wrapper->DrawString(renderer.ptr_device_context, L"GVMP Anti-Cheat", 12, 8, 5, 0x9fffffff, FW1_RESTORESTATE);
			renderer.font_wrapper->DrawString(renderer.ptr_device_context, L"GVMP Anti-Cheat", 12, 8, 8, 0x59ffffff, FW1_RESTORESTATE);
		}
	}

	return renderer.o_d3d11_present(swap_chain, sync_interval, flags);
}

bool renderer::initialize()
{
	HWND window = GetForegroundWindow();

	if (!window)
		return false;

	D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc;

	ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swap_chain_desc.OutputWindow = window;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.Windowed = (GetWindowLong(window, GWL_STYLE) & WS_POPUP) != 0 ? FALSE : TRUE;
	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	HRESULT create_result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &feature_level, 1, D3D11_SDK_VERSION, &swap_chain_desc, &ptr_swap_chain, &ptr_device, NULL, &ptr_device_context);

	if (FAILED(create_result))
		return false;

	v_table_swap_chain = (DWORD_PTR*)(ptr_swap_chain);
	v_table_swap_chain = (DWORD_PTR*)(v_table_swap_chain[0]);

	v_table_device = (DWORD_PTR*)(ptr_device);
	v_table_device = (DWORD_PTR*)(v_table_device[0]);

	v_table_device_context = (DWORD_PTR*)(ptr_device_context);
	v_table_device_context = (DWORD_PTR*)(v_table_device_context[0]);

	auto ptr_d3d11_present = (d3d11_present_t)v_table_swap_chain[8];

	if (MH_CreateHook(ptr_d3d11_present, &d3d11_present, reinterpret_cast<LPVOID*>(&o_d3d11_present)) != MH_OK)
		Log::Error("Renderer /", "Failed to create hook.");

	if (MH_EnableHook(ptr_d3d11_present) != MH_OK)
		Log::Error("Renderer /", "Failed to enable hook.");

	ptr_swap_chain->Release();
	ptr_device->Release();
	ptr_device_context->Release();

	Log::Error("Renderer /", "Successfully initialized renderer.");

	return true;
}