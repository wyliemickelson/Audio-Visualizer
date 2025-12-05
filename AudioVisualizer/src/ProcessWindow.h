#pragma once
#include <AudioVisualizerApp.h>
#include <wx/display.h>
#include <VisualizerWindow.h>
#include <vector>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xmlreshandler.h>
#include <processwindow.h>
#include <processhandling.h>
#include <clientdata.h>

class ProcessWindow : public ProcessSelection
{
public:
	void OnClose(wxCloseEvent& event);
	ProcessWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Directional Audio Visualizer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(575, 330), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) : ProcessSelection(parent, id, title, pos, size, style)
	{
		// Create and open Visualizer Window
		visualizer = new VisualizerWindow(NULL);

		//get screen size
		wxDisplay* display = new wxDisplay();
		screen_size = (display->GetClientArea()).GetSize();

		pos_x_slider->SetMax(screen_size.x);
		pos_x_slider->SetValue(0);
		pos_y_slider->SetValue(0);
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

		SetIcon(wxIcon("AAAA"));

		//handle window close event
		Bind(wxEVT_CLOSE_WINDOW, &ProcessWindow::OnClose, this, wxID_ANY);
	}
	wxListBox* getProcessesList();
	void populateProcessList();
	boolean is_rendering = true;
	VisualizerWindow* visualizer;

private:
	void OnRefresh(wxCommandEvent& event) override;
	void OnExit(wxCommandEvent& event) override;
	void OnConfirm(wxCommandEvent& event) override;
	void OnReset(wxCommandEvent& event) override;

	//customization input callbacks
	//sets text boxes to same number as slider & vice versa
	void OnSL_Pos(wxCommandEvent& event) override;
	void OnSL_Size(wxCommandEvent& event) override;
	void OnSize(wxCommandEvent& event) override;
	void OnPos(wxCommandEvent& event) override;

	void SetPreviewPos();
	wxFrame* preview_window;
	wxSize screen_size;
};
