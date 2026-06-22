#include <iostream>


void analysis(string ifname, string ofname, string treename)
{
    gSystem->Load("libMyAnalysis.so");

    MyAnalysis* ana = new MyAnalysis(ifname, ofname, treename); //AW 20260605 edited to add tree for bdt!!

    ana->Run();
}
