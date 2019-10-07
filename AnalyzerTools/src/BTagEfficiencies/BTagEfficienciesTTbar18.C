/* These Efficiencies have been derived for Summer15ttbar events and should 
   be used only for the same MC samples or for events with similar topology */  



//################################### FIXME add other TaggerOP

float BTagSFUtil::TagEfficiencyB_2018(float JetPt, float JetEta) {
  
if (TaggerOP=="DeepCSV_Medium") { 
  if (JetPt > 20.00000 && JetPt <= 30.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.64949;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.64918;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.59131;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.52667;  
  } 
  else if (JetPt > 30.00000 && JetPt <= 50.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.73836;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.73653;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.69001;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.65228;  
  } 
  else if (JetPt > 50.00000 && JetPt <= 70.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.77629;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.77270;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.72589;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.69215;  
  } 
  else if (JetPt > 70.00000 && JetPt <= 100.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.79322;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.78733;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.73593;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.69443;  
  } 
  else if (JetPt > 100.00000 && JetPt <= 140.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.79986;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.79053;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.73134;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.68097;  
  } 
  else if (JetPt > 140.00000 && JetPt <= 200.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.79353;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.77873;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.71106;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.64700;  
  } 
  else if (JetPt > 200.00000 && JetPt <= 300.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.75467;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.73097;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.65243;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.57606;  
  } 
  else if (JetPt > 300.00000 && JetPt <= 600.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.65732;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.62851;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.55300;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.48557;  
  } 
  else if (JetPt > 600.00000 && JetPt <= 1000.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.46853;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.44386;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.37026;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.36300;  
  }
}

  return 1.;
}




float BTagSFUtil::TagEfficiencyC_2018(float JetPt, float JetEta) {
  
if (TaggerOP=="DeepCSV_Medium") { 
  if (JetPt > 20.00000 && JetPt <= 30.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.13494;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14406;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.13148;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.11773;  
  } 
  else if (JetPt > 30.00000 && JetPt <= 50.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.12919;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14210;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.14177;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14387;  
  } 
  else if (JetPt > 50.00000 && JetPt <= 70.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.12814;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14045;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.14088;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14521;  
  } 
  else if (JetPt > 70.00000 && JetPt <= 100.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.13721;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.14804;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.14508;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14677;  
  } 
  else if (JetPt > 100.00000 && JetPt <= 140.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.14957;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.15720;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.15022;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14960;  
  } 
  else if (JetPt > 140.00000 && JetPt <= 200.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.15991;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.16346;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.15315;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.14765;  
  } 
  else if (JetPt > 200.00000 && JetPt <= 300.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.15807;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.15599;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.13968;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.12810;  
  } 
  else if (JetPt > 300.00000 && JetPt <= 600.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.13577;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.12556;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.10894;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.09738;  
  } 
  else if (JetPt > 600.00000 && JetPt <= 1000.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.07618;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.05878;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.06223;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.03927;  
  } 

}

  return 1.;
}


float BTagSFUtil::TagEfficiencyLight_2018(float JetPt, float JetEta) {
  
if (TaggerOP=="DeepCSV_Medium") { 
   if (JetPt > 20.00000 && JetPt <= 30.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00997;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01211;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01377;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01513;  
  } 
  else if (JetPt > 30.00000 && JetPt <= 50.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00794;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01022;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01331;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01858;  
  } 
  else if (JetPt > 50.00000 && JetPt <= 70.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00710;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00921;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01201;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01760;  
  } 
  else if (JetPt > 70.00000 && JetPt <= 100.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00795;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00982;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01234;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01811;  
  } 
  else if (JetPt > 100.00000 && JetPt <= 140.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.00948;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01106;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01341;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.02003;  
  } 
  else if (JetPt > 140.00000 && JetPt <= 200.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.01116;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01222;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01454;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.02168;  
  } 
  else if (JetPt > 200.00000 && JetPt <= 300.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.01235;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01262;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01519;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.02119;  
  } 
  else if (JetPt > 300.00000 && JetPt <= 600.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.01438;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.01343;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01757;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.02097;  
  } 
  else if (JetPt > 600.00000 && JetPt <= 1000.00000){  
    if (fabs(JetEta) > 0.00000 && fabs(JetEta) <= 0.60000) return 0.01199;  
    else if (fabs(JetEta) > 0.60000 && fabs(JetEta) <= 1.20000) return 0.00974;  
    else if (fabs(JetEta) > 1.20000 && fabs(JetEta) <= 1.80000) return 0.01547;  
    else if (fabs(JetEta) > 1.80000 && fabs(JetEta) <= 2.40000) return 0.01611;  
  } 
}

  return 1.;
}
