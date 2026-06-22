# ALP-ePIC
Simulation and analysis of electrophilic Axion-Like Particle (ALP) production processes at the Electron-Ion Collider (ePIC).

## Requirements
0. Please review [this](https://github.com/eic/ALP-ePIC) page for event generation.
1. **eic-shell**: Latest installation of the EIC container environment. ([Link](https://github.com/eic/eic-shell))
2. **MadGraph5_aMC@NLO (v3.5.13)**: Working installation with the following internal dependencies. ([Link](https://launchpad.net/mg5amcnlo))
   * From the MG5 console, ensure the following are installed:
     ```bash
     install lhapdf6
     install pythia8
     ```
3. **UFO Models**: Place the ALP model directories into `./models/` before running the steering cards.
4. **Custom PDFs**: Copy the provided photon PDF set to your LHAPDF path:
   `./HEPTools/lhapdf6_py3/share/LHAPDF/`

## Quick Start
1. Clone this repository:
  ```bash
  git clone https://github.com/eic/ALP-ePIC-analysis.git
  ```
2. Compile the library:
  ```bash
  cd ALP-ePIC-analysis/analysis
  make
  ```
3. Run the starter macro in ALP-ePIC-analysis/analysis/macros/analysis.C
  ```bash
  root -l -b -q -e 'gSystem->Load("libMyAnalysis.so");' "macros/analysis.C(\"$INPUTFILE\", \"$OUTPUTFILE\")"
  ```
  Alternatively, one can use the premade handling script.
  ```bash
  bash scripts/run_analysis.sh $INPUTFILENAME $OUTPUTFILENAME
  ```
