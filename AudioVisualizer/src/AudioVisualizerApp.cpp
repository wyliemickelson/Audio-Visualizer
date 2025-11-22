///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "AudioVisualizerApp.h"

///////////////////////////////////////////////////////////////////////////

Options::Options( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );


	this->Centre( wxBOTH );
}

Options::~Options()
{
}

VisualizerFrame::VisualizerFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* options_sizer;
	options_sizer = new wxBoxSizer( wxVERTICAL );


	this->SetSizer( options_sizer );
	this->Layout();

	this->Centre( wxBOTH );
}

VisualizerFrame::~VisualizerFrame()
{
}

ProcessSelection::ProcessSelection( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* options_sizer;
	options_sizer = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, _("Please select which application to visualize:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL, 5 );

	processes_list = new wxListBox( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	processes_list->SetMinSize( wxSize( 320,200 ) );

	bSizer3->Add( processes_list, 0, wxALL, 5 );

	wxBoxSizer* confirmation;
	confirmation = new wxBoxSizer( wxHORIZONTAL );

	confirm = new wxButton( m_panel1, wxID_ANY, _("Ok"), wxDefaultPosition, wxSize( -1,50 ), 0 );
	confirmation->Add( confirm, 0, wxALL, 5 );

	cancel = new wxButton( m_panel1, wxID_ANY, _("Cancel"), wxDefaultPosition, wxSize( -1,50 ), 0 );
	confirmation->Add( cancel, 0, wxALL, 5 );

	remember_checkbox = new wxCheckBox( m_panel1, wxID_ANY, _("Remember my Selection"), wxDefaultPosition, wxSize( -1,50 ), 0 );
	confirmation->Add( remember_checkbox, 0, wxALL, 5 );


	bSizer3->Add( confirmation, 1, wxEXPAND, 5 );


	m_panel1->SetSizer( bSizer3 );
	m_panel1->Layout();
	bSizer3->Fit( m_panel1 );
	options_sizer->Add( m_panel1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( options_sizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	confirm->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnConfirm ), NULL, this );
	cancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ProcessSelection::OnExit ), NULL, this );
}

ProcessSelection::~ProcessSelection()
{
}
