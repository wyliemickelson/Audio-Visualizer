#include <vector>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xmlreshandler.h>
#include <audiovisualizerapp.h>
#include <processwindow.h>
#include <processhandling.h>

class App : public wxApp
{
	public:
		virtual bool OnInit();
};

bool App::OnInit()
{
	ProcessWindow* process_selection = new ProcessWindow(NULL);
	process_selection->Show(true);
	wxWindowList p_children = process_selection->GetChildren();

	//populate process list with information
	int children_len = p_children.size();
	int i = 0;
	wxListBox *process_list = process_selection->getProcessesList();
	if (process_list) 
	{
		std::vector<process_info> processes_info = getCurrentProcesses(getDefaultAudioDevice());
		int len = processes_info.size();
		wxArrayString process_options = wxArrayString();

		for (int i = 0; i < len; ++i)
		{
			process_info process_info = processes_info.at(i);
			std::cout << process_info.name << std::endl;
			process_options.push_back(wxString(process_info.name));
			
		}
		process_list->Append(process_options);
	}
	return true;
}

wxIMPLEMENT_APP(App);
