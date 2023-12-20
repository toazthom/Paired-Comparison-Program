/**
 * @file ViewHome.h
 * @author Thomas Toaz
 *
 * View class for our Home Page
 */

#ifndef PAIREDCOMPARISONPROGRAM_COMPARISONLIB_VIEWHOME_H
#define PAIREDCOMPARISONPROGRAM_COMPARISONLIB_VIEWHOME_H

/**
 * View class for our Home Page
 */
class ViewHome final : public wxScrolledCanvas{
private:
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftDoubleClick(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);

    /// The last mouse position
    wxPoint mLastMouse = wxPoint(0, 0);

public:
    /// The current mouse mode
    enum class Mode {Move, Rotate};

    /// The currently set mouse mode
    Mode mMode = Mode::Move;

public:
    ViewHome(wxFrame* parent);


};

#endif //PAIREDCOMPARISONPROGRAM_COMPARISONLIB_VIEWHOME_H
