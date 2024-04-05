/**
 * @file EssayManager.h
 * @author Thomas Toaz
 *
 * Class to update and manage the essays being displayed and compared
 */

#ifndef PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAYMANAGER_H
#define PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAYMANAGER_H

class Essay;
class Pair;
class MainFrame;

/**
 * Class to update and manage the essays being displayed and compared
 */
class EssayManager
{
private:
    /// List of all the essays in the manager that can be compared
    std::vector<std::shared_ptr<Essay>> mEssays;

    /// List of all the essay pairs that have not been displayed/used yet
    std::vector<std::shared_ptr<Pair>> mIncompletedPairs;

    /// List of all the essay pairs that have been displayed/used
    std::vector<std::shared_ptr<Pair>> mCompletedPairs;

    /// The mainframe of the program
    MainFrame *mMainFrame;

    /// Current essay pair being displayed
    std::shared_ptr<Pair> mCurrentPair = nullptr;


public:
    /** Assignment operator disabled */
    void operator=(const EssayManager &) = delete;

    EssayManager();

    void CreatePairs();

    void Load(const wxString& filename);
    void Save(const wxString &filename);
    void Import(const wxString& filename);

    void SetMainFrame(MainFrame *mainframe);

    /// Get the current pair being displayed
    std::shared_ptr<Pair> GetCurrentPair() {return mCurrentPair;}

    /// Get the essays the manager is managing
    std::vector<std::shared_ptr<Essay>> *GetEssays() {return &mEssays;}

    /// Get the pairs of essays that have NOT gone through comparison
    std::vector<std::shared_ptr<Pair>> GetIncompletedPairs() {return mIncompletedPairs;}

    /// Get the pairs of essays that HAVE gone through comparison
    std::vector<std::shared_ptr<Pair>> GetCompletedPairs() {return mCompletedPairs;}

    void DisplayPair();
    std::string ListResults();
    void Clear();

    void XmlEssay(wxXmlNode *node);
    void XmlIncompletedPair(wxXmlNode *node);
    void XmlCompletedPair(wxXmlNode *node);
    void XmlCurrentPair(wxXmlNode *node);

};

#endif //PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAYMANAGER_H
