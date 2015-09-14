#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <xnamath.h>

namespace Renderer
{
	class DX11Renderer
	{
	public:
		static bool Init(HWND hwnd, HINSTANCE hInstance);
		static void RelaseObjects();
		static bool InitScene();
		static void UpdateScene();
		static void DrawScene();

	private:
		static float r, g, b;
		static int colormodr, colormodg, colormodb;
		static IDXGISwapChain* swapChain;
		static ID3D11Device* device;
		static ID3D11DeviceContext* deviceContext;
		static ID3D11RenderTargetView* renderTargetView;
	};
}