#!/usr/bin/python 
import os,sys,time


## User Environment Variables

USER = os.environ['USER']
SKFlatLogEmail = os.environ['SKFlatLogEmail']
SKFlatLogWeb = os.environ['SKFlatLogWeb']
SKFlatLogWebDir = os.environ['SKFlatLogWebDir']
SKFlat_WD = os.environ['SKFlat_WD']
SKFlatV = os.environ['SKFlatV']
SKFlatRunlogDir = os.environ['SKFlatRunlogDir']
SKFlatOutputDir = os.environ['SKFlatOutputDir']
SKFlatSEDir = os.environ['SKFlatSEDir']
SKFlat_LIB_PATH = os.environ['SKFlat_LIB_PATH']
UID = str(os.getuid())

# Machine Environment

HOSTNAME = os.environ['HOSTNAME']
IsKISTI = ("sdfarm.kr" in HOSTNAME)
IsUI10 = ("ui10.sdfarm.kr" in HOSTNAME)
IsUI20 = ("ui20.sdfarm.kr" in HOSTNAME)
IsKNU = ("knu" in HOSTNAME)
IsTAMSA2 = ("tamsa2" in HOSTNAME)
IsTAMSA1 = ("cms.snu" in HOSTNAME)
IsSNU = IsTAMSA1 or IsTAMSA2


if IsKISTI:
  HostNickName = "KISTI"
#if IsSNU:
#  HostNickName = "SNU"
if IsTAMSA2:
  HostNickName = "TAMSA2"
if IsTAMSA1:
  HostNickName = "TAMSA1"
if IsKNU:
  HostNickName = "KNU"
