/**
 * @file AnalysisView.h
 * @author Thomas Toaz
 *
 * Class to manage the viewing of Essay data and analysis
 */

#ifndef PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ANALYSISVIEW_H
#define PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ANALYSISVIEW_H

class EssayManager;

/**
 * Class to manage the viewing of Essay data and analysis
 */
class AnalysisView final : public wxScrolledCanvas
{
private:
    /// The last mouse position
    wxPoint mLastMouse = wxPoint(0, 0);

    /// Essay manager of the program
    std::shared_ptr<EssayManager> mEssayManager;

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftDoubleClick(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

public:
    /** Copy constructor disabled */
    AnalysisView(const AnalysisView &) = delete;
    /** Assignment operator disabled */
    void operator=(const AnalysisView &) = delete;

    AnalysisView(wxFrame* parent, std::shared_ptr<EssayManager> essayManager);



};

#endif //PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ANALYSISVIEW_H
