#! bash

# incrond configuration


if test $# -lt 1
then
	echo "Usage, sh incrond_configuration.sh [ operation[key_install, delete] ]"
	echo "Usage, sudo sh incrond_configuration.sh [ operation[add] ]"
	exit 0
fi

operation=$1
user_account_name=`logname`

if [ "$operation" == "delete" ]
then
	echo "Delete the directories[first word in a sentence is directory], that you don't want to watch and save the file and quit[:wq]"
	read -rsn 1 -p "Press any key to continue..."

	incrontab -e

elif [ "$operation" == "key_install" ] || [ "$operation" == "add" ]
then
	username=""
	ipaddress=""

	choice="replace"

	while [ "$choice" == "replace" ]
	do
		echo -n "Enter the Alternate-node username:"
		read username

		echo -n "Enter the Alternate-node ipaddress:"
		read ipaddress

		choice=""
		echo "Alternate-node username and ipaddress are [ $username,$ipaddress ]"
		echo -n "Enter the keyword [replace], if the above details are incorrect or press the Enter key to continue:"
		read choice

		if test -z $choice
		then
			#Length of the string choice is zero
			choice="add"
			break
		else
			if [ "$choice" != "replace" ]
			then
				echo "Invalid choice !, please try again"
				choice="replace"
			fi
		fi
	done

	if [ "$operation" == "key_install" ]
	then
		echo "+ ssh-keygen configuration"
		echo "+ press only the Enter key as the choice for ssh-keygen configuration, in case of Overwrite (y/n), choose y"
		ssh-keygen
		echo "+ ssh-keygen configuration is sucessfully done !!!"

		while true
		do
			echo "+ You can get the path of public-key id_rsa.pub file from just above the \"randomart image\""

			echo -n "Enter the public-key id_rsa.pub file path:"
			read publickey_path

			if [ -e "$publickey_path" ]
			then
				ssh-copy-id -i $publickey_path $username@$ipaddress
				break
			else
				echo "provided public-key id_rsa.pub file path is incorrect, please enter a valid path"
			fi
		done
	else
		while [ "$choice" == "add" ]
		do
			echo -n "Enter the directory to watch[Target directory path in the Alternate-node to sync is considered as same]:"
			read watch_directory

			if test -z $watch_directory
			then
				echo "It's empty string, please enter a proper path"
				continue
			fi

			incrond_entry="$watch_directory IN_MODIFY,IN_CREATE,IN_DELETE,IN_MOVE,IN_NO_LOOP rsync -rPvaz --exclude=\".*\" --delete $watch_directory/ $username@$ipaddress:$watch_directory"
			incrond_file="/var/spool/incron/$user_account_name"

			echo $incrond_entry >> $incrond_file

			choice=""
			echo -n "Enter the keyword [add], for another incrond_entry or press the Enter key to finish the incrontab configuration:"
			read choice

			if test -z $choice
			then
				#Length of the string choice is zero
				break
			else
				if [ "$choice" != "add" ]
				then
					echo "Invalid choice !, please enter a valid option, otherwise it will be considered as to finish the incrondtab configuration"
					echo -n "Enter the keyword [add], for another incrontab_entry or press the Enter key to finish the incrontab configuration:"
					read choice

					if test -z $choice
					then
						#Length of the string choice is zero
						break
					fi
				fi
			fi
		done
	fi

	echo "Sucessfully configured !!!"

else
	echo "Invalid operation, valid operations are [key_install, add, delete]"
	exit 0
fi
