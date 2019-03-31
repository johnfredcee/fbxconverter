///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "DestPropertyGrid.h"
#include "SourcePropertyGrid.h"

#include "FbxConverter.h"

///////////////////////////////////////////////////////////////////////////

FbxConverterDialogBase::FbxConverterDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* DialogSizrer;
	DialogSizrer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bPropertyGridSizer;
	bPropertyGridSizer = new wxBoxSizer( wxHORIZONTAL );

	m_fbxSourcePropertyGrid = new wxFbxSourcePropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bPropertyGridSizer->Add( m_fbxSourcePropertyGrid, 1, wxALL|wxEXPAND, 5 );

	m_fbxDestPropertyGrid = new wxFbxDestPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bPropertyGridSizer->Add( m_fbxDestPropertyGrid, 1, wxALL|wxEXPAND, 5 );


	DialogSizrer->Add( bPropertyGridSizer, 5, wxEXPAND, 5 );

	wxBoxSizer* bButtonSizer;
	bButtonSizer = new wxBoxSizer( wxHORIZONTAL );

	m_OpenFile = new wxButton( this, wxID_OPEN_BUTTON, wxT("Open"), wxDefaultPosition, wxDefaultSize, 0 );
	bButtonSizer->Add( m_OpenFile, 1, wxALIGN_CENTER|wxALL, 5 );

	m_SaveFileButton = new wxButton( this, wxID_SAVE_BUTTON, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	m_SaveFileButton->Enable( false );

	bButtonSizer->Add( m_SaveFileButton, 1, wxALIGN_CENTER|wxALL, 5 );

	m_ExitButton = new wxButton( this, wxID_EXIT_BUTTON, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	bButtonSizer->Add( m_ExitButton, 1, wxALIGN_CENTER|wxALL, 5 );


	DialogSizrer->Add( bButtonSizer, 1, wxEXPAND, 5 );


	this->SetSizer( DialogSizrer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FbxConverterDialogBase::CloseMainDialog ) );
	m_OpenFile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnOpenFbxFile ), NULL, this );
	m_SaveFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnSaveFbxFile ), NULL, this );
	m_ExitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnExitApp ), NULL, this );
}

FbxConverterDialogBase::~FbxConverterDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FbxConverterDialogBase::CloseMainDialog ) );
	m_OpenFile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnOpenFbxFile ), NULL, this );
	m_SaveFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnSaveFbxFile ), NULL, this );
	m_ExitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnExitApp ), NULL, this );

}
