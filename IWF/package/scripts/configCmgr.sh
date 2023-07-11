PRODUCT=iwf
source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh



MYSQL_CFG_PATH=$DRE_MYSQL_SERVER_CONFDIR/mysql.cfg 
DB_PORT="db_port" 
DB_PROTOCOL="db_protocol"                                                 
DB_USER="db_user"                                                         
DB_PASS="db_pass"                                                                     
DB_HOST="db_host"

set_port()                                                                    
{                                                                             
    sed -i "s/^$DB_PORT = [^ ]*/$DB_PORT = $1/" $MYSQL_CFG_PATH
}                                                                             

set_protocol()                                                                
{                                                                             
    sed -i "s/^$DB_PROTOCOL = [^ ]*/$DB_PROTOCOL = $1/" $MYSQL_CFG_PATH                                           
}   

set_user()                                                                    
{                                                                             
    sed -i "s/^$DB_USER = [^ ]*/$DB_USER = $1/" $MYSQL_CFG_PATH                                           
}
		                                                                             
set_pass()
{                                                                    
    sed -i "s/^$DB_PASS = [^ ]*/$DB_PASS = $1/" $MYSQL_CFG_PATH                                           
}	

set_host()
{
    sed -i "s/^$DB_HOST = [^ ]*/$DB_HOST = $1/" $MYSQL_CFG_PATH
}

if [ $# != 5 ]
then
    echo "Usage: ./script <protocol> <username> <password> <IPAddress> <port>"
 #   exit 
else
    echo "Updating mysql.cfg file..."
fi



#testing the functions
set_port $5
set_protocol $1
set_user $2
set_pass $3
#incase of active-standby installation mode we have to set the mysql virtual IP
if [ "`GetDreInstallMode`" == "2" ];then
    LOG_DEBUG "Updating virtual IP in mysq.cfg" $LINENO 
    VIP=`GetVirtualIP` 
    set_host `echo "$VIP"|cut -d'/' -f1`
else
    LOG_DEBUG "Updating localhost in mysql.cfg" $LINENO
    set_host $4
fi

 



		               
