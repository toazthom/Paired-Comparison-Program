/**
 * @file PairedComparisonApp.h
 * @author Toazt
 *
 * Main application class
 */

#ifndef PAIRED_COMPARISON_PROGRAM__PAIREDCOMPARISONAPP_H
#define PAIRED_COMPARISON_PROGRAM__PAIREDCOMPARISONAPP_H

/**
 * Main application class
 */
class PairedComparisonApp : public wxApp {
public:
    bool OnInit() override;
    int OnExit() override;
};

#endif //PAIRED_COMPARISON_PROGRAM__PAIREDCOMPARISONAPP_H
