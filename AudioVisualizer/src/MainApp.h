#pragma once
#include <ProcessWindow.h>
#include <CustomizationWindow.h>
#include <Tray.h>
class App : public wxApp
{
	public:
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



