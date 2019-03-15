#!/bin/bash

# That file needs to be launched in corewar/vm/vm_champs folder
# Usage: ./mass_checker.zsh <couple of bots.cor to test vms>
# ./mass_checker.sh champs/Car.cor champs/Gagnant.cor champs/Octobre_Rouge_V4.2.cor
# for logs check folder $PREFIX(default: /tmp)

ARGS=($*)
if [[ ${#ARGS[@]} -eq 0 ]]; then
	echo "That file needs to be launched in corewar/vm/vm_champs folder"
	echo "Usage: ./mass_checker.zsh <couple of bots.cor to test vms>"
	echo "./mass_checker.sh champs/Car.cor champs/Gagnant.cor champs/Octobre_Rouge_V4.2.cor"
	echo "for logs check folder \$PREFIX(default: /tmp)"
	exit 1
fi
ARG_NUM=4
PREFIX="/tmp/"
TO_DO="to_do.sh"
ERR_D="${PREFIX}/errors/"; mkdir -p $ERR_D
ERRORS=$ERR_D"err_list"
ERRNUM=$(ls -1r $ERR_D | grep diff_ | head -1); ERRNUM=$(($ERRNUM+0))
ERR_F="errors_$RANDOM"

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[1;34m'
RESET='\033[0m'

j=1
fact=1
for i in $*;
do
	let fact*=$j
	let j++
done
let fact*=2
echo "Start testing $fact combinations of this bots: $*"

make -C ..
rm -f ${PREFIX}diff_* ${PREFIX}log_* $TO_DO
echo -n > $TO_DO
# let fact=6
for i in `seq 1 $fact`;
do
	let j=$RANDOM%$ARG_NUM

	let i=$ARG_NUM-1
	VMAV=""
	for l in `seq 0 $i`;
	do
		let k=($j+$l)%$ARG_NUM
		VMAV="$VMAV ${ARGS[$k]}"
	done

	let i=$RANDOM
	ORIG_LOG=${PREFIX}log_$i
	OURS_LOG=${PREFIX}log__$i
	DIFF=${PREFIX}diff_$i
	while [[ $(grep -E "$ORIG_LOG|$OURS_LOG|$DIFF" $TO_DO) ]];
	do
		echo BAD RANDOM $i
		let i=$RANDOM
		ORIG_LOG=${PREFIX}log_$i
		OURS_LOG=${PREFIX}log__$i
		DIFF=${PREFIX}diff_$i
	done
	echo -n > $DIFF; echo -n > $ORIG_LOG; echo -n > $OURS_LOG
	./corewar -d 15000 $VMAV > $ORIG_LOG &
	../corewar -d 15000 $VMAV > $OURS_LOG 2>> $ERR_F &
	if [[ $(cat $ERR_F) ]]; then
		printf $RED; cat $ERR_F; printf $RESET
		rm -f $ERR_F; exit 1
	fi
	echo "diff $ORIG_LOG $OURS_LOG > $DIFF" >> $TO_DO
	echo "# $VMAV" >> $TO_DO
	sleep 1
done
rm -f $ERR_F

while [[ $(pgrep corewar) ]];
do
	echo -n "Waiting... for "
	echo -n $(pgrep corewar | wc -l)
	echo " proccesses"
	sleep 5
done
chmod 744 $TO_DO
./$TO_DO

let j=ERRNUM
for i in $(ls -1 ${PREFIX} | grep diff_)
do
	is_err=$(wc -l < ${PREFIX}$i)
	if [[ $(($is_err+0)) != 0 ]];
	then
		if [[ $ERRNUM == $j ]];
		then
			echo > $ERRORS
		fi
		rand=$(echo $i | cut -d'_' -f 2)
		mv ${PREFIX}diff_$rand $ERR_D
		mv ${PREFIX}log_$rand $ERR_D
		mv ${PREFIX}log__$rand $ERR_D
		grep -A 1 $i $TO_DO >> $ERRORS
		let j++
	fi
done
rm -f $TO_DO

if [[ $(($j-$ERRNUM)) -gt 0 ]];
then
	printf $RED
else
	printf $GREEN
fi
echo "Number of wrong player combinations: $(($j-$ERRNUM))"
printf $BLUE
echo "Wrong player combinations placed with love in $ERRORS"
echo "All logs you can find in ${ERR_D}"
printf $RESET
if [[ $ERRNUM -lt $j ]];
then
	sleep 3
	less $ERRORS
fi
rm -rf ${PREFIX}diff_* ${PREFIX}log_*
