#include <iostream>


void analysis(string ifname, string ofname, string treename)
{
    gSystem->Load("libMyAnalysis.so");

    MyAnalysis* ana = new MyAnalysis(ifname, ofname, treename);

    ana->Run();
}
