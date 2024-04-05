/**
 * @file MainFrame.cpp
 * @author Thomas Toaz
 */

#include "pch.h"

#include <wx/xrc/xmlres.h>
#include <wx/stdpaths.h>

#include "MainFrame.h"

#include "EssayView.h"
#include "AnalysisView.h"
#include "EssayManager.h"
#include "Essay.h"

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 * @param resourcesDir Directory path containing resources
 */
MainFrame::MainFrame(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{

}



/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{

    wxXmlResource::Get()->LoadFrame(this, nullptr, L"MainFrame");
#ifdef WIN32
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif


    auto sizer = new wxBoxSizer( wxHORIZONTAL );

    auto imagesDir = mResourcesDir + ImagesDirectory;

    mEssayManager = std::make_shared<EssayManager>();

    mEssayManager->SetMainFrame(this);


    mEssayView1 = new EssayView(this);
    mEssayView2 = new EssayView(this);
    mAnalysisView = new AnalysisView(this, mEssayManager);

    sizer->Add(mEssayView1,1, wxEXPAND | wxALL, 5);
    sizer->Add(mEssayView2,1, wxEXPAND | wxALL, 5 );
    sizer->Add(mAnalysisView,1, wxEXPAND | wxALL );

    mAnalysisView->Hide();

    SetSizer( sizer );
    Layout();

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnImport, this, XRCID("ImportEssays"));
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileSave, this, wxID_SAVEAS);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnFileOpen, this, wxID_OPEN);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::SelectLeft, this, XRCID("SelectLeft"));
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::SelectRight, this, XRCID("SelectRight"));

}



/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Application about box menu handler
 * @param event The menu command event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxDialog aboutDlg;
    wxXmlResource::Get()->LoadDialog(&aboutDlg, this, L"AboutDialog");
    aboutDlg.ShowModal();
}


/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
//    mViewComparison->Stop();
    Destroy();
}

/**
 * File>Save menu handler
 * @param event Menu event
 */
void MainFrame::OnFileSave(wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(this, L"Save Comparison file", L"", L"",
                                L"Comparison Files (*.comp)|*.comp", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();

    mEssayManager->Save(filename);

}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void MainFrame::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, _("Load Comparison file"), "", "",
                                "Comparison Files (*.comp)|*.comp", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mEssayManager->Load(filename);
    Refresh();
}

/**
 * File>Import menu handler
 * @param event Menu event
 */
void MainFrame::OnImport(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, _("Load CSV file of essays"), "", "",
                                "CSV Files (*.csv)|*.csv", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mEssayManager->Import(filename);
    Refresh();
}

/**
 * Handle the selection of an essay
 * @param event Menu event
 */
void MainFrame::SelectLeft(wxCommandEvent& event)
{
    if(mEssayManager->GetCurrentPair())
    {
        mEssayView1->GetEssay()->SelectOver(mEssayView2->GetEssay()->GetId());
        mEssayView2->GetEssay()->LoseTo(mEssayView1->GetEssay()->GetId());
        mEssayManager->DisplayPair();
    }
}

/**
 * Handle the selection of an essay
 * @param event Menu event
 */
void MainFrame::SelectRight(wxCommandEvent& event)
{
    if(mEssayManager->GetCurrentPair())
    {
        mEssayView1->GetEssay()->LoseTo(mEssayView2->GetEssay()->GetId());
        mEssayView2->GetEssay()->SelectOver(mEssayView1->GetEssay()->GetId());
        mEssayManager->DisplayPair();
    }
}

void MainFrame::EndComparison()
{
    mEssayView1->EndComparison();
    mEssayView2->EndComparison();

    mEssayView1->Hide();
    mEssayView2->Hide();

    mAnalysisView->Show();

    // Refresh Layout
    GetSizer()->Layout();
}




