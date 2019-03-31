
#include <fbxsdk.h>
#include <wx/wx.h>
#include <wx/filedlg.h>
#include "FbxConverter.h"
#include "FbxConverterDialog.h"

//wxString FbxConverterDialog::filterString = wxT("FBX (*.fbx)|*.fbx|Collada DAE (*.dae)|*.dae|Alias OBJ (*.obj)|*.obj|AutoCAD DXF (*.dxf)|*.dxf");


void FbxConverterDialog::OnOpenFbxFile(wxCommandEvent &event) 
{
		fbxsdk::FbxIOPluginRegistry *fbxIOPluginRegistry = fbxManager->GetIOPluginRegistry();
		wxString filterString;
		int formatCount = fbxIOPluginRegistry->GetReaderFormatCount();
		for (int formatIndex = 0; formatIndex < formatCount; ++formatIndex)
		{
			wxString formatExtension(fbxIOPluginRegistry->GetReaderFormatExtension(formatIndex));
			wxString formatDescription(fbxIOPluginRegistry->GetReaderFormatDescription(formatIndex));
			wxLogDebug("Format %i is %s (%s)", formatIndex, formatExtension.c_str(), formatDescription.c_str());
			filterString.Append(wxString::Format("%s|(*.%s)", formatDescription, formatExtension));
			if (formatIndex < formatCount-1)
			{
				filterString.Append("|");
			}
		}

		wxFileDialog openFileDialog(this, "Open File", "", "",
									filterString, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (openFileDialog.ShowModal() == wxID_CANCEL)
			return; // the user changed idea...

		wxString fileToImport(openFileDialog.GetPath());
		wxLogDebug("Reading %s", fileToImport.c_str());
		int SDKMajor, SDKMinor, SDKRevision;
		FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);
		wxLogDebug("Autodesk FBX SDK Version %d:%d:%d", SDKMajor, SDKMinor, SDKRevision);


		// Create an importer.
		FbxImporter *fbxImporter = FbxImporter::Create(fbxManager, "");

		// Initialize the importer by providing a filename.
		const bool bImportStatus = fbxImporter->Initialize(openFileDialog.GetPath().c_str(), -1, fbxManager->GetIOSettings());
		if (bImportStatus)
		{
			int FileMajor, FileMinor, FileRevision;
			fbxImporter->GetFileVersion(FileMajor, FileMinor, FileRevision);
			if (fbxImporter->IsFBX())
			{
				wxLogDebug("FBX file format version is %d.%d.%d\n\n", FileMajor, FileMinor, FileRevision);
				int animStackCount = fbxImporter->GetAnimStackCount();

				wxLogDebug("Number of animation stacks %d", animStackCount);
				wxLogDebug("Current animation stack:\"%s\"", fbxImporter->GetActiveAnimStackName().Buffer());
				for (int i = 0; i < animStackCount; ++i)
				{
					FbxTakeInfo *takeInfo = fbxImporter->GetTakeInfo(i);

					wxLogDebug("Animation stack %d", i);
					wxLogDebug("Name:\"%s\"", takeInfo->mName.Buffer());
					wxLogDebug("Description:\"%s\"", takeInfo->mDescription.Buffer());
					wxLogDebug("Import name:\"%s\"", takeInfo->mImportName.Buffer());
					wxLogDebug("Import state%s", takeInfo->mSelect ? "true" : "false");
				}
				IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
				IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
				IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
				IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
				IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
				IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
				IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
				FbxScene *fbxScene = FbxScene::Create(fbxManager, openFileDialog.GetFilename().c_str());
				if (fbxScene)
				{
					bool importStatus = fbxImporter->Import(fbxScene);
					if (importStatus)
					{
						FbxStatus status;
						FbxArray<FbxString *> details;
						FbxSceneCheckUtility sceneCheck(fbxScene, &status, &details);
						bool sceneOk = sceneCheck.Validate(FbxSceneCheckUtility::eCkeckData);
						if (sceneOk == false)
						{
							for (int i = 0; i < details.GetCount(); ++i)
							{
								wxLogDebug("Error: %s", details[i]->Buffer());
							}
							FbxArrayDelete<FbxString *>(details);
						}
						else
						{
							if (mainScene != nullptr)
							{
								mainScene->Destroy();
							}
							mainScene = fbxScene;
							m_SaveFileButton->Enable(true);
						}
					}
					else
					{
						wxLogDebug("Fbx scene inport failed.");
					}
				}
				else
				{
					wxLogDebug("Unable to create fbx scene.");
				}
				fbxImporter->Destroy();
			}
		}
		else // bImportStatus
		{
			FbxString error = fbxImporter->GetStatus().GetErrorString();
			wxLogDebug("Failed to create importer for %s", openFileDialog.GetPath().c_str());
			wxLogDebug("Error returned %s", error.Buffer());
		}
		event.Skip();
	}
	
	void FbxConverterDialog::OnSaveFbxFile(wxCommandEvent &event)
	{
		wxString filterString;
		fbxsdk::FbxIOPluginRegistry *fbxIOPluginRegistry = fbxManager->GetIOPluginRegistry();
		int formatCount = fbxIOPluginRegistry->GetWriterFormatCount();
		for (int formatIndex = 0; formatIndex < formatCount; ++formatIndex)
		{
			wxString formatExtension(fbxIOPluginRegistry->GetWriterFormatExtension(formatIndex));
			wxString formatDescription(fbxIOPluginRegistry->GetWriterFormatDescription(formatIndex));
			wxLogDebug("Format %i is %s (%s)", formatIndex, formatExtension.c_str(), formatDescription.c_str());
			filterString.Append(wxString::Format("%s|(*.%s)", formatDescription, formatExtension));
			if (formatIndex < formatCount-1)
			{
				filterString.Append("|");
			}
		}

		const bool bEmbedMedia = false;
		wxFileDialog saveFileDialog(this, "Save File", "", "",
									filterString, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return; // the user changed idea...
		wxString fileToExport(saveFileDialog.GetPath());	
		wxLogDebug("Writing %s", fileToExport.c_str());
		FbxExporter *fbxExporter = FbxExporter::Create(fbxManager, "");
		int saveFormatIndex =  saveFileDialog.GetFilterIndex();
		if (fbxExporter != nullptr)
		{
			if (saveFormatIndex >= 0)
			{

				// Set the export states. By default, the export states are always set to
				// true except for the option eEXPORT_TEXTURE_AS_EMBEDDED. The code below
				// shows how to change these states.
				IOS_REF.SetBoolProp(EXP_FBX_MATERIAL, true);
				IOS_REF.SetBoolProp(EXP_FBX_TEXTURE, true);
				IOS_REF.SetBoolProp(EXP_FBX_EMBEDDED, bEmbedMedia);
				IOS_REF.SetBoolProp(EXP_FBX_SHAPE, true);
				IOS_REF.SetBoolProp(EXP_FBX_GOBO, true);
				IOS_REF.SetBoolProp(EXP_FBX_ANIMATION, true);
				IOS_REF.SetBoolProp(EXP_FBX_GLOBAL_SETTINGS, true);
			}
		}
		bool bExporterInitialised = fbxExporter->Initialize(fileToExport.c_str(), saveFormatIndex, fbxManager->GetIOSettings());
		if (bExporterInitialised)
		{
			int SDKMajor, SDKMinor, SDKRevision;
			FbxManager::GetFileFormatVersion(SDKMajor, SDKMinor, SDKRevision);
			wxLogDebug("Autodesk FBX SDK Version %d:%d:%d", SDKMajor, SDKMinor, SDKRevision);
			fbxExporter->Export(mainScene);
			fbxExporter->Destroy();
		}
		else 
		{
			wxLogDebug("Failed to initialise exporter.");
   			wxLogDebug("Error returned: %s\n\n", fbxExporter->GetStatus().GetErrorString());
     	}

	}