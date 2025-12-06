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
#include <Tray.h>

bool App::OnInit()
{
	//#ifdef _DEBUG
	//	AllocConsole();
	//	freopen("CONOUT$", "w", stdout);
	//#endif

	process_window = new ProcessWindow(NULL);
	process_window->Show(true);

	//populate process list with information
	wxWindowList p_children = process_window->GetChildren();
	//wxListBox *process_list = process_selection->getProcessesList();
	process_window->populateProcessList();

	// create tray icon
	wxMenu *menu = new wxMenu();
	menu->Append(wxID_PROPERTIES, "Customize");
	menu->Append(wxID_EXIT, "Exit");
	menu->Bind(wxEVT_MENU, &App::OnExit, this, wxID_EXIT);
	menu->Bind(wxEVT_MENU, &App::OnCustomize, this, wxID_PROPERTIES);
	Tray *tray = new Tray(menu);


	return true;
}

void App::OnCustomize(wxCommandEvent& event)
{
	customization = new CustomizationWindow(process_window->visualizer);
	customization->Show(true);
}

void App::OnExit(wxCommandEvent& event)
{
	process_window->Close();
	customization->Close();
}

wxIMPLEMENT_APP(App);
