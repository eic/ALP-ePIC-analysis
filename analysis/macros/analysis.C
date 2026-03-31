#include <iostream>


void analysis(string ifname, string ofname)
{
    gSystem->Load("libMyAnalysis.so");

    MyAnalysis* ana = new MyAnalysis(ifname, ofname);

    ana->Run();
}
