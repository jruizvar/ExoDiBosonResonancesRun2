#!/bin/bash 
#
# Submit jobs to crab. Usage: 
#
#       cmsenv; source /cvmfs/cms.cern.ch/crab3/crab.sh; source submitAll.sh

crab submit Data.inputDataset='/SingleMuon/Run2016B-PromptReco-v2/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2016C-PromptReco-v2/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2016D-PromptReco-v2/MINIAOD'

# Switch to electron channel
sed -i '6 s/mu/el/' crabConfig.py

crab submit Data.inputDataset='/SingleElectron/Run2016B-PromptReco-v2/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2016C-PromptReco-v2/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2016D-PromptReco-v2/MINIAOD'

# Switch back to muon channel
sed -i '6 s/el/mu/' crabConfig.py
