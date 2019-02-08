if [[ $HOSTNAME == *"cms.snu.ac.kr"* ]]; then
  qstat -u "*"
elif [[ $HOSTNAME == *"cms.snu.ac.kr"* ]]; then
  qstat
else
  echo "Not prepared at " $HOSTNAME
fi
  

