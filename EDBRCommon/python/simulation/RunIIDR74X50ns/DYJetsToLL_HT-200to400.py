import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/00077244-BF32-E511-9977-001E675A622F.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/28154202-5934-E511-AF62-20CF3027A568.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/46B2D08A-C135-E511-87AC-002618943949.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/84AB4BDA-9D34-E511-8967-6C3BE5B59150.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/A201200B-F333-E511-813E-001E673968F1.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/B0AB1E1B-7C34-E511-B439-0026181D28D0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/B8BBD8A2-9B33-E511-86E5-001517F7F504.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/20000/DE882265-6F33-E511-9F81-28924A3504DA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/16364293-D931-E511-81B9-00266CFFA1FC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/2E80EB32-C333-E511-AD21-00261894387C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/3CFED340-C333-E511-834D-002590A8881E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/421C1D2C-D131-E511-AB81-001517FA7A98.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/5CA68028-C232-E511-9F7C-001E675A6C2A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/5CBD392C-D131-E511-B5FA-001E67A40604.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/7E5B96EB-A332-E511-A0B6-0015C5F825CE.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/94B9EE28-C331-E511-AB1C-00269E95ACFC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/D0FD6E46-AE32-E511-A2EF-002590AC4C3E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/30000/D400335E-D131-E511-8F57-001E67A3FF1F.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/00BC2A51-CC32-E511-9800-C81F66DD6743.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/229B7EF2-6133-E511-97C8-02163E011A4B.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/3CC35350-6033-E511-8A0C-842B2B76653D.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/70F5365A-3A33-E511-A176-90B11C06E1A0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/841510BC-3933-E511-A837-001E67A3F3DF.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/8A660B6A-3933-E511-A291-E0CB4E2E4E6A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/8AFECD4C-6033-E511-AABA-008CFA1979BC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/9038064D-6033-E511-82EA-485B398168B7.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/946FCEDB-4133-E511-8D98-0CC47A13CD44.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/B8F89BD9-5F33-E511-9028-003048D15DF0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/BCD0044E-6033-E511-89DA-002590A8880E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/C8F98DEF-5F33-E511-B87B-AC853DA0692A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/40000/D0B8D30E-E031-E511-A04E-C81F66B7910D.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/1A3F6B90-BC34-E511-8C8F-002590D9D8B2.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/1ABB2A73-BC34-E511-A38F-002590A887F8.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/1E1E7355-9434-E511-8B17-02163E0133F0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/56E03804-6333-E511-B831-001E675A659A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/6A4263F8-7536-E511-9674-20CF3027A575.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/80567068-BC34-E511-B3AB-00259059642A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/86E5125D-4534-E511-9CA2-D4AE529D9537.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/94C8DC89-BC34-E511-8E3B-842B2B7669E2.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/9A9F204C-3533-E511-B77A-001E67583BE0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/A41E5966-BC34-E511-91DE-0025905B858C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/A4FEE9E3-3333-E511-8820-00259074AE52.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/B42889A9-3A33-E511-8D88-20CF3027A575.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/BE61AB61-BC34-E511-8759-002618943870.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/D29C0D3F-2F33-E511-82EA-001E675A58D9.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/F2638005-4633-E511-A51F-02163E0167CA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/1EB25BAC-9E33-E511-93C3-001E673969FF.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/86B59D52-B433-E511-8D2A-001E67396581.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/D89209F5-FE32-E511-8B24-001E67A4061D.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/80000/EAD7E766-3A32-E511-A0D9-0025905C3DCE.root' ] );


secFiles.extend( [
               ] )

