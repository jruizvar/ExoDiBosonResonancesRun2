Instructions to setup the ExoDiBosonResonances code
========

```
cmsrel CMSSW_8_0_22
cd CMSSW_8_0_22/src
cmsenv
git cms-init # This will allow you to checkout packages in official CMSSW
git cms-merge-topic jruizvar:egm_id_80X_v2
git clone -b Analysis80X git@github.com:jruizvar/ExoDiBosonResonancesRun2.git ExoDiBosonResonances
scram b -j 9
```

#IMPORTANT: 

These instructions should always be up-to-date with the ones in our Twiki:

`https://twiki.cern.ch/twiki/bin/view/CMS/ExoDiBosonResonancesRun2`
