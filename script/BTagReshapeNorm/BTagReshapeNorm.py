import ROOT
import os

# first run "hadd -T " commend for TTLJ_powheg
# get histograms
# estimate normalization by jet multiplicity and systematic flags

base_dir = "/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190417_161108" #TTLJ_powheg folder dir
hadd_file_name = "TTLJ_powheg.root"
out_file_name = "BTag_Reshape_Norm.root" # .root file name containing normalization

#base_dir = "/data8/DATA/SMP/Run2Legacy_v3/2017/MetFt_L_v2_TTSemiLep_v1/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/190417_160732"
#hadd_file_name = "TTLL_powheg.root"
#out_file_name = "BTag_Reshape_Norm_TTLL_powheg.root" # .root file name containing normalization


syst_bins = ["",
             "up_lfstats1", "down_lfstats1",
             "up_lfstats2", "down_lfstats2",
	     "up_lf", "down_lf",      
             "up_hf", "down_hf",      
             "up_jes", "down_jes",     
             "up_hfstats1", "down_hfstats1",
             "up_hfstats2", "down_hfstats2",
             "up_cferr1", "down_cferr1",  
             "up_cferr2", "down_cferr2"  
            ]

nhf5_bins = ["nhf5eq0","nhf5eq1","nhf5eq2","nhf5eq3","nhf5geq4"]

def doHadd(base_dir, hadd_file_name):
  cmd = "hadd -T %s %s/*/*.root"%(hadd_file_name, base_dir)
  os.system(cmd)

def mkNorm(tfile,syst,nhf5):
  before_btagW = "n_entry_before_BTagSF" # hist name
  after_btagW = "n_entry_after_BTagSF"  # hist name
  out_hist_name = "btagW_norm"
  if not syst =="":
    after_btagW += "_%s"%syst
    out_hist_name += "_%s"%syst
  before_btagW += "_%s"%nhf5
  after_btagW += "_%s"%nhf5
  out_hist_name += "_%s"%nhf5

  h_before_btagW = tfile.Get(before_btagW)
  h_after_btagW  = tfile.Get(after_btagW)

  h_out = h_before_btagW.Clone(out_hist_name)
  h_out.Divide(h_after_btagW)
  #for i in range(1,1,8):
  #  content_before = h_out.GetBinContent(i)
  #  content_after = h_after_btagW.GetBinContent(i)
  #  ratio = content_before/content_after if not content_after==0 else 0
  #  h_out.SetBinContent(i, ratio)

  return h_out

def printCut(f_out):
  nhf5_bins = ["nhf5eq0","nhf5eq1","nhf5eq2","nhf5eq3","nhf5geq4"]
  nhf5_cut  = ["nhf5==0","nhf5==1","nhf5==2","nhf5==3","nhf5>=4"]
  nhf0_cut  = ["nhf0==0","nhf0==1","nhf0==2","nhf0==3","nhf0==4","nhf0==5","nhf0==6","nhf0==7","nhf0==8","nhf0==9","nhf0>9"]
  out = "*("
  for i, nhf5 in enumerate(nhf5_bins):
    hist_name = "btagW_norm_%s"%nhf5
    h = f_out.Get(hist_name)
    sub_out = " (%s)*(" % nhf5_cut[i]
    for j, nhf0 in enumerate(nhf0_cut):
      sub_out += " (%s)*%f"%(nhf0,h.GetBinContent(j+1))
      if not j == len(nhf0_cut)-1:
        sub_out += " +"
    sub_out +=" )"
    out += sub_out
    if not i == len(nhf5_cut)-1:
      out += " +"
  out +=" )"
  print(out)



doHadd(base_dir, hadd_file_name)

f_in  = ROOT.TFile(hadd_file_name,"READ")
f_out = ROOT.TFile(out_file_name,"RECREATE")
f_out.cd()

for syst in syst_bins:
  for nhf5 in nhf5_bins:
    h_out = mkNorm(f_in, syst, nhf5)
    h_out.Write()
printCut(f_out)
f_out.Close()
