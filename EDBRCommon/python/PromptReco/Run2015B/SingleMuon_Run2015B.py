import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/162/00000/160C08A3-4227-E511-B829-02163E01259F.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/164/00000/544E58CD-A226-E511-834E-02163E0134D6.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/167/00000/EE9594B8-A826-E511-A18B-02163E011A7D.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/168/00000/4E8E390B-EA26-E511-9EDA-02163E013567.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/168/00000/60FF8405-EA26-E511-A892-02163E01387D.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/244/00000/68275270-7C27-E511-B1F0-02163E011A46.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/244/00000/B6304C6F-7C27-E511-9C77-02163E01250E.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/251/00000/EEBF2AF4-8D27-E511-91F7-02163E014527.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/252/00000/0438FA5A-A127-E511-BA6F-02163E013414.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/252/00000/7E4A8F57-A127-E511-9BF5-02163E014629.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/493/00000/6A4D2AB2-E828-E511-B82B-02163E0121E9.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/496/00000/680026A4-AF2C-E511-9CDB-02163E013515.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/496/00000/9092B59B-AF2C-E511-8CC3-02163E011D30.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/496/00000/CA1D329B-AF2C-E511-B923-02163E01360C.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/497/00000/668C5130-FE28-E511-8F78-02163E0133B0.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/498/00000/50CD6709-0C29-E511-8F8B-02163E0134FD.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/499/00000/402D1C6D-1729-E511-ABF5-02163E011DFF.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/500/00000/62310AED-3729-E511-AC61-02163E012712.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/500/00000/A2A303EC-3729-E511-9ECE-02163E011A29.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/521/00000/425B1189-6729-E511-AF38-02163E013728.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/522/00000/F6930521-5D29-E511-B517-02163E011D37.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/548/00000/44CE0650-EF29-E511-BA0D-02163E012601.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/559/00000/3C6564E0-A62C-E511-A11A-02163E012603.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/560/00000/A886DB09-E029-E511-8A06-02163E0125C8.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/561/00000/F6A7CE0F-132A-E511-A423-02163E011D88.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/7CC342FD-A02A-E511-BE8D-02163E01182A.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/96297F29-862A-E511-85C1-02163E013901.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/C6637305-A12A-E511-AD71-02163E0138F6.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/E0561625-7C2A-E511-9016-02163E0133D1.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/562/00000/EA8BA8F7-A02A-E511-A45F-02163E013473.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/604/00000/1606A3BF-972A-E511-86A7-02163E013515.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/612/00000/7A0CE8FF-A72A-E511-B7DC-02163E011D1C.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/638/00000/10C07DF0-FA2A-E511-846A-02163E01474A.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/642/00000/D20F8A8A-DE2A-E511-9D16-02163E0133FF.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/643/00000/1E72D617-BE2C-E511-96A0-02163E0139A2.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/643/00000/3C563818-BE2C-E511-993B-02163E0144D6.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/643/00000/C061E81E-BE2C-E511-AA5F-02163E01208E.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/643/00000/C6F9761A-BE2C-E511-932C-02163E011D30.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/643/00000/CC199B16-BE2C-E511-B1A5-02163E012B30.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/643/00000/D4FE721A-BE2C-E511-856B-02163E01250C.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/721/00000/30BD3F39-542C-E511-A5DA-02163E011DA4.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/721/00000/329A9A3B-542C-E511-B6B8-02163E01360E.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/781/00000/CE3105FD-A82C-E511-B330-02163E011955.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/883/00000/089D049E-262D-E511-85A7-02163E0146EB.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/883/00000/62919ECB-1F2D-E511-B387-02163E013796.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/883/00000/E2546D9E-492D-E511-9977-02163E011D46.root',
       '/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/251/883/00000/E49261AB-492D-E511-9FCA-02163E011E24.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/116/00000/7E03BD9B-7730-E511-BA13-02163E011976.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/201D1572-EB31-E511-852A-02163E01340A.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/2471A7F2-6C31-E511-A71B-02163E0133F0.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/58D01EE9-6B31-E511-852A-02163E0139B0.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/647C27E8-E231-E511-A3D9-02163E012704.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/9E0526D6-F131-E511-94B7-02163E01428F.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/A0BF6FF9-8231-E511-AD78-02163E0133AD.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/BA9B25ED-E231-E511-976A-02163E01340A.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/BE4EB725-7131-E511-84DD-02163E0139B0.root',
       #'/store/data/Run2015B/SingleMuon/MINIAOD/PromptReco-v1/000/252/126/00000/DAF3D992-ED31-E511-812B-02163E014181.root' 
       ] );


secFiles.extend( [
               ] )

