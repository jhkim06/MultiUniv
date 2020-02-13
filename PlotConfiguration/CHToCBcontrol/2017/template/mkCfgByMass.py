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
  ("090","090to110"),
  ("100","090to110"),
  ("110","090to110"),
  ("120","120to150"),
  ("130","120to150"),
  ("140","120to150"),
  ("150","120to150"),
]

for template in template_list:
  for mass in mass_list:
    with open(template_directory+'/'+template, 'r') as fIn:
      with open(save_directory+'/'+template.replace('_M.txt','_M%s.py'%mass[0]), 'w') as fOut:
        for line in fIn.readlines():
	  if "configuration_" in template or "plot_" in template:
            out = line.replace('<MASS>',mass[0])
	  else:
            out = line.replace('<MASS>',mass[1])
	  fOut.write(out)






