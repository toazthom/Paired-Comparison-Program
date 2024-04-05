/**
 * @file EssayView.h
 * @author Thomas Toaz
 *
 * Essay display class
 */

#ifndef PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAYVIEW_H
#define PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAYVIEW_H

class Essay;

/**
 * Essay display class
 */
class EssayView final : public wxScrolledCanvas {
private:
    /// The last mouse position
    wxPoint mLastMouse = wxPoint(0, 0);

    /// Pointer to the essay this view is currently displaying
    std::shared_ptr<Essay> mCurrentEssay = nullptr;

    /// Boolean for whether all essays have been compared yet
    bool mFinished = false;

    void OnLeftDown(wxMouseEvent &event);
    void OnLeftDoubleClick(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

public:
    /** Copy constructor disabled */
    EssayView(const EssayView &) = delete;
    /** Assignment operator disabled */
    void operator=(const EssayView &) = delete;

    /**
     * Get this view's essay
     * @return this view's essay
     */
    std::shared_ptr<Essay> GetEssay() {return mCurrentEssay;}

    EssayView(wxFrame* parent);

    void SetEssay(std::shared_ptr<Essay> essay);

    void EndComparison() {mFinished = true;}


};

#endif //PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAYVIEW_H
