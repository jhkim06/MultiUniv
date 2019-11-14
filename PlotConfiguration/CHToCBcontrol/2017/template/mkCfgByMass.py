#!/usr/bin/env python


template_directory = "."
save_directory = "../"

template_list = [
  "configuration_El_Combi_M.txt",
  "configuration_Mu_Combi_M.txt",
  "plot_El_Combi_M.txt",
  "plot_Mu_Combi_M.txt",
  "variables_Combi_M.txt",
  "nuisances_El_Combi_M.txt",
  "nuisances_Mu_Combi_M.txt"
]

mass_list = [
  "090",
  "100",
  "110",
  "120",
  "130",
  "140",
  "150",
]

for template in template_list:
  for mass in mass_list:
    with open(template_directory+'/'+template, 'r') as fIn:
      with open(save_directory+'/'+template.replace('_M.txt','_M%s.py'%mass), 'w') as fOut:
        for line in fIn.readlines():
          out = line.replace('<MASS>',mass)
	  fOut.write(out)






