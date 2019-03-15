CHFOLDER="."
champs=$(ls -R $CHFOLDER | grep -E "(/|.*\.s$)" | sed -e ':a' -e 'N' -e '$!ba' -e "s/\.s//g")

j=0;
for champ in $champs; do
	if [[ $(echo $champ | grep ":$") ]]; then
		path=$(echo $champ | sed -e "s|:|/|g")
	else
		if [[ ! $(./asm "${path}$champ.s" | grep error) ]]; then
			found[$j]="${path}$champ.cor"
			let j++
		fi
	fi
done

cn=${#found[@]}
NEEDED_CHAMP_NUM=$(($1))
if [[ $NEEDED_CHAMP_NUM == 0 || $NEEDED_CHAMP_NUM > 4 ]]; then
	NEEDED_CHAMP_NUM=4
fi

for (( i=0; i<$NEEDED_CHAMP_NUM; i++)); do
	chosen[$i]="${found[$(($RANDOM%cn))]}";
done

# echo "-Found Champs--------------------------------------------------------"
# echo ${found[@]}
# echo "-Chosen Champs-------------------------------------------------------"
# echo ${chosen[@]}
# echo "---------------------------------------------------------------------"

./mass_checker.zsh ${chosen[@]}
