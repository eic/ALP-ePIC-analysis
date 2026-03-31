#include "MyAnalysis.h"


void MyAnalysis::ReserveHistograms()
{
    h1.clear();
    h2.clear();
    h3.clear();
    mOutFile->cd();

    h1["event__stage"] = new TH1F("event__stage", "", 20, 0, 20);

    

    for (map<string,TH1*>::const_iterator itr = h1.begin(); itr != h1.end(); ++itr) itr->second->Sumw2();
    for (map<string,TH2*>::const_iterator itr = h2.begin(); itr != h2.end(); ++itr) itr->second->Sumw2();
    for (map<string,TH3*>::const_iterator itr = h3.begin(); itr != h3.end(); ++itr) itr->second->Sumw2();
}
