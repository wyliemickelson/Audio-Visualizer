#include <VisualizerWindow.h>
#include <vector>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xmlreshandler.h>
#include <audiovisualizerapp.h>
#include <processwindow.h>
#include <processhandling.h>
#include <clientdata.h>
#include <wx/gdicmn.h>
#include <MainApp.h>

bool App::OnInit()
{
	ProcessWindow* process_selection = new ProcessWindow(NULL);
	process_selection->Show(true);

	//populate process list with information
	wxWindowList p_children = process_selection->GetChildren();
	//wxListBox *process_list = process_selection->getProcessesList();
	process_selection->populateProcessList();

	return true;
}

