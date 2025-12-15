#pragma once
#include <ProcessWindow.h>
#include <CustomizationWindow.h>
#include <Tray.h>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

class App : public wxApp
{
	public:
		const int FPS = 60;
		Clock::time_point last_render;
		bool render_loop_on;
		virtual bool OnInit();
		void onIdle(wxIdleEvent& evt);
		void OnCustomize(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void activateRenderLoop(bool on);
	private:
		ProcessWindow* process_window;
		Tray* tray;
		CustomizationWindow* customization;
};



