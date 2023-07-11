SETUP:
------
Server Hostnames: hadev1, hadev2 -> these play the role of ACTIVE/STANDBY node at runtime
OS: CentOS-6.2-x86_64

NOTES:
------
In the following, the values of server hostnames, ethernet interface names, IP addresses, TIPC network id and TIPC network address are examples.

It MUST be ensured that the VIPs (virtual IP addresses) and their corresponding routing prefixes (associated with corresponding subnet masks for IPv4) are same on both nodes.

There shall be no practical limit to the number of IPv4/IPv6 addresses that can be assigned - these MUST be assigned on the ethernet interface earmarked for Diameter / Management Client (CLI / WebUI) traffic

TIPC network id MUST be same on both nodes, else, the nodes will not talk to each other.

Both nodes MUST have UNIQUE hostnames.

Both nodes MUST be time SYNCHRONIZED - NTP can be used for this, to do this in an easy and accurate way.

If both nodes are operational and configured properly, ACTIVE/STANDBY determination is automatic.

Manual Switchover is SUPPORTED - requires CLI / WebUI to effect a manual switchover.

hadev1 details:
---------------
eth0 -> 172.16.8.50 -> Should not be used for Diameter / Management Client / TIPC traffic; intended for general reachability
eth1 -> 172.16.9.54 -> HA software configured (example) to assign IP addresses 172.16.9.61 (Diameter traffic) and 172.16.9.62 (Management Client traffic)
eth2 -> 172.16.10.54 -> MySQL configured (example) to assign VIP addresss 172.16.10.71 (CMGR must be configured with this IP address) on eth2:0
eth3 -> 172.16.11.54 -> TIPC primary (DRE heartbeat) channnel
eth4 -> 172.16.13.54 -> TIPC secondary (DRE heartbeat) channel

Linux Ethernet Bonding shall be configured in the future

TIPC -> Network Id: 1983 -> Address (Z.C.N): 1.1.23 -> Bearers: eth3, eth4 (refer above)

hadev2 details:
---------------
eth0 -> 172.16.8.51 -> Should not be used for Diameter / Management Client (CLI / WebUI) / TIPC traffic; intended for general server reachability
eth1 -> 172.16.9.55 -> HA software configured (example) to assign IP addresses 172.16.9.61 (Diameter traffic) and 172.16.9.62 (Management Client traffic)
eth2 -> 172.16.10.55 -> MySQL configured (example) to assign VIP addresss 172.16.10.71 (CMGR must be configured with this IP address) on eth2:0
eth3 -> 172.16.11.55 -> TIPC primary (DRE heartbeat) channnel
eth4 -> 172.16.13.55 -> TIPC secondary (DRE heartbeat) channel

Linux Ethernet Bonding shall be configured in the future

TIPC -> NetId: 1983 -> Address (Z.C.N): 1.1.29 -> Bearers: eth3, eth4 (refer above)

DRE HA Steps:
=============
1. DRE service script is /etc/init.d/dre. DRE can be STARTED using 'service dre start'. DRE can be STOPPED using 'service dre stop'. DRE can be restarted using 'service dre restart'. Any of start / stop / restart commands must be issued with 'root' permissions. The initial Availability Manager logging level and whether STANDALONE mode are specified in /etc/sysconfig/dre.
2. DRE can be configured to start automatically on REBOOT using 'service chkconfig on'. The same can be disabled using 'service chkconfig off'.
3. 'net.ipv4.conf.all.arp_filter = 1' must be added to /etc/sysctl.conf. This configuration is required to prevent the ARP flux issue - shall be required for ethernet bonding
4. DRE specific setup will be placed in /etc/profile.d/dre.sh. This will prevent the need to specifically source any shell script manually.
5. If 172.16.6.250 (example) is the Near-Hop Gateway / Arbitrator IP address, the following must be added to /etc/sysconfig/network-scripts/route-eth0 to ensure reachability to the Near-Hop Gateway / Arbitrator using 'eth0' (example). As mentioned above, 'eth0' is intended for general reachability. This is to ensure that the node has a 'neutral' path to reach the Near-Hop Gateway / Arbitrator.

	#'n' must be replaced with a number, depending on whether entries already exist in the file, else 'n' can be zero
	ADDRESSn=172.16.6.250
	NETMASKn=255.255.255.255
	GATEWAYn=0.0.0.0

6. The Linux NetworkManager service should be disabled using 'chkconfig NetworkManager off'.

7. Check TIPC links between the two nodes are up and running.
8. Till CLI/WebUI -> CMGR -> AvaMgr -> CMAPI -> MySqL path is available, Availability Manager configuration will be read (at startup) from /opt/diameteriq/bin - configuration file name is 'avamgr.cfg'. Ensure that AVAMGR_CONFDIR environment variable is exported through /etc/profile.d/dre.sh.
9. Syslogd must be configured for Syslog logging.
10. Reboot required after executing the above steps.
11. After reboot, TIPC reconfiguration may be required.

Replication of Rules Engine (RE) Rules files:
---------------------------------------------
The rules files can be changed through the Rule Editor, or manually. On any CREATE, UPDATE or DELETE operation in the RE specific directories (monitored through the iNotify cron daemon, namely incrond) , the corresponding rules files will be synced (using rsync) between the two nodes.

Steps (Replication of Rules files):
-----------------------------------
1) Install the incron-0.5.10 package
2) Run the incrond_configuration.sh script (interactive) - specify the directories to be watched for; in this case the directories meant to be pointed by the RE_CONFDIR and ERLBF_RE_CONFDIR environment variables
3) Run incrond (root permissions required)

MySQL HA Setup:
===============
MySQL HA will use Linux Heartbeat (standard) and MySQL Master-Master Replication (standard). MySQL ACTIVE/STANDBY determination is INDEPENDENT of and DECOUPLED from DRE ACTIVE/STANDBY determination (this is for simplicity and elegance), i.e., ACTIVE DRE instance MAY host the STANDBY MySQL instance, and vice versa. A CMGR instance will always automatically talk to the ACTIVE MySQL instance, irrespective of which node the ACTIVE MySQL instance is running on - this is possible through the use of the VIP assigned for MySQL HA.

A MySQL client MUST only use the MySQL VIP to communicate with the MySQL HA setup [the relevant (MySQL) GRANT PRIVILEGES must be setup for this purpose].

Pre-requisites:
---------------
1) Copy these packages from:
---------------------------
	Path -	172.16.3.25:/home/public/Software/Linux
	Files -
		1) PyXML-0.8.4-19.el6.x86_64.rpm
		2) cluster-glue-libs-1.0.5-6.el6.x86_64.rpm
		3) cluster-glue-1.0.5-6.el6.x86_64.rpm
		4) resource-agents-3.9.2-7.el6.x86_64.rpm
		5) heartbeat-libs-3.0.4-1.el6.x86_64.rpm
		6) heartbeat-3.0.4-1.el6.x86_64.rpm


2) Install the packages (the following order MUST be maintained)
	1) rpm -ivh PyXML-0.8.4-19.el6.x86_64.rpm
	2) rpm -ivh cluster-glue-libs-1.0.5-6.el6.x86_64.rpm
	3) rpm -ivh cluster-glue-1.0.5-6.el6.x86_64.rpm
	4) rpm -ivh resource-agents-3.9.2-7.el6.x86_64.rpm
	5) rpm -ivh heartbeat-libs-3.0.4-1.el6.x86_64.rpm
	6) rpm -ivh heartbeat-3.0.4-1.el6.x86_64.rpm

Note:
-----
MUST: iptables must be STOPPED or FLUSHED or configured to allow peer (MySQL) traffic on UDP port 694 (refer UDP port configuration below).

Recap:
------
Server Hostnames: hadev1, hadev2 -> these play the role of ACTIVE/STANDBY MySQL node at runtime
MySQL ethernet interface -> eth2 -> MySQL configured to assign VIP addresss 172.16.10.71 (CMGR must be configured with this IP address) on eth2:0

Linux HA Configuration:
-----------------------
Directory -> /etc/ha.d

Files that need to be changed:
------------------------------
1) authkeys
2) ha.cf
3) haresources
4) /etc/hosts

In 1) authkeys, configure:
--------------------------
auth 1
1 crc

In 2) ha.cf, configure:
-----------------------
debugfile /var/log/ha-debug
logfile	   /var/log/ha-log
logfacility    local0
keepalive 1
deadtime 15
udpport	   694
baud	19200
auto_failback  on
node	hadev1
node	hadev2
debug 1

In 3) haresources, confgiure:
-----------------------------
hadev1 IPaddr:172.16.10.71/16/eth2/172.16.255.255

	Note (in this case):
	--------------------
		Preferred Active Node - hadev1
		Virtual IP address - 172.16.10.71
		Subnet Mask - 255.255.0.0 (equivalent to a routing prefix of 16)
		Ethernet Interface - eth2
		Broadcast address - 172.16.255.255

In 4) /etc/hosts, configure:
----------------------------
IP addresses and hostname of both the nodes

172.16.8.50	hadev1	  hadev1
172.16.8.51	hadev2	  hadev2

MySQL Configuration:
--------------------

Master side MySQL Configuration:
--------------------------------
GRANT REPLICATION SLAVE ON *.* TO replica@"%" IDENTIFIED BY 'replica_passwd';
GRANT ALL ON *.* to replica@'172.16.8.51' IDENTIFIED BY 'replica_passwd';
GRANT ALL ON *.* to root@'172.16.8.51' IDENTIFIED BY 'intelliss7';
GRANT ALL ON *.* to root@'172.16.8.50' IDENTIFIED BY 'intelliss7';
STOP SLAVE;
CHANGE MASTER TO MASTER_HOST='172.16.8.51', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';
START SLAVE;

Master side my.cfg Configuration:
---------------------------------
#Replication Configuration
server-id=1
# Enable binary logs. Path to bin log is optional
log-bin=mysqlha
# If the binary log exceeds 10M, rotate the logs
max_binlog_size=10M

Slave Side Mysql Configuration:
-------------------------------
GRANT REPLICATION SLAVE ON *.* TO replica@"%" IDENTIFIED BY 'replica_passwd';
GRANT ALL ON *.* to replica@'172.16.8.50' IDENTIFIED BY 'replica_passwd';
GRANT ALL ON *.* to root@'172.16.8.50' IDENTIFIED BY 'intelliss7';
GRANT ALL ON *.* to root@'172.16.8.51' IDENTIFIED BY 'intelliss7';
STOP SLAVE;
CHANGE MASTER TO MASTER_HOST='172.16.8.50', MASTER_USER='replica', MASTER_PASSWORD='replica_passwd';
START SLAVE;

Slave side my.cfg Configuration:
--------------------------------
#Replication Configuration
server-id=2
# Enable binary logs. Path to bin log is optional
log-bin=mysqlha
# If the binary log exceeds 10M, rotate the logs
max_binlog_size=10M

Further Considerations:
=======================
1) In the event that all TIPC links fail, i.e., both primary and secondary DRE heartbeat channels fail, a node will try to interact with the arbitrator (using a non-TIPC mechanism -> ICMP ping) to determine if the node is still in the network, i.e., can possibly interact with other nodes - if the node does not get any response from the arbitrator, it will think that it is isolated from the network, and hence will switch to STANDBY state if it was running as ACTIVE when the event happened (else, if it was running as STANDBY when the event happened, it will 'remain' in the STANDBY state) - this is to 'minimize' the possibility of having TWO ACTIVE nodes in the system, which the current solution is not designed for.

However, in the unlikely event that 'both' the nodes are able to interact with the arbitrator in case of an all-TIPC link failure, both nodes will become ACTIVE - the situation will lead to a race condition - a manual intervention is required in this case to a) shutdown one of the DREs ('service dre stop'), b) restore at least one TIPC link and then, c) start the DRE that had been shutdown.

In future, when we shall have more than two Diametriq nodes in the HA setup, a 'more' intelligent arbitrator function shall be considered, which in the scenario described above will perform a STONITH (Shoot The Other Node In The Head) function, where the arbitrator will decide which of the two currently ACTIVE nodes should remain active.

2) Tomcat Servlet Container and Memcached MUST be run separately, i.e., Availability Manager WILL NOT manage them - these probably can be scheduled for automatic restarts using /etc/inittab (investigation required). These entities must be in a READY state on both the nodes. Because they are being used as STATELESS entities, they will not be designated as ACTIVE/STANDBY, but they MUST be in READY state on both the nodes.

3) Memcached DOES NOT implicitly support replication of its content. Hence, memcached data replication is outside the scope of the solution, currently.
