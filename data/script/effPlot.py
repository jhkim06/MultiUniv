from CommonPyTools.python.getEvn import *
from CommonPyTools.python.CommonTools import *
from ROOT import *
#import numpy as np

outF = open("muonEff2018_medTrkIsoLoose_v1.txt", "w")
effDir = SKFlat_WD + '/data/Run2Legacy_v3/2018/ID/Muon/'
#effDir = SKFlat_WD + '/data/Run2Legacy_v1/2017/ID/Electron/'
#effDir = SKFlat_WD + '/data/Run2Legacy_v1/2016/ID/Muon/'
#effDir = SKFlat_WD + '/data/Run2Legacy_v1/2017/ID/Muon/'

#     f(0:mu, 1:ele)  s  m  a(0:data, 1MC) b(0.offline, 1leg1,2leg2)   c( 0 for +) d(idx of eta)
#file base
files = [ \
    'IDISO_Minus_2018_medTrkIsoLoose_v1.root' \
    ,'IDISO_Plus_2018_medTrkIsoLoose_v1.root' \
    ,'IsoMu24_Minus_2018_medTrkIsoLoose_v1.root' \
    ,'IsoMu24_Plus_2018_medTrkIsoLoose_v1.root' \
    ,'Mu17_Minus_2018_medTrkIsoLoose_v1.root' \
    ,'Mu17_Plus_2018_medTrkIsoLoose_v1.root' \
    ,'Mu8_Minus_2018_medTrkIsoLoose_v1.root' \
    ,'Mu8_Plus_2018_medTrkIsoLoose_v1.root' \
    ]
# flav 0 for muon 1 for electron
#flav = [1, 1, 1, 1, 1, 1]
flav = [0, 0, 0, 0, 0, 0, 0, 0]
# 0 for off, 1 for single lepton trigger, 2 for double lepton trigger
offLineHLT = [0, 0, 1, 1, 2, 2, 3, 3]
#offLineHLT = [0, 0, 2, 2, 3, 3]
# Q minus 1, plus 0
Qlep = [1, 0, 1, 0, 1, 0, 1, 0]
idxF = 0

# histogram base for each files
effHisto = ['muonEffi_data_eta_pt', 'muonEffi_mc_eta_pt'] 
#effHisto = [ ['EGamma_EffData2D', 'EGamma_EffMC2D'], ['EGamma_EffData2D','EGamma_EffMC2D'], ['EGamma_EffData2D', 'EGamma_EffMC2D'], ['EGamma_EffData2D', 'EGamma_EffMC2D'], ['EGamma_EffData2D', 'EGamma_EffMC2D'], ['EGamma_EffData2D', 'EGamma_EffMC2D'] ]
#effHisto = [ ['muonEffi_data_eta_pt', 'muonEffi_mc_eta_pt'], ['muonEffi_data_eta_pt','muonEffi_mc_eta_pt'], ['muonEffi_data_eta_pt', 'muonEffi_mc_eta_pt'], ['muonEffi_data_eta_pt', 'muonEffi_mc_eta_pt'], ['muonEffi_data_eta_pt', 'muonEffi_mc_eta_pt'], ['muonEffi_data_eta_pt', 'muonEffi_mc_eta_pt'] ]
# data 0, MC 1 for each histo set of each file
dataMC  = [0, 1]
#files = ['2017_IDISO_minus.root']
for idxF in range(len(files) ):
  gROOT.Reset()
  fullPathFile = effDir + '/' + files[idxF]
  #outF.write( files[idxF].replace(".root", "") + '\n' )
  #print fullPathFile
  if not IsThis(fullPathFile):
    print 'exiting....'
    exit()
  inF = TFile( fullPathFile )
  for num_hist in range(len(effHisto)):
  #for num_hist in range(len(effHisto[idxF])):
    #outF.write( effHisto[idxF][num_hist] + '\n')
    histo = inF.Get( effHisto[num_hist] )
    #histo = inF.Get( effHisto[idxF][num_hist] )
    if not histo:
      raise RuntimeError('Unable to retrieve histogram named {0} from {1}'.format(effHisto[num_hist], fullPathFile))
      #raise RuntimeError('Unable to retrieve histogram named {0} from {1}'.format(effHisto[idxF][num_hist], fullPathFile))
    #histo = gROOT.FindObject( effHisto[idxF][num_hist] )
    #histo = gROOT.FindObject( 'SF_eta_pt' )
    nbinEta =  histo.GetNbinsX()
    nbinPt =  histo.GetNbinsY()
    #print 'Nbin Eta', nbinEta
    etaBins = []
    for idx in range(nbinEta):
      bin_num = idx + 1
      #print 'bin', bin_num, histo.GetXaxis().GetBinLowEdge(bin_num), 'to', histo.GetXaxis().GetBinUpEdge(bin_num)
      etaBins.append( histo.GetXaxis().GetBinLowEdge(bin_num) )
      if idx == nbinEta -1:
        etaBins.append( histo.GetXaxis().GetBinUpEdge(bin_num) )
    #print 'Nbin Y', nbinPt
    ptBins = []
    for idx in range(nbinPt):
      bin_num = idx + 1
      #print 'bin', bin_num, histo.GetYaxis().GetBinLowEdge(bin_num), 'to', histo.GetYaxis().GetBinUpEdge(bin_num)
      ptBins.append( histo.GetYaxis().GetBinLowEdge(bin_num) )
      if idx == nbinPt -1:
        ptBins.append( histo.GetYaxis().GetBinUpEdge(bin_num) )

    #print 'Eta binning', etaBins
    #print 'Pt binning', ptBins
    #SF = np.ones( ( nbinEta, nbinPt ) )
    eF = [ [1 for y in range(nbinPt) ] for x in range(nbinEta) ]
    eF_Err = [ [1 for y in range(nbinPt) ] for x in range(nbinEta) ]
    for ix in range(nbinEta) :
      idX = ix + 1
      for iy in range(nbinPt) :
        idY = iy + 1
        eF[ix][iy] = histo.GetBinContent( idX, idY  )
        eF_Err[ix][iy] = histo.GetBinError( idX, idY  )

    # print out
    print 'ETA', nbinEta,(" ".join( map(str,etaBins) ) )
    print 'PT', nbinPt,(" ".join( map(str,ptBins) ) )
    # -1 for not-uniform binning
    outF.write('{0} {1} {2} {3} {4} {5}\n'.format('ETA', flav[idxF], offLineHLT[idxF], nbinEta, "-1", (" ".join( map(str,etaBins) ) ) ) )
    outF.write('{0} {1} {2} {3} {4} {5}\n'.format('PT',  flav[idxF], offLineHLT[idxF], nbinPt,  "-1", (" ".join( map(str,ptBins) ) ) ) )
    #     f(0:mu, 1:ele)  s  m  a(0:data, 1MC) b(0.offline, 1leg1,2leg2)   c( 0 for +) d(idx of eta)
    for ix in range(nbinEta) :
      print flav[idxF], 0, 0, dataMC[num_hist], offLineHLT[idxF], Qlep[idxF] , ix, (" ".join(map(str,eF[ix]))) 
      #print flav[idxF], 0, 0, dataMC[idxF][num_hist], offLineHLT[idxF], Qlep[idxF] , ix, (" ".join(map(str,eF[ix]))) 
      outF.write( '{0} 0 0 {1} {2} {3} {4} {5}\n'.format( flav[idxF], dataMC[num_hist], offLineHLT[idxF], Qlep[idxF], str(ix), (" ".join(map(str,eF[ix]))) )  )
      #outF.write( '{0} 0 0 {1} {2} {3} {4} {5}\n'.format( flav[idxF], dataMC[idxF][num_hist], offLineHLT[idxF], Qlep[idxF], str(ix), (" ".join(map(str,eF[ix]))) )  )
    #  idX = ix + 1
    #  for iy in range(nbinPt) :
    #    idY = iy + 1
    #    print eF[ix][iy]
    #    print eF_Err[ix][iy]
outF.close()
