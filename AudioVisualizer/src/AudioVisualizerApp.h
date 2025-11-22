///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class Options
///////////////////////////////////////////////////////////////////////////////
class Options : public wxFrame
{
	private:

	protected:

	public:

		Options( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Options();

};

///////////////////////////////////////////////////////////////////////////////
/// Class ProcessSelection
///////////////////////////////////////////////////////////////////////////////
class ProcessSelection : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel1;
		wxStaticText* m_staticText2;
		wxListBox* processes_list;
		wxButton* confirm;
		wxButton* cancel;
		wxCheckBox* remember_checkbox;

		// Virtual event handlers, override them in your derived class
		virtual void OnConfirm( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExit( wxCommandEvent& event ) { event.Skip(); }


	public:

		ProcessSelection( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Directional Audio Visualizer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,330 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~ProcessSelection();

};

