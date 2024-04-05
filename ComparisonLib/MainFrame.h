/**
 * @file MainFrame.h
 * @author Thomas Toaz
 *
 * The top-level (main) frame of the application
 */

#ifndef PAIRED_COMPARISON_PROGRAM_COMPARISONLIB_MAINFRAME_H
#define PAIRED_COMPARISON_PROGRAM_COMPARISONLIB_MAINFRAME_H

class EssayView;
class AnalysisView;
class EssayManager;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our first essay being shown
    EssayView *mEssayView1;

    /// View class for our second essay being shown
    EssayView *mEssayView2;

    /// Essay manager for handling essays
    std::shared_ptr<EssayManager> mEssayManager;

    /// View class for analysis of essay comparison data
    AnalysisView *mAnalysisView;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent&);
    void OnClose(wxCloseEvent &event);

    void OnImport(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnFileSave(wxCommandEvent& event);


    /// The resources directory to use
    std::wstring mResourcesDir;

public:
    MainFrame(std::wstring resourcesDir);

    void Initialize();

    /**
     * Get the essayview1 of the program
     * @return
     */
    EssayView * GetEssayView1() const {return mEssayView1;}

    /**
     * Get the essayview2 of the program
     * @return
     */
    EssayView * GetEssayView2() const {return mEssayView2;}

    void SelectLeft(wxCommandEvent& event);
    void SelectRight(wxCommandEvent& event);

    void EndComparison();
};

#endif //PAIRED_COMPARISON_PROGRAM_COMPARISONLIB_MAINFRAME_H
