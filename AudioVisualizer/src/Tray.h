#pragma once
#include <wx/wx.h>
#include <wx/taskbar.h>
#include <ProcessWindow.h>
#include <MainApp.h>
class Tray : public wxTaskBarIcon
{
public:
	Tray(wxMenu* menu) : wxTaskBarIcon()
	{
		this->menu = menu;
		SetIcon(wxIcon("AAAA"));

	}
	wxMenu* GetPopupMenu() override;
private:
	wxMenu* menu;
};