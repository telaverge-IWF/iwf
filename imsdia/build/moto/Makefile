
all:
	echo $(os) $(platform) $(tls) $(sdk) 
	. build.sh os=$(os) platform=$(platform) tls=$(tls) sdk=$(sdk) 

install_static_nrd:   #### Static  Non Redundancy 
	. scripts/make_diaapp_pack-NRD $(IMS_VER)

install_static_rd:    #### Static Redundance
	. scripts/make_diaapp_pack-RD $(IMS_VER)

install_dist_srv_nrd: #### Distributed Server Non Redundancy  
	. scripts/make_dist_server_pack-NRD $(IMS_VER)

install_dist_srv_rd:  #### Distributed Server Redundancy
	. scripts/make_dist_server_pack-RD $(IMS_VER)

install_dist_client:  #### Distributed Client
	. scripts/make_dist_client_pack $(IMS_VER)

install_interfaces:   #### Interfaces  
	. scripts/make_diaapp_pack-INTERFACE $(IMS_VER)


