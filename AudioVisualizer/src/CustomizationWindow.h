#pragma once
#include <wx/wx.h>
#include <wx/string.h>
#include <string.h>
#include <AudioVisualizerApp.h>
#include <wx/display.h>

class CustomizationWindow : public Customization 
{
public:
	void OnExit(wxCommandEvent& event) override;
	void OnApply(wxCommandEvent& event) override;

	//customization input callbacks
	//sets text boxes to same number as slider & vice versa
	void OnSL_Pos(wxCommandEvent& event) override;
	void OnSL_Size(wxCommandEvent& event) override;
	void OnSize(wxCommandEvent& event) override;
	void OnPos(wxCommandEvent& event) override;

	void SetPreviewPos();

	CustomizationWindow(wxSize size = wxSize(235,300)) : Customization(NULL, wxID_ANY, _("Customization"), wxDefaultPosition, size, wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL)
	{
		//get screen size
		wxDisplay* display = new wxDisplay();
		wxSize screen_size = (display->GetClientArea()).GetSize();

		pos_x_slider->SetMax(screen_size.x);
		pos_y_slider->SetMax(screen_size.y);

		size_x_slider->SetMax(screen_size.x);
		size_x_slider->SetValue(screen_size.x);
		size_y_slider->SetValue(50);
		size_y_slider->SetMax(screen_size.y);

		size_x_text->SetValue(std::to_string(screen_size.x));
		size_y_text->SetValue(std::to_string(50));

		//create preview window
		preview_window = new wxFrame(NULL, wxID_ANY, "Preview", wxPoint(0,0), wxSize(screen_size.x, 50), wxFRAME_NO_TASKBAR, wxFrameNameStr);
		preview_window->Show(true);

	};

private:
	wxFrame* preview_window;
		
};