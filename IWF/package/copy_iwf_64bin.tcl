set timeout -1

set ReleaseServer_IP "172.16.1.102"
set ReleaseServer_UsrName "build"
set ReleaseServer_Passwd "qwerasdf@123"

set console "Jenkins#]"

set IWF_Binary_Path "/home/jenkins/workspace/IWF_PRODUCT/IWF/package/bin"
set IWF_Binary_Destination_Path "/home/build/Release/IWF/CentOS/64-bit"
set Latest_IWFBinary [exec /bin/ls -lrt $IWF_Binary_Path | tail -1 | tr -s " " | cut -d " " -f 9]
set Build_Date [exec /bin/date +%Y-%m-%d-%H:%M:%S]


#Deletes 15 days older builds and creates current date directory in release server.
spawn ssh -o UserKnownHostsFile=/dev/null  -o StrictHostKeyChecking=no $ReleaseServer_UsrName@$ReleaseServer_IP
set spawnssh_sd $spawn_id

set timeout 1
expect -i $spawnssh_sd -re "(yes/no)?"
exp_send -i $spawnssh_sd "yes\r"
set timeout -1

expect -i $spawnssh_sd -re "assword"
exp_send -i $spawnssh_sd "$ReleaseServer_Passwd\r"
expect -i $spawnssh_sd -re "Last login"
sleep 1
exp_send -i $spawnssh_sd "export PS1=$console\r"
expect -i $spawnssh_sd -re $console

exp_send -i  $spawnssh_sd "cd $IWF_Binary_Destination_Path \r"
expect -i $spawnssh_sd -re $console

exp_send -i  $spawnssh_sd "find . -type d -mtime +15 | rm -fr `xargs -0` \r"
expect -i $spawnssh_sd -re $console
exp_send -i  $spawnssh_sd "mkdir $Build_Date \r"
expect -i $spawnssh_sd -re $console

exp_close -i $spawnssh_sd

#copies iwf binary.
spawn scp -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no $IWF_Binary_Path/$Latest_IWFBinary $ReleaseServer_UsrName@$ReleaseServer_IP:$IWF_Binary_Destination_Path/$Build_Date/
set spawnssh_sd $spawn_id

set timeout 1
expect -i $spawnssh_sd -re "(yes/no)?"
exp_send -i $spawnssh_sd "yes\r"
set timeout -1

exp_send -i $spawnssh_sd "export PS1=$console\r"
expect -i $spawnssh_sd -re "assword"
exp_send -i $spawnssh_sd "$ReleaseServer_Passwd\r"
expect -i $spawnssh_sd -re $console

