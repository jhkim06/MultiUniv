import os
import argparse
import collections


#masses = ['090']
masses = ['090','100','110','120','130','140','150']
#mass_points = [("CH090",90),("CH100",100),("CH110",110),("CH120",120),("CH130",130),("CH140",140),("CH150",150)]
cuts_2b =[0.00] #[0.00,0.35,0.55]
cuts_3b =[0.00] #[0.00,0.2,0.30,0.40,0.50,0.60]

#dirBase = '/data6/Users/salee/CMS/MultiUniv/PlotConfiguration/CHToCBcontrol/'
dirBase = '/data6/Users/bhoh/MultiUniv/MultiUniv/PlotConfiguration/CHToCBcontrol/'
variableName = ['fitted_dijet_M090to110','fitted_dijet_M120to150']
#variableName = ['initial_dijet_M090to110','initial_dijet_M120to150']


class LimitCalc():

    def __init__(self,StatOnly, Ch, Cut, Year, Method, Run):
        if StatOnly==True:
            self.StatOnlyLabel = "stat_only"
	    self.StatOnly = '-S 0'
        elif StatOnly==False:
            self.StatOnlyLabel = ""
	    self.StatOnly = ''
        else:
            raise RuntimeError("no such args: %s"%StatOnly)

	if Ch == "All":
	  self.Ch = ['Mu', 'El']
	elif Ch in ['Mu','El']:
	  self.Ch = [Ch]
	else:
	  print 'There is no channel like',Ch, 'Exiting....'
	  exit()

        if Year == "All":
	  self.Year = ['2016','2017','2018']
	elif Year in ['2016','2017','2018']:
          self.Year	= [Year]
	else:
	  print 'there is no year like',Year,'Exiting....'
	  exit()

	if Cut == 'All':
	  #self.Cuts = ['4j5j2b','4j5j3b']
	  #self.Cuts = ['4j5j2b','6j2b','4j5j3b','6j3b']
	  self.Cuts = ['2b','3b']
	elif Cut in ['2b','3b']:
	#elif Cut in ['4j5j2b','6j2b','4j5j3b','6j3b']:
	  self.Cuts = [Cut]
	else:
	  print 'there is no cut like',Cut,'Exiting...'
	  exit()

	if Run !='':
	  self.Run = '--run '+Run
	  self.RunLabel = Run
	else:
	  self.Run =''
	  self.RunLabel = ''
	
	self.Method = Method

	self.combinedCards = []
	self.workspaceFile = []


	print 'Configuration for Combination ========================='
	print 'Stat only'.ljust(20),	self.StatOnlyLabel
	print 'Channel'.ljust(20),	self.Ch
	print 'Year'.ljust(20),		self.Year
	print 'Cuts'.ljust(20),		self.Cuts
	print 'Run'.ljust(20),		self.Run
	print 'Method'.ljust(20),	self.Method

    def CombineCards(self, doRun=False):
        if not os.path.isdir('combinedCards'):
	  os.mkdir('combinedCards')
        for mass in masses:
          cards = collections.OrderedDict()
          combName='combinedCards/M' + mass
	  for year in self.Year:
	    combName = combName + 'Y'+year
	    for ch in self.Ch:
	      combName += ch
	      for cut in self.Cuts:
		combName += cut
		processName = 'M'+mass+'_'+ch+'_'+cut
		if mass < "120":
		  tmp_variableName = variableName[0]
		else:
		  tmp_variableName = variableName[1]
	        cardName= dirBase+year+'/DataCard_CHToCB_'+ch+'_Combi_M'+mass+'/'+ch+cut+'/'+tmp_variableName+'/datacard.txt'
		#print processName
		#print cardName

		cards[processName]=cardName
	  cmd = 'combineCards.py '
	  for process in cards:
	    #print process, cards[process]
	    cmd = cmd + ' ' + process + '=' + cards[process]
	  cmd += ' > ' + combName + '.txt'
	  if doRun:
	    print 'cmd', cmd
            os.system(cmd)
	  else:
	    print 'cmd', cmd
	    
	  self.combinedCards.append(combName+'.txt')
                    

    def Text_to_Workspace(self, doRun=False):
      if not os.path.isdir('workspace'):
	os.mkdir('workspace')

      for card in self.combinedCards:
	for mass in masses:
	  if 'M'+mass in card:
	    massf = float(mass)
	    print 'making workspace for',card,'mass', massf
        #example:
        #text2workspace.py CHToCB_datacard_CH090_0.35_0.40.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggsCB -o ../workspace/mu_90_0.35_0.40_stat.root -m 90
            command_template = "text2workspace.py %s -P %s -o %s -m %i"
            arg1 = card
            arg2 = "HiggsAnalysis.CombinedLimit.ChargedHiggsCB:brChargedHiggsCB"
            arg3 = 'workspace/' + card.split('combinedCards/')[-1] + '.root'
            arg4 = massf
            command = command_template%(arg1,arg2,arg3,arg4)
	    #### scaling constraint
	    #command += " --X-rescale-nuisance 'CMS*' 0.5"
	    self.workspaceFile.append(arg3)
	    if doRun:
              os.system(command)
	    else:
              print 'cmd',command


    def Combine(self,doRun=False):
        if not os.path.isdir('combine'):
	  os.mkdir('combine')
        #example:
        #combine ../workspace/mu_90_0.35_0.40_stat.root -M AsymptoticLimits  --cminDefaultMinimizerType Minuit2 --rAbsAcc 0.000001 --mass 90 --name CHlimit_mu_90_0.35_0.40 | tee res_mu_90_0.35_0.40_stat.out
        command_template = "combine %s --mass %d --name %s "
        #FIXME
        #command_template = "combine harvest install %s --mass %d --name %s "
        for workspace in self.workspaceFile:
	  for mass in masses:
	    if 'M'+mass in workspace:
	      print workspace
              arg1 = workspace
              arg2 = float(mass)
	      name = workspace.split('/')[1]
	      print name
	      name = name.split('.txt.root')[0]
	      print name
	      arg3 =name
	      if self.StatOnly != '':
                arg3 += '_' + self.StatOnlyLabel
	      if self.RunLabel != '':
		arg3 += '_' + self.RunLabel
              command = command_template%(arg1,arg2,arg3)
	      #########
              #options = "-M FitDiagnostics --plots --saveShapes"
              #options = "-M FitDiagnostics --plots --saveShapes --saveWithUncertainties"
	      #options += " -t -1 --expectSignal 0"
	      #--cminDefaultMinimizerTolerance arg (=0.10000000000000001)
	      #options += " --stepSize 0.01 --maxFailedSteps 10"
	      #options += " --cminDefaultMinimizerTolerance 0.1"
	      #options += " --robustHesse 1"
	      #options += " --cminPreScan --cminPreFit 1"
	      #options += " --keepFailures --saveNLL" 
	      #options += " --preFitValue 0"
	      #options += " --cminPreScan --cminSingleNuisFit "
              #options = "-M FitDiagnostics --expectSignal 0 --stepSize 0 --plots --saveShapes"
	      #########
	      #options = "-M ChannelCompatibilityCheck"
	      #########
              options = '-M '+self.Method
	      options +=' --rAbsAcc 0 --rRelAcc 0.000000001'
	      #options += ' -t 500  '
	      #options += ' --toysFrequentist'
	      #########
	      #options = "-M MultiDimFit --robustFit=1 "
	      #########
              command += options
	      #command += ' '+self.Run
	      #command += ' '+self.StatOnly
              pipe_line = "| tee combine/res_%s.out"%(name)
              command += pipe_line
	      if doRun:
                os.system(command)
	      else:
                print(command)
	      
	      print arg3
		#higgsCombineM090Y2017Mu2b3bEl2b3b.AsymptoticLimits.mH90.root
	      rootFileName = 'higgsCombine'+arg3+'.AsymptoticLimits.mH'+str(arg2).split('.0')[0] + str(arg2).split('.0')[1]+'.root'
	      print rootFileName
	      os.system('mv '+rootFileName +' combine/')
        #os.system("mv higgsCombineCHlimit_%s_*.root output_root"%self.ch)

    def Tail(self):
        for mass_point in mass_points:
            for cut_2b in cuts_2b:
                for cut_3b in cuts_3b:
                    if cut_2b == 0.00 or cut_3b ==0.00:
                        if cut_2b != cut_3b:
                            continue
                    #example:
                    #tail res_mu_90_0.35_0.40_stat.out | sed -e '9,10d' | awk {'print $5'} > dummy ; sed '3i CLs' dummy > mu_90_0.35_0.40_stat.out
                    command = "tail combine/res_%s_%d_%.2f_%.2f_%s.out | sed -e '9,10d' | "%(self.ch,mass_point[1],cut_2b,cut_3b,self.suffix)
                    command += "awk {'print $5'} > combine/dummy ; "
                    command += "sed '3i CLs' combine/dummy > combine/%s_%d_%.2f_%.2f_%s.out"%(self.ch,mass_point[1],cut_2b,cut_3b,self.suffix)
                    #print(command)
                    os.system(command)
        os.system("rm combine/dummy")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='TrueOrNotTrue')
    parser.add_argument('-StatOnly',help="False or True", default=False, type=bool)
    parser.add_argument('-Ch',help="Mu of El", default='All')
    parser.add_argument('-Cuts',help="Cuts", default='All')
    parser.add_argument('-Year',help="Which year to use", default='All')
    parser.add_argument('-M',help="Method to use", default='AsymptoticLimits')
    parser.add_argument('-run',help="blind?", default='')

    args = parser.parse_args()
    StatOnly=args.StatOnly
    Ch=args.Ch
    Cuts=args.Cuts
    Year=args.Year
    Method=args.M
    Run=args.run

    print 'Set up parameters =========================================='
    print 'StatOnly:'.ljust(20),StatOnly
    print 'Lepton Flavor:'.ljust(20),Ch
    print 'Year:'.ljust(20),Year
    print 'Method:'.ljust(20),Method
    print 'Run:'.ljust(20),Run

    s = LimitCalc(StatOnly,Ch,Cuts,Year,Method,Run)
    s.CombineCards(True)
    s.Text_to_Workspace(True)
    s.Combine(True)
    #    s.Tail()
