import FWCore.ParameterSet.Config as cms

puppiTau21 = "userFloat('ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau2')\
             /userFloat('ak8PFJetsPuppiValueMap:NjettinessAK8PuppiTau1')\
             <0.75" 

corrJetsProducer = cms.EDProducer ( "CorrJetsProducer",
                                    jets    = cms.InputTag( "cleanPatJets"             ),
                                    vertex  = cms.InputTag( "goodOfflinePrimaryVertex" ), 
                                    rho     = cms.InputTag( "fixedGridRhoFastjetAll"   ),
                                    payload = cms.string  ( "AK8PFchs"                 ),
                                    isData  = cms.bool    (  False                     ))

nsubjettiness = cms.EDFilter(      "CandViewSelector",
                                    src = cms.InputTag("corrJetsProducer:corrJets"),
                                    cut = cms.string(puppiTau21),
                                    filter = cms.bool(True) )

hadronicV = cms.EDFilter(          "CandViewSelector",
                                    src = cms.InputTag("nsubjettiness"),
                                    cut = cms.string('pt>200. & abs(eta)<2.4 & \
                                                      userFloat("ak8PFJetsCorrPuppiSoftDropMass")>20. & \
                                                      userFloat("ak8PFJetsCorrPuppiSoftDropMass")<220.'),
                                    filter = cms.bool(True) )

hadronicVSequence = cms.Sequence(   corrJetsProducer +
                                    nsubjettiness    +
                                    hadronicV        )
