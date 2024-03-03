#ifndef AUXPORT_GUI_H
#define AUXPORT_GUI_H
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2023, Satyarth Arora
			All rights reserved.

			Redistribution and use in source and binary forms, with or without
			modification, are permitted provided that the following conditions are met:

			1. Redistributions of source code must retain the above copyright notice, this
			   list of conditions and the following disclaimer.

			2. Redistributions in binary form must reproduce the above copyright notice,
			   this list of conditions and the following disclaimer in the documentation
			   and/or other materials provided with the distribution.

			3. Neither the name of the copyright holder nor the names of its
			   contributors may be used to endorse or promote products derived from
			   this software without specific prior written permission.

			THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
			AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
			IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
			DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
			FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
			DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
			SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
			CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
			OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
			OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*===================================================================================*/

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <functional>
#include "AuxPort.h"

///////////////////////////////////////////////////////////////////////////////////////
/// Required Macros for ImGui Driver Code
///////////////////////////////////////////////////////////////////////////////////////
#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

///////////////////////////////////////////////////////////////////////////////////////
/// Forward declare message handler from imgui_impl_win32.cpp
/// Will be called by WndProc Helper Function
///////////////////////////////////////////////////////////////////////////////////////
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Extensions
{
	namespace AuxGui
	{
		class Application
		{
		public:
			Application(const std::wstring& applicationTitle);
			~Application();
			void setMainLoop(const std::function<void()>& mainLoopUpdateFunction);
			void run();
			float getFrameRate();
		private:
			std::function<void()> mainLoopUpdateFunction;

			///////////////////////////////////////////////////////////////////////////////////////
			/// Required Data for ImGui
			///////////////////////////////////////////////////////////////////////////////////////
			static ID3D11Device* g_pd3dDevice;
			static ID3D11DeviceContext* g_pd3dDeviceContext;
			static IDXGISwapChain* g_pSwapChain;
			static UINT g_ResizeWidth;
			static UINT g_ResizeHeight;
			static ID3D11RenderTargetView* g_mainRenderTargetView;
			ImGuiIO* io;
			WNDCLASSEXW wc;
			HWND hwnd;
			ImVec4 clear_color;

			///////////////////////////////////////////////////////////////////////////////////////
			/// Helper Functions for ImGui
			///////////////////////////////////////////////////////////////////////////////////////
			static bool CreateDeviceD3D(HWND hWnd);
			static void CleanupDeviceD3D();
			static void CreateRenderTarget();
			static void CleanupRenderTarget();
			static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		};

		class Widget
		{
		public:
			Widget() = default;
			virtual void draw() = 0;
		};

		class Text : public Widget 
		{
		public:
			Text(const std::string& text);
			void draw();
		private:
			std::string text;
		};

		class Window
		{
		public:
			Window(const std::string& windowTitle, bool* isOpen = nullptr);
			~Window();
			void addWidget(Widget& newWidget);
		private:
			std::string windowTitle;
		};
	}
}
#endif