
#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <fbxsdk.h>

#include "FbxConverterApp.h"
#include "FbxConverter.h"
#include "FbxConverterDialog.h"


// Create a new application object : this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
wxIMPLEMENT_APP(FbxConverterApp);

FbxManager *fbxManager;

FbxConverterDialog *mainDialog;

// `Main program' equivalent, creating windows and returning main app frame
bool FbxConverterApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	// The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	fbxManager = FbxManager::Create();
	if (!fbxManager)
	{
		wxLogDebug("Error: Unable to create FBX Manager!");
		return false;
	}
	wxLogDebug("Autodesk FBX SDK version %s", fbxManager->GetVersion());

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings *ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	fbxManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	FbxScene *fbxScene = FbxScene::Create(fbxManager, "My Scene");
	if (!fbxScene)
	{
		wxLogDebug("Error: Unable to create FBX scene!");
		return false;
	}

	mainDialog = new FbxConverterDialog(nullptr);
	mainDialog->ShowModal();
	return true;
}

int FbxConverterApp::OnExit()
{
	mainDialog->Destroy();
	if (fbxManager != nullptr)
	{
		fbxManager->Destroy();
	}
	return wxApp::OnExit();
}
// ----------------------------------------------------------------------------
// custom log target
// ----------------------------------------------------------------------------

class FbxConverterLogGui : public wxLogGui
{
  private:
	virtual void DoShowSingleLogMessage(const wxString &message,
										const wxString &title,
										int style) wxOVERRIDE
	{
		wxMessageDialog dlg(NULL, message, title,
							wxOK | wxCANCEL | wxCANCEL_DEFAULT | style);
		dlg.SetOKCancelLabels(wxID_COPY, wxID_OK);
		dlg.SetExtendedMessage("Note that this is a custom log dialog.");
		dlg.ShowModal();
	}
};

wxLog *FbxConverterAppTraits::CreateLogTarget()
{
	return new FbxConverterLogGui;
}
