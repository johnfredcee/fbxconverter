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

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	sourceStaticText = new wxStaticText( this, wxID_ANY, wxT("Source File"), wxDefaultPosition, wxDefaultSize, 0 );
	sourceStaticText->Wrap( -1 );
	bSizer4->Add( sourceStaticText, 0, wxALL, 5 );

	fbxSourcePropertyGrid = new wxFbxSourcePropertyGrid(this, wxID_SOURCE_PG, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer4->Add( fbxSourcePropertyGrid, 1, wxALL|wxEXPAND, 5 );

	fbxSourceFileComboBox = new wxComboBox( this, wxID_SOURCEFILE_COMBO, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer4->Add( fbxSourceFileComboBox, 0, wxALL|wxEXPAND, 5 );


	bPropertyGridSizer->Add( bSizer4, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	destStaticText = new wxStaticText( this, wxID_ANY, wxT("Destination File"), wxDefaultPosition, wxDefaultSize, 0 );
	destStaticText->Wrap( -1 );
	bSizer5->Add( destStaticText, 0, wxALL, 5 );

	fbxDestPropertyGrid = new wxFbxDestPropertyGrid(this, wxID_DEST_PG, wxDefaultPosition, wxDefaultSize, wxPG_DEFAULT_STYLE);
	bSizer5->Add( fbxDestPropertyGrid, 1, wxALL|wxEXPAND, 5 );

	fbxDestFileComboBox = new wxComboBox( this, wxID_DESTFILE_COMBO, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	bSizer5->Add( fbxDestFileComboBox, 0, wxALL|wxEXPAND, 5 );


	bPropertyGridSizer->Add( bSizer5, 1, wxEXPAND, 5 );


	DialogSizrer->Add( bPropertyGridSizer, 5, wxEXPAND, 5 );

	wxBoxSizer* bButtonSizer;
	bButtonSizer = new wxBoxSizer( wxHORIZONTAL );

	openFileButton = new wxButton( this, wxID_OPEN_BUTTON, wxT("Open"), wxDefaultPosition, wxDefaultSize, 0 );
	bButtonSizer->Add( openFileButton, 1, wxALIGN_CENTER|wxALL, 5 );

	saveFileButton = new wxButton( this, wxID_SAVE_BUTTON, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	saveFileButton->Enable( false );

	bButtonSizer->Add( saveFileButton, 1, wxALIGN_CENTER|wxALL, 5 );

	exitButton = new wxButton( this, wxID_EXIT_BUTTON, wxT("Exit"), wxDefaultPosition, wxDefaultSize, 0 );
	bButtonSizer->Add( exitButton, 1, wxALIGN_CENTER|wxALL, 5 );


	DialogSizrer->Add( bButtonSizer, 1, wxEXPAND, 5 );


	this->SetSizer( DialogSizrer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FbxConverterDialogBase::CloseMainDialog ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FbxConverterDialogBase::InitDialog ) );
	fbxSourcePropertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnSourcePGChanged ), NULL, this );
	fbxSourceFileComboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnSourceComboBox ), NULL, this );
	fbxDestPropertyGrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnDestPGChanged ), NULL, this );
	fbxDestFileComboBox->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnDestComboBox ), NULL, this );
	openFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnOpenFbxFile ), NULL, this );
	saveFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnSaveFbxFile ), NULL, this );
	exitButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnExitApp ), NULL, this );
}

FbxConverterDialogBase::~FbxConverterDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FbxConverterDialogBase::CloseMainDialog ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( FbxConverterDialogBase::InitDialog ) );
	fbxSourcePropertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnSourcePGChanged ), NULL, this );
	fbxSourceFileComboBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnSourceComboBox ), NULL, this );
	fbxDestPropertyGrid->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( FbxConverterDialogBase::OnDestPGChanged ), NULL, this );
	fbxDestFileComboBox->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FbxConverterDialogBase::OnDestComboBox ), NULL, this );
	openFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnOpenFbxFile ), NULL, this );
	saveFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnSaveFbxFile ), NULL, this );
	exitButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FbxConverterDialogBase::OnExitApp ), NULL, this );

}
