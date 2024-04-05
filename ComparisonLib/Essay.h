/**
 * @file Essay.h
 * @author Thomas Toaz
 *
 * Essay class to store essay data
 */

#ifndef PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAY_H
#define PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAY_H

/**
 * Essay class to store essay data
 */
class Essay
{
private:
    /// Essay ID
    std::string mId = "";

    /// Essay text content
    std::string mContent = "";

    /// List of the ID's of the essays that this essay was chosen over in comparison
    std::vector<std::string> mChosenOver;

    /// List of the ID's of the essays that this essay lost to in comparison
    std::vector<std::string> mLostTo;


public:
    Essay(const std::string &id, const std::string &content);

    /** Default constructor disabled */
    Essay() = delete;
    /** Copy constructor disabled */
    Essay(const Essay &) = delete;
    /** Assignment operator disabled */
    void operator=(const Essay &) = delete;

    /// Get the essay ID
    std::string GetId() const {return mId;}

    /// Get the essay text/content
    std::string GetContent() const {return mContent;}

    void SelectOver(std::string loserId);
    void LoseTo(std::string winnerId);

    /// Get the list of essay ids that the essay was selected over
    std::vector<std::string> GetSelectedOver() const {return mChosenOver;}

    /// Get the list of essay ids that the essay lost to
    std::vector<std::string> GetLostTo() const {return mLostTo;}

    wxXmlNode * XmlSave(wxXmlNode *node);


};

#endif //PAIREDCOMPARISONPROGRAM_COMPARISONLIB_ESSAY_H
