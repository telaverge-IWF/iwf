set timeout 20

set cmd_type [lindex $argv 0]
set console "#"

if { [string compare $cmd_type "keygen"] == 0 } {
        puts "Cmd Type: keygen\n";

	spawn /bin/rm -fr /root/.ssh/id_rsa /root/.ssh/id_rsa.pub

	spawn /usr/bin/ssh-keygen
	set spawnssh_sd $spawn_id

	expect -i $spawnssh_sd -re "Enter file in which to save the key"
	exp_send -i $spawnssh_sd "/root/.ssh/id_rsa\r"

	expect -i $spawnssh_sd -re "Enter passphrase"
	exp_send -i $spawnssh_sd "\r"

	expect -i $spawnssh_sd -re "Enter same passphrase again"
	exp_send -i $spawnssh_sd "\r"

	expect -i $spawnssh_sd -re $console
}
