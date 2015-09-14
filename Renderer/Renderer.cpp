#include "Renderer.h"

namespace Renderer
{
	IDXGISwapChain*			DX11Renderer::swapChain;
	ID3D11Device*			DX11Renderer::device;
	ID3D11DeviceContext*	DX11Renderer::deviceContext;
	ID3D11RenderTargetView* DX11Renderer::renderTargetView;
	float					DX11Renderer::r = 1.0f;
	float					DX11Renderer::g = 0.0f;
	float					DX11Renderer::b = 0.0f;
	int						DX11Renderer::colormodr = 1;
	int						DX11Renderer::colormodg = 1;
	int						DX11Renderer::colormodb = 1;

	bool DX11Renderer::Init(HWND hwnd, HINSTANCE hInstance)
	{
		HRESULT hr;

		DXGI_MODE_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

		bufferDesc.Width = 800;
		bufferDesc.Height = 600;
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, NULL, &deviceContext);

		ID3D11Texture2D* backBuffer;
		hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

		hr = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
		backBuffer->Release();

		deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);
		return true;
	}

	bool DX11Renderer::InitScene()
	{
		return true;
	}

	void DX11Renderer::RelaseObjects()
	{
		swapChain->Release();
		device->Release();
		deviceContext->Release();
	}

	void DX11Renderer::UpdateScene()
	{
		if (r == 1.0f)
		{
			r = 0.0f;
			g = 1.0f;
		}
		else if (g == 1.0f)
		{
			g = 0.0f;
			b = 1.0f;
		}
		else
		{
			b = 0.0f;
			r = 1.0f;
		}
	}

	void DX11Renderer::DrawScene()
	{
		D3DXCOLOR bgColor(r, g, b, 1.0f);
		deviceContext->ClearRenderTargetView(renderTargetView, bgColor);
		swapChain->Present(0,0);
	}
}