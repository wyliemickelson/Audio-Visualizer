#pragma once
#include <ProcessWindow.h>
#include <CustomizationWindow.h>
class App : public wxApp
{
	public:
		virtual bool OnInit();
		void OnCustomize(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
	private:
		ProcessWindow* process_window;
		CustomizationWindow* customization;
};

