#pragma once

class ProcessWindow : public ProcessSelection
{
public:
	ProcessWindow(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Directional Audio Visualizer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(350, 330), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) : ProcessSelection(parent, id, title, pos, size, style) {};
	wxListBox* getProcessesList();
protected:
	void OnExit(wxCommandEvent& event) override;
};
