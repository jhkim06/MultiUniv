from ROOT import TFile, TH1, TH1F, TMVA, Double

base_dir    = "out_root_2017/"
method_list = ['BDT_400_MinNodeSize1of10'] #currently only support single method
sample_list = [
  'TTLJ_powheg_4j5j_2b',
  'TTLJ_powheg_4j5j_3b',
  'TTLJ_powheg_6j_2b',
  'TTLJ_powheg_6j_3b',
  'CHToCB_M090to110_4j5j_2b',
  'CHToCB_M090to110_4j5j_3b',
  'CHToCB_M090to110_6j_2b',
  'CHToCB_M090to110_6j_3b',
  'CHToCB_M120to150_4j5j_2b',
  'CHToCB_M120to150_4j5j_3b',
  'CHToCB_M120to150_6j_2b',
  'CHToCB_M120to150_6j_3b',
]
#
ref_effB_list       = [0.1,0.2,0.3,0.4,0.5]
#
out_effS_dict       = {}
out_effS_dict_train = {}
out_AUC_dict        = {}
out_AUC_dict_train  = {}
out_cuts_dict       = {}
out_cuts_dict_train = {}
out_key_list        = []
#
out_text_name = 'out_ROCCalc.txt'
#
def GetXforYof(hist_, ref_y):
  hist_points=[]
  for ibin in range(hist_.GetNbinsX()):
    xval      = hist_.GetXaxis().GetBinCenter(ibin)
    yval      = hist_.GetBinContent(ibin)
    yval_diff = abs(yval - ref_y)
    hist_points.append((xval,yval,yval_diff))
  #assume that histo bin size > 2
  hist_points.sort(key=lambda x:x[2],reverse=False)
  out_x = hist_points[0][0]
  return out_x

def GetROCIntegral(hist_effS, hist_effB):
  effS_points=[]
  effB_points=[]
  if hist_effS.GetNbinsX() != hist_effB.GetNbinsX():
    print("WARNING: bin size of hist_effS and hist_effB not same!!!")
  for ibin in range(hist_effS.GetNbinsX(),0,-1):
    effS_points.append(hist_effS.GetBinContent(ibin))
    effB_points.append(1-hist_effB.GetBinContent(ibin))
  prev_x = 0.
  prev_y = 1.
  integral =0.
  #print(effS_points)
  #print(effB_points)
  for x,y in zip(effS_points,effB_points):
    diff_x = x - prev_x
    avg_y = (y + prev_y)/2.
    integral += diff_x*avg_y
    prev_x = x; prev_y = y
  return integral
    
#
for sample_ in sample_list:
  for method_ in method_list:
    tfile      = TFile(base_dir +'out_train_%s.root'%sample_,"READ")
    effS       = tfile.Get('TMVAClassification/Method_%s/%s/MVA_%s_effS'%(method_,method_,method_))
    effB       = tfile.Get('TMVAClassification/Method_%s/%s/MVA_%s_effB'%(method_,method_,method_))
    Train_effS = tfile.Get('TMVAClassification/Method_%s/%s/MVA_%s_trainingEffS'%(method_,method_,method_))
    Train_effB = tfile.Get('TMVAClassification/Method_%s/%s/MVA_%s_trainingEffB'%(method_,method_,method_))

    #
    out_effS_list = []
    out_effS_list_train = []
    out_cut_list = []
    out_cut_list_train = []
    for ref_effB in ref_effB_list:
      #
      cut = GetXforYof(effB,ref_effB)
      cut_train = GetXforYof(Train_effB,ref_effB)
      out_cut_list.append(cut)
      out_cut_list_train.append(cut_train)
      #
      out_effS       = effS.GetBinContent( effS.FindBin(cut) )
      out_effS_train = Train_effS.GetBinContent( Train_effS.FindBin(cut_train) )
      out_effS_list.append(out_effS)
      out_effS_list_train.append(out_effS_train)


    key = "%s_%s"%(method_,sample_)
    out_key_list.append(key)
    out_effS_dict[key] = out_effS_list
    out_effS_dict_train[key] = out_effS_list_train
    #
    out_cuts_dict[key] = out_cut_list
    out_cuts_dict_train[key] = out_cut_list_train

    # calc AUC
    out_AUC       = GetROCIntegral(effS,effB)
    out_AUC_train = GetROCIntegral(Train_effS,Train_effB)
    out_AUC_dict[key] = out_AUC
    out_AUC_dict_train[key] = out_AUC_train

#TODO save to text file
with open(out_text_name,'w') as f:
  f.write("ref_effB_list="+str(ref_effB_list))
  f.write("\n\n")
  f.write("out_effS_dict="+str(out_effS_dict))
  f.write("\n\n")
  f.write("out_effS_dict_train"+str(out_effS_dict_train))
  f.write("\n\n")
  f.write("out_cuts_dict"+str(out_cuts_dict))
  f.write("\n\n")
  f.write("out_cuts_dict_train"+str(out_cuts_dict_train))
  f.write("\n\n")
  f.write("out_AUC_dict"+str(out_AUC_dict))
  f.write("\n\n")
  f.write("out_AUC_dict_train"+str(out_AUC_dict_train))
  f.write("\n\n")
  f.close()

