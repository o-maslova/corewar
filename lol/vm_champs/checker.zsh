#!/bin/bash

# That file needs to be launched in corewar/vm/vm_champs folder

i=$RANDOM
PREFIX="/tmp/"
ORIG_LOG=${PREFIX}log_${i}
OURS_LOG=${PREFIX}log__${i}
DIFF=${PREFIX}diff_${i}

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[1;34m'
RESET='\033[0m'

make -C ..
echo -n > $ORIG_LOG; echo -n > $OURS_LOG; echo -n > $DIFF
rm -f log1 log diff
ln -s $ORIG_LOG log1
ln -s $OURS_LOG log
ln -s $DIFF diff
./corewar $* > $ORIG_LOG &
../corewar $* > $OURS_LOG &
while [[ $(pgrep corewar) ]];
do
	echo -n "Waiting... for "
	echo -n $(pgrep corewar | wc -l)
	echo " proccesses"
	sleep 5
done
diff $ORIG_LOG $OURS_LOG > $DIFF
numdiffs=$(wc -l < $DIFF)
if [[ $numdiffs -gt 0 ]];
then
	printf $RED
else
	printf $GREEN
fi
echo "Number of diffs: $numdiffs"
printf $BLUE
echo "Diff string: diff $ORIG_LOG $OURS_LOG > $DIFF"
printf $RESET
if [[ $(head $DIFF) ]];
then
	sleep 3
	less $DIFF
else
	rm -f $ORIG_LOG $OURS_LOG $DIFF
fi
