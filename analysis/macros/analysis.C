#include <iostream>

void analysis(string ifname, string ofname, string treefname = "")
{
    gSystem->Load("libMyAnalysis.so");

    MyAnalysis* ana;
    if (treefname == "") ana = new MyAnalysis(ifname, ofname);
    else ana = new MyAnalysis(ifname, ofname, treefname);

    ana->Run();
}
