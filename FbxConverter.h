///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/combobox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_SOURCE_PG 1000
#define wxID_SOURCEFILE_COMBO 1001
#define wxID_SOURCEUPAXISTEXT 1002
#define wxID_SCENE_TREE 1003
#define wxID_DEST_PG 1004
#define wxID_DESTFILE_COMBO 1005
#define wxID_DESTUPAXISCOMBO 1006
#define wxID_OPEN_BUTTON 1007
#define wxID_SAVE_BUTTON 1008
#define wxID_EXIT_BUTTON 1009

///////////////////////////////////////////////////////////////////////////////
/// Class FbxConverterDialogBase
///////////////////////////////////////////////////////////////////////////////
class FbxConverterDialogBase : public wxDialog
{
	private:

	protected:
		wxStaticText* sourceStaticText;
		wxPropertyGrid* fbxSourcePropertyGrid;
		wxComboBox* fbxSourceFileComboBox;
		wxStaticText* fbxSourceUpAxisLabel;
		wxTextCtrl* fbxSourceUpAxisText;
		wxTreeCtrl* sceneTreeCtrl;
		wxStaticText* destStaticText;
		wxPropertyGrid* fbxDestPropertyGrid;
		wxComboBox* fbxDestFileComboBox;
		wxStaticText* fbDestUpAxisLabel;
		wxComboBox* fbxDestUpAxisComboBox;
		wxButton* openFileButton;
		wxButton* saveFileButton;
		wxButton* exitButton;

		// Virtual event handlers, overide them in your derived class
		virtual void CloseMainDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void InitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnPGChanged( wxPropertyGridEvent& event ) { event.Skip(); }
		virtual void OnSourceComboBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDestComboBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOpenFbxFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSaveFbxFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExitApp( wxCommandEvent& event ) { event.Skip(); }


	public:

		FbxConverterDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Fbx Converter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 980,794 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~FbxConverterDialogBase();

};

