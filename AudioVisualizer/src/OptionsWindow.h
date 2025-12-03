#include <AudioVisualizerApp.h>

class OptionsWindow : public Options
{
public:
	void OnQuit(wxCommandEvent& event) override;
	void OnCustomize(wxCommandEvent& event) override;
	OptionsWindow() : Options(NULL, wxID_ANY, _("Visualizer"), wxDefaultPosition, wxSize(200, 100), wxSTAY_ON_TOP | wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) {};
};