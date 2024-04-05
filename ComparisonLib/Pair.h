/**
 * @file Pair.h
 * @author Thomas Toaz
 *
 * Pair class to store essay pairs in
 */

#ifndef PAIREDCOMPARISONPROGRAM_COMPARISONLIB_PAIR_H
#define PAIREDCOMPARISONPROGRAM_COMPARISONLIB_PAIR_H

class Essay;

/**
 * Pair class to store essay pairs in
 */
class Pair
{
private:
    /// First essay of the pair
    std::shared_ptr<Essay> mEssay1;

    /// Second essay of the pair
    std::shared_ptr<Essay> mEssay2;


public:
    Pair(std::shared_ptr<Essay> &essay1, std::shared_ptr<Essay> &essay2);

    /** Default constructor disabled */
    Pair() = delete;
    /** Copy constructor disabled */
    Pair(const Pair &) = delete;
    /** Assignment operator disabled */
    void operator=(const Pair &) = delete;

    /**
     * Get the first essay in this pair of essays
     * @return
     */
    std::shared_ptr<Essay> GetEssay1() const {return mEssay1;}

    /**
     * Get the second essay in this pair of essays
     * @return
     */
    std::shared_ptr<Essay> GetEssay2() const {return mEssay2;}

    wxXmlNode * XmlSave(wxXmlNode *node);



};

#endif //PAIREDCOMPARISONPROGRAM_COMPARISONLIB_PAIR_H
