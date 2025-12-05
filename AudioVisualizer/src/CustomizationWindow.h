#pragma once
#include <wx/wx.h>
#include <wx/string.h>
#include <string.h>
#include <AudioVisualizerApp.h>
#include <wx/display.h>
#include <VisualizerWindow.h>

class CustomizationWindow : public Customization 
{
public:
	//customization input callbacks
	void OnReset(wxCommandEvent& event) override;
	//sets text boxes to same number as slider & vice versa
	void OnSL_Pos(wxCommandEvent& event) override;
	void OnSL_Size(wxCommandEvent& event) override;
	void OnSize(wxCommandEvent& event) override;
	void OnPos(wxCommandEvent& event) override;
	void OnExit(wxCommandEvent& event) override;

	void SetPreviewPos();

	CustomizationWindow(VisualizerWindow* visualizer, wxSize size = wxSize(300,300)) : Customization(NULL, wxID_ANY, _("Customization"), wxDefaultPosition, size, wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL | wxSTAY_ON_TOP)
	{
		//get screen size
		SetIcon(wxIcon("aaaa"));
		this->visualizer = visualizer;
		wxDisplay* display = new wxDisplay();
		screen_size = (display->GetClientArea()).GetSize();

		wxSize vis_size = visualizer->GetSize();
		wxPoint pos = visualizer->GetPosition();
		pos_x_slider->SetMax(screen_size.x);
		pos_y_slider->SetMax(screen_size.y);
		pos_x_slider->SetValue(pos.x);
		pos_y_slider->SetValue(pos.y);

		size_x_slider->SetMax(screen_size.x);
		size_x_slider->SetValue(vis_size.x);
		size_y_slider->SetValue(vis_size.y);
		size_y_slider->SetMax(screen_size.y);

		size_x_text->SetValue(std::to_string(vis_size.x));
		size_y_text->SetValue(std::to_string(vis_size.y));
	};

private:
	wxSize screen_size;
	VisualizerWindow* visualizer;
		
};