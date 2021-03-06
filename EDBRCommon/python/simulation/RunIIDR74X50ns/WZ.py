import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/12C5D08A-D40C-E511-846B-B083FECFD4F0.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/1A2C29E7-560C-E511-90DF-002590E3A222.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/284E8A8C-D40C-E511-83A1-00259073E4CA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/285B623F-600C-E511-9FBF-0002C92DB46C.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/34D4D545-D40C-E511-A087-0025907FD2B6.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/38AEDB61-D40C-E511-890B-008CFA1974D8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/3C774892-600C-E511-BDAD-0002C90F8088.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/466D49FF-560C-E511-B90A-0025901D08BA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/4AF09029-680C-E511-A7CB-002590D9D966.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/4C727A40-D40C-E511-9327-000F530E479C.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/566B6A2F-D40C-E511-A0B5-20CF3027A5B2.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/581024A1-6B0C-E511-B4F1-28924A33B9AA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/5A55F043-7E0C-E511-97D0-001E67396D6F.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/5C251CDC-600C-E511-9A52-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/64AEE48B-D40C-E511-BFC7-0CC47A4DED1A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/6819D938-560C-E511-91A9-0CC47A13CB18.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/6E43059F-5C0C-E511-BC4D-842B2B7609C0.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/728A3A92-D40C-E511-AC3D-00266CFCC160.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/741852F4-610C-E511-929D-0002C92A1020.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/80E9C279-D40C-E511-9EAA-1CC1DE0530F8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/82821C30-D40C-E511-B3A8-001EC9B1D0C4.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/8859A93F-560C-E511-86A2-00238BBD75D8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/90C00DBF-B20C-E511-8A2D-6C3BE5B581A8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/98D2AB8F-D40C-E511-9EC2-00259073E4A0.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/9E4C9C5D-960C-E511-BDEC-02163E00E901.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/AE6725A8-6F0C-E511-A547-90B11C2CC96F.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/B01E3A9D-6B0C-E511-BB54-001EC9ADCB54.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/B4BC7A94-5A0C-E511-BC7F-003048344BF8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/C629ABF7-560C-E511-8E86-002590E2F664.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/CC9689E2-560C-E511-9098-002590E39DF4.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/CE910145-D40C-E511-9634-02163E00E5AB.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/D47D009A-D40C-E511-A156-B083FED42A1A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/D86BBB47-D40C-E511-A356-0CC47A0AD6EA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/E2AACF8F-D40C-E511-B83F-0025907277BE.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/E48D2DB9-630C-E511-A727-A0369F3016EC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/F8D6E181-D40C-E511-B13D-782BCB285E30.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/FA61A03B-D40C-E511-A3CC-0026B927866B.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/FC29D53F-680C-E511-B4B4-008CFA0A5738.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/FCFCE990-D40C-E511-9C9A-0002C94D564A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/FE36650C-700C-E511-9E39-0025907D244A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v2/60000/FE8D750C-680C-E511-80E2-0CC47A0AD630.root' ] );


secFiles.extend( [
               ] )

