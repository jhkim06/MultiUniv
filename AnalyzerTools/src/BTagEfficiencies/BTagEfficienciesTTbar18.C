/* These Efficiencies have been derived for Summer15ttbar events and should 
   be used only for the same MC samples or for events with similar topology */  



//################################### FIXME add other TaggerOP

float BTagSFUtil::TagEfficiencyB_2018(float JetPt, float JetEta) {
  
if (TaggerOP=="DeepCSV_Medium") { 
  if (JetPt > 20.00000 && JetPt <= 40.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.68734;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.68587;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.63287;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.58046;  
  } 
  else if (JetPt > 40.00000 && JetPt <= 60.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.75989;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.75706;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.71161;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.67763;  
  } 
  else if (JetPt > 60.00000 && JetPt <= 80.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.78337;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.77868;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.72978;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.69191;  
  } 
  else if (JetPt > 80.00000 && JetPt <= 100.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.79324;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.78694;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.73394;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.68896;  
  } 
  else if (JetPt > 100.00000 && JetPt <= 120.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.79716;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.78863;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.73035;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.68116;  
  } 
  else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.78168;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.76714;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.70184;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.64440;  
  } 
 
}

  return 1.;
}




float BTagSFUtil::TagEfficiencyC_2018(float JetPt, float JetEta) {
  
if (TaggerOP=="DeepCSV_Medium") { 
  if (JetPt > 20.00000 && JetPt <= 40.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.13146;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14239;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.13528;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.12737;  
  } 
  else if (JetPt > 40.00000 && JetPt <= 60.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.12443;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.13692;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.13844;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14334;  
  } 
  else if (JetPt > 60.00000 && JetPt <= 80.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.12917;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14028;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.13987;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14263;  
  } 
  else if (JetPt > 80.00000 && JetPt <= 100.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.13695;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14717;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.14343;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14462;  
  } 
  else if (JetPt > 100.00000 && JetPt <= 120.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.14432;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.15245;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.14661;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14630;  
  } 
  else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.15338;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.15601;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.14556;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14139;  
  } 
 
}

  return 1.;
}


float BTagSFUtil::TagEfficiencyLight_2018(float JetPt, float JetEta) {
  
if (TaggerOP=="DeepCSV_Medium") { 
   if (JetPt > 20.00000 && JetPt <= 40.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00980;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01190;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01385;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01599;  
  } 
  else if (JetPt > 40.00000 && JetPt <= 60.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00673;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00861;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01146;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01671;  
  } 
  else if (JetPt > 60.00000 && JetPt <= 80.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00618;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00783;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01022;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01501;  
  } 
  else if (JetPt > 80.00000 && JetPt <= 100.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00659;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00801;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01022;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01519;  
  } 
  else if (JetPt > 100.00000 && JetPt <= 120.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00714;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00856;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01064;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01611;  
  } 
  else if (JetPt > 120.00000 && JetPt <= 3000.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00914;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00985;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01226;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01830;  
  }  
}

  return 1.;
}
