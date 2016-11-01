#!/bin/bash 
#
# Submit jobs to crab. Usage: 
#
#       cmsenv; source /cvmfs/cms.cern.ch/crab3/crab.sh; source submitAll.sh

crab submit Data.inputDataset='/SingleMuon/Run2016B-23Sep2016-v3/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2016C-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2016D-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2016E-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2016F-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleMuon/Run2016G-23Sep2016-v1/MINIAOD'

# Switch to electron channel
sed -i '6 s/mu/el/' crabConfig.py

crab submit Data.inputDataset='/SingleElectron/Run2016B-23Sep2016-v3/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2016C-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2016D-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2016E-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2016F-23Sep2016-v1/MINIAOD'
crab submit Data.inputDataset='/SingleElectron/Run2016G-23Sep2016-v1/MINIAOD'


# Switch back to muon channel
sed -i '6 s/el/mu/' crabConfig.py
