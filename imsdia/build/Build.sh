#!/bin/sh
########################################################################
#
# Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.
#          Manufactured in the United States of America.
#   1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.
#
########################################################################
#
# ID: $Id: Build.sh,v 3.15 2011/04/08 08:34:17 vnagender Exp $
#
# LOG: Revision 2.4  2006/12/06 09:11:00  chandral
# LOG: Modified Build scripts as GA Rel1.2
# LOG:
# LOG: Revision 1.7  2006/07/31 04:44:25  nvijikumar
# LOG: Changes for Java Package.
# LOG:
# LOG: Revision 1.6  2006/06/14 07:32:42  nvijikumar
# LOG: Changes to maintain version number.
# LOG:
# LOG: Revision 1.5  2006/05/30 05:02:06  nvijikumar
# LOG: Changes for CC compiler options.
# LOG:
# LOG: Revision 1.4  2006/05/18 12:07:16  nvijikumar
# LOG: fix for dist package build.
# LOG:
# LOG: Revision 1.3  2006/05/07 10:05:05  nvijikumar
# LOG: Path exporting for solaris package.
# LOG:
# LOG: Revision 1.2  2006/05/07 05:18:44  nvijikumar
# LOG:
# LOG: Changes to support for solaris and linux OS.
# LOG:
# LOG: Revision 1.1  2006/04/03 12:25:02  nvijikumar
# LOG: Common script to build solaris and linux pkgs
# LOG:
########################################################################


echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo ">>    Package Building Utility       >>"
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo "Is all source compilation complete ?"
echo "Continue <y/n> ? "
read ans

echo "For which customer this release is?"
echo "1. BridgeWater"
echo "2. Motorola-PSG"
echo "3. Others"
read cust

if [ $ans = "y" ]
then
PKG_LOC=/usr/src/redhat/RPMS/i386
linuxInf_pkg()
{    
     PKG=IMSDIA-GA
     APP_PKG=$1
     interface=$2
     VERSION=$IMS_VER
     export PKG VERSION APP_PKG interface
     pwd
     echo "Preparing the Release Directory as ReleaseDir"
     echo "Package Name will start with "$PKG""
     echo " Enter "
     cd linux
     ../common/copyscripts/make_diaapp_pack-INTERFACE
     if [ $? = 0 ]
     then
     pwd
     ./make_diaapp-interface.rpm
     fi
     gzip $PKG_LOC/$APP_PKG-$IMS_VER-$IMS_SUBVER.i386.rpm
}
linuxInf_Jpkg()
{    
     PKG=IMSDIA-GA
     APP_PKG=$1
     interface=$2
     VERSION=$IMS_VER
     export PKG VERSION APP_PKG interface
     pwd
     echo "Preparing the Release Directory as ReleaseDir"
     echo "Package Name will start with "$PKG""
     echo " Enter "
     cd linux
     ../common/copyscripts/make_diaapp_pack-JINTERFACE
     if [ $? = 0 ]
     then
     pwd
     ./make_diaapp-jinterface.rpm
     fi
     gzip $PKG_LOC/$APP_PKG-$IMS_VER-$IMS_SUBVER.i386.rpm
}
solarisInf_pkg()
{
     PKG=IMSDIA-GA
     APP_PKG=$1
     interface=$2
     VERSION=$IMS_VER
     export PKG VERSION APP_PKG interface
     echo "Preparing the Release Directory as ReleaseDir"
     echo "Package Name will start with "$PKG""
     if [ $PLATFORM = "solaris" ]
     then 
         cd solaris
     elif [ $PLATFORM = "solaris64" ]
     then
         cd solaris64
     fi 
     ../common/copyscripts/make_diaapp_pack-INTERFACE
     if [ $? = 0 ]
     then
         cp ./appscripts/PackageMakefile ./ReleaseDir/makefile
         cd ./ReleaseDir
         make
         cd ..
     gzip $IMS_ROOT/build/Packages/$1-sparc-$IMS_VER-$PLATFORM-$IMSCXX 

                if [ $cust = "1" ] #### Renaming package with BW-packagename onyl for Bridgewater
   		then
                    mv $IMS_ROOT/build/Packages/$1-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz $IMS_ROOT/build/Packages/$1-BW-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz
                fi

     fi
     cd ..
}

SourceMotoPsg_pkg()
{
    cd linux
    ../common/copyscripts/make_src_pack-Moto-PSG
}

linux_pkg()
{
      IMSCXX=gcc
      export IMSCXX
      echo "Select the Linux Package you need to Build"
      echo "a. For Static Client-Server Package"
      echo "b. For Distributed Server Package"
      echo "c. For Distributed Client Package"
      echo "d. For All Packages"
      echo "e. For C++ Interface Packages"
      echo "f. For Java Interface Packages"
      echo "g. For source Packages"

      read choice
      if [ $choice = "a" ]
      then
           echo "Select the type of Package"
           echo " 1. General-IMSDIA "
           echo " 2. BCGI"
           read apiType
           if [ $apiType = "1" ]
           then
               echo "Select Redundant or Non Redundant"
               echo " 1. Non-Redundant "
               echo " 2. Redundant"
               read pType
               if [ $pType = "1" ]
               then
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_diaapp_pack-NRD
               if [ $? = 0 ]
               then
                   ./make_diaapp-GA.rpm
               mv $PKG_LOC/IMSDIA-GA-$IMS_VER-$IMS_SUBVER.i386.rpm $PKG_LOC/IMSDIA-GA-NRD-$IMS_VER-$IMS_SUBVER.i386.rpm
               gzip $PKG_LOC/IMSDIA-GA-NRD-$IMS_VER-$IMS_SUBVER.i386.rpm

               fi
               elif [ $pType = "2" ]
               then
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_diaapp_pack-RD
               if [ $? = 0 ]
               then
                   ./make_diaapp-GA.rpm
               mv $PKG_LOC/IMSDIA-GA-$IMS_VER-$IMS_SUBVER.i386.rpm $PKG_LOC/IMSDIA-GA-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               gzip $PKG_LOC/IMSDIA-GA-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               fi
                else
              echo " Please select valid type"
             fi

	   elif [ $apiType = "2" ]
           then
               echo "Select Redundant or Non Redundant"
               echo " 1. Non-Redundant "
               echo " 2. Redundant"
               read pType
               if [ $pType = "1" ]
               then
               echo " Enter "
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_diaapp_pack-BCGI-NRD
               if [ $? = 0 ]
               then
                   ./make_diaapp-BCGI.rpm
               mv $PKG_LOC/IMSDIA-BCGI-$IMS_VER-$IMS_SUBVER.i386.rpm $PKG_LOC/IMSDIA-BCGI-NRD-$IMS_VER-$IMS_SUBVER.i386.rpm
               gzip $PKG_LOC/IMSDIA-BCGI-NRD-$IMS_VER-$IMS_SUBVER.i386.rpm
               fi
               elif [ $pType = "2" ]
               then
               echo " Enter "
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_diaapp_pack-BCGI-RD
               if [ $? = 0 ]
               then
                   ./make_diaapp-BCGI.rpm
               mv $PKG_LOC/IMSDIA-BCGI-$IMS_VER-$IMS_SUBVER.i386.rpm $PKG_LOC/IMSDIA-BCGI-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               gzip $PKG_LOC/IMSDIA-BCGI-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               fi

              else
              echo " Please select valid type"
             fi

           else
              echo " Please select valid Package type"
           fi
           cd -

        elif [ $choice = "b" ]
        then
           echo "Select Redundant or Non Redundant"
           echo " 1. Non-Redundant "
           echo " 2. Redundant"
           echo " 3. IWLAN"
           read pType
           if [ $pType = "1" ]
           then
               echo " Enter "
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_dist_server_pack-NRD
               if [ $? = 0 ]
               then
                   ./make_dist_server.rpm
               mv $PKG_LOC/IDS-$IMS_VER-$IMS_SUBVER.i386.rpm $PKG_LOC/IDS-NRD-$IMS_VER-$IMS_SUBVER.i386.rpm
               gzip $PKG_LOC/IDS-NRD-$IMS_VER-$IMS_SUBVER.i386.rpm
               fi
           elif [ $pType = "2" ]
           then
               echo " Enter "
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_dist_server_pack-RD
               if [ $? = 0 ]
               then
                   ./make_dist_server.rpm
               mv $PKG_LOC/IDS-$IMS_VER-$IMS_SUBVER.i386.rpm $PKG_LOC/IDS-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               gzip $PKG_LOC/IDS-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               fi
           elif [ $pType = "3" ]
           then
               echo " Enter "
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_dist_server_pack_wlan
               if [ $? = 0 ]
               then
                   ./make_dist_server.rpm
               mv $PKG_LOC/IDS-$IMS_VER-$IMS_SUBVER.i386.rpm $PKG_LOC/IDS-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               gzip $PKG_LOC/IDS-RD-$IMS_VER-$IMS_SUBVER.i386.rpm
               fi
           else
              echo " Please select valid type"
           fi
           cd -


       elif [ $choice = "c" ]
       then
           echo "Select the API type to build a Package"
           echo " 1. For C++ API Client "
           echo " 2. For JAva API Client "
           read apiType
           if [ $apiType = "1" ]
           then
               echo " Enter "
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_dist_client_pack
               if [ $? = 0 ]
               then
                   ./make_dist_client.rpm
               gzip $PKG_LOC/IDC-$IMS_VER-$IMS_SUBVER.i386.rpm
               fi
           elif [ $apiType = "2" ]
           then
               echo " Enter "
               echo "Preparing the Release Directory as ReleaseDir"
               cd linux
               ../common/copyscripts/make_dist_jdiaapp_pack
               if [ $? = 0 ]
               then
                   ./make_dist_jdiaapp.rpm
               fi
           else
              echo " Please select valid API type"
           fi
           cd -

       elif [ $choice = "d" ]
       then
           echo "Building all Packages"
           cd linux

           ../common/copyscripts/make_diaapp_pack
	   if [ $? = 0 ]
  	   then
 	       ./make_diaapp.rpm
	   fi

           ../common/copyscripts/make_dist_server_pack
           if [ $? = 0 ]
           then
               ./make_dist_server.rpm
           fi

           ../common/copyscripts/make_dist_diaapp_pack
           if [ $? = 0 ]
           then
               ./make_dist_diaapp.rpm
           fi

       elif [ $choice = "e" ]
       then
           echo "Select the New Interface type to build a Package"
           echo " 1. For GX API "
           echo " 2. For TX API "
           echo " 3. For RX API "
           echo " 4. For WX API "
           echo " 5. For TY API "
           echo " 6. For CX-3GPP2 API "
           echo " 7. For E2 API "
           echo " 8. For E4 API "
           echo " 9. For EAP API "
           echo " 10. For MIP API "
           echo " 11. For NASREQ API "
           echo " 12. For RQ API "
           echo " 13. For SH-3GPP2 API "
           echo " 14. For WM API "
	   echo " 15. For s6a API "
	   echo " 16. For s13 API "
           echo " 99. For ALL API "
           read apiType
           if [ $apiType = "1" ]
           then
              #linux_pkg <APP_PKG> <interface>
              linuxInf_pkg GX gx
           elif [ $apiType = "2" ]
           then
              linuxInf_pkg TX tx
           elif [ $apiType = "3" ]
           then
              linuxInf_pkg RX rx
           elif [ $apiType = "4" ]
           then
              linuxInf_pkg WX wx
           elif [ $apiType = "5" ]
           then
              linuxInf_pkg TY ty
           elif [ $apiType = "6" ]
           then
              linuxInf_pkg CX-3GPP2 cx_3gpp2
           elif [ $apiType = "7" ]
           then
              linuxInf_pkg E2 e2
           elif [ $apiType = "8" ]
           then
              linuxInf_pkg E4 e4
           elif [ $apiType = "9" ]
           then
              linuxInf_pkg EAP eap
           elif [ $apiType = "10" ]
           then
              linuxInf_pkg MIP mip
           elif [ $apiType = "11" ]
           then
              linuxInf_pkg NASREQ nasreq
           elif [ $apiType = "12" ]
           then
              linuxInf_pkg RQ rq
           elif [ $apiType = "13" ]
           then
              linuxInf_pkg SH-3GPP2 sh_3gpp2
           elif [ $apiType = "14" ]
           then
              linuxInf_pkg WM wm
           elif [ $apiType = "15" ]
           then
              linuxInf_pkg S6A s6a
           elif [ $apiType = "16" ]
           then
              linuxInf_pkg S13 s13
           elif [ $apiType = "99" ]
           then
              linuxInf_pkg GX gx
              linuxInf_pkg TX tx
              linuxInf_pkg RX rx
              linuxInf_pkg WX wx
              linuxInf_pkg TY ty
              linuxInf_pkg CX-3GPP2 cx_3gpp2
              linuxInf_pkg E2 e2
              linuxInf_pkg E4 e4
              linuxInf_pkg EAP eap
              linuxInf_pkg MIP mip
              linuxInf_pkg NASREQ nasreq
              linuxInf_pkg RQ rq
              linuxInf_pkg SH-3GPP2 sh_3gpp2
              linuxInf_pkg WM wm
	      linuxInf_pkg S6A s6a
 	      linuxInf_pkg S13 s13
           else
              echo " Please select valid API type"
           fi

       elif [ $choice = "f" ]
       then
           echo "Select the New Interface type to build a Package"
           echo " 1. For GX API "
           echo " 2. For TX API "
           echo " 3. For RX API "
           echo " 4. For WX API "
           echo " 5. For TY API "
           echo " 6. For CX-3GPP2 API "
           echo " 7. For E2 API "
           echo " 8. For E4 API "
           echo " 9. For EAP API "
           echo " 10. For MIP API "
           echo " 11. For NASREQ API "
           echo " 12. For RQ API "
           echo " 13. For SH-3GPP2 API "
           echo " 14. For WM API "
           echo " 99. For ALL API "
           read apiType
           if [ $apiType = "1" ]
           then
              #linux_pkg <APP_PKG> <interface>
              linuxInf_Jpkg JGX gx
           elif [ $apiType = "2" ]
           then
              linuxInf_Jpkg JTX tx
           elif [ $apiType = "3" ]
           then
              linuxInf_Jpkg JRX rx
           elif [ $apiType = "4" ]
           then
              linuxInf_Jpkg JWX wx
           elif [ $apiType = "5" ]
           then
              linuxInf_Jpkg JTY ty
           elif [ $apiType = "6" ]
           then
              linuxInf_Jpkg JCX-3GPP2 cx_3gpp2
           elif [ $apiType = "7" ]
           then
              linuxInf_Jpkg JE2 e2
           elif [ $apiType = "8" ]
           then
              linuxInf_Jpkg JE4 e4
           elif [ $apiType = "9" ]
           then
              linuxInf_Jpkg JEAP eap
           elif [ $apiType = "10" ]
           then
              linuxInf_Jpkg JMIP mip
           elif [ $apiType = "11" ]
           then
              linuxInf_Jpkg JNASREQ nasreq
           elif [ $apiType = "12" ]
           then
              linuxInf_Jpkg JRQ rq
           elif [ $apiType = "13" ]
           then
              linuxInf_Jpkg JSH-3GPP2 sh_3gpp2
           elif [ $apiType = "14" ]
           then
              linuxInf_Jpkg JWM wm
           elif [ $apiType = "99" ]
           then
              linuxInf_Jpkg GX gx
              linuxInf_Jpkg TX tx
              linuxInf_Jpkg RX rx
              linuxInf_Jpkg WX wx
              linuxInf_Jpkg TY ty
              linuxInf_Jpkg CX-3GPP2 cx_3gpp2
              linuxInf_Jpkg E2 e2
              linuxInf_Jpkg E4 e4
              linuxInf_Jpkg EAP eap
              linuxInf_Jpkg MIP mip
              linuxInf_Jpkg NASREQ nasreq
              linuxInf_Jpkg RQ rq
              linuxInf_Jpkg SH-3GPP2 sh_3gpp2
              linuxInf_Jpkg WM wm
           else
              echo " Please select valid API type"
           fi
       elif [ $choice = "g" ]
       then
           if [ $cust = "2" ]
           then
               SourceMotoPsg_pkg;
           fi
       fi
}

solaris_pkg()
{

      PATH=$PATH:/usr/local/bin:/usr/sfw/bin:/bin
      export PATH
      echo "Select the compiler for Solaris Package"
      echo "1. For GCC"
      echo "2. For CC"
      read compiler
      if [ $compiler = 1 ]
      then
         echo "Selected compiler is GCC"
         IMSCXX=gcc
         export IMSCXX
      elif [ $compiler = 2 ]
      then
         echo "Selected compiler is CC"
         IMSCXX=CC
         export IMSCXX
      else
         echo " Please select proper compiler"
         exit 1;
      fi
  
      echo "Select the Solaris Package you need to Build"
      echo "a. For Static Client-Server Package"
      echo "b. For Static TCS"
      echo "c. For Distributed Server Package"
      echo "d. For Distributed Client Package"
      echo "e. For All Package"
      echo "f. For New Interface Packages"
      if [ $cust = "2" ]
      then
          echo "g. Source Packages"
      fi

      read choice
      if [ $choice = "a" ]
      then
          echo "Select Redundant or Non Redundant"
          echo " 1. Non-Redundant "
          echo " 2. Redundant"
          read pType
          if [ $pType = "1" ]
          then
              PKG=IMSDIA-GA
              VERSION=$IMS_VER
              export PKG VERSION IMS_SUBVER
              echo "Preparing the Release Directory as ReleaseDir"
              echo "Package Name will start with "$PKG""
              if [ $PLATFORM = "solaris" ]
              then 
                  cd solaris
              elif [ $PLATFORM = "solaris64" ]
              then 
                  cd solaris64
              fi 
              $IMS_ROOT/build/common/copyscripts/make_diaapp_pack-NRD
              if [ $? = 0 ]
              then
                  cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
                  cd ./ReleaseDir
                  make
                  cd ..
              mv $IMS_ROOT/build/Packages/IMSDIA-GA-sparc-$IMS_VER-$PLATFORM-$IMSCXX $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX
              gzip $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX

                if [ $cust = "1" ] #### Renaming package with BW-packagename onyl for Bridgewater
   		then
                    mv $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-BW-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz
                fi

              fi
          elif [ $pType = "2" ]
          then
              PKG=IMSDIA-GA
              VERSION=$IMS_VER
              export PKG VERSION
              echo "Preparing the Release Directory as ReleaseDir"
              echo "Package Name will start with "$PKG""
              if [ $PLATFORM = "solaris" ]
              then 
                  cd solaris
              elif [ $PLATFORM = "solaris64" ]
              then
                  cd solaris64
              fi 
              $IMS_ROOT/build/common/copyscripts/make_diaapp_pack-RD
              if [ $? = 0 ]
              then
                  cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
                  cd ./ReleaseDir
                  make
                  cd ..
              mv $IMS_ROOT/build/Packages/IMSDIA-GA-sparc-$IMS_VER-$PLATFORM-$IMSCXX $IMS_ROOT/build/Packages/IMSDIA-GA-RD-sparc-$IMS_VER-$PLATFORM-$IMSCXX
              gzip $IMS_ROOT/build/Packages/IMSDIA-GA-RD-sparc-$IMS_VER-$PLATFORM-$IMSCXX

                if [ $cust = "1" ] #### Renaming package with BW-packagename onyl for Bridgewater
  		then
                    mv $IMS_ROOT/build/Packages/IMSDIA-GA-RD-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz $IMS_ROOT/build/Packages/IMSDIA-GA-RD-BW-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz
                fi

              fi

           else
              echo " Please select valid Package type"
        fi
        cd ..
      elif [ $choice = "b" ]
      then
        PKG=IMSDIA-GA
        VERSION=$IMS_VER
        export PKG VERSION IMS_SUBVER
        echo "Preparing the Release Directory as ReleaseDir"
        echo "Package Name will start with "$PKG""
        cd solaris
        $IMS_ROOT/build/common/copyscripts/make_diaapp_pack-TCS
        if [ $? = 0 ]
        then
          cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
          cd ./ReleaseDir
          make
          cd ..
          mv $IMS_ROOT/build/Packages/IMSDIA-GA-sparc-$IMS_VER-$PLATFORM-$IMSCXX $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX
          gzip $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX

           mv $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz $IMS_ROOT/build/Packages/IMSDIA-GA-NRD-TCS-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz
        fi
        cd ..
       elif [ $choice = "c" ]
       then
           echo "Select Redundant or Non Redundant"
           echo " 1. Non-Redundant "
           echo " 2. Redundant"
           read pType
           if [ $pType = "1" ]
             then
             PKG=IDS
             VERSION=$IMS_VER
             export PKG VERSION
             echo "Preparing the Release Directory as ReleaseDir"
             echo "Package Name will start with "$PKG""
             if [ $PLATFORM = "solaris" ]
             then 
                 cd solaris
             elif [ $PLATFORM = "solaris64" ]
             then
                 cd solaris64
             fi 
             $IMS_ROOT/build/common/copyscripts/make_dist_server_pack-NRD
             if [ $? = 0 ]
             then
                 cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
                 cd ./ReleaseDir
                 make
                 cd ..
              mv $IMS_ROOT/build/Packages/IDS-sparc-$IMS_VER-$PLATFORM-$IMSCXX $IMS_ROOT/build/Packages/IDS-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX
              gzip $IMS_ROOT/build/Packages/IDS-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX

                if [ $cust = "1" ] #### Renaming package with BW-packagename onyl for Bridgewater
		then
                    mv $IMS_ROOT/build/Packages/IDS-NRD-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz $IMS_ROOT/build/Packages/IDS-NRD-BW-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz
                fi

             fi
             cd ..

           elif [ $pType = "2" ]
             then
             PKG=IDS
             VERSION=$IMS_VER
             export PKG VERSION
             echo "Preparing the Release Directory as ReleaseDir"
             echo "Package Name will start with "$PKG""
             if [ $PLATFORM = "solaris" ]
             then 
                 cd solaris
             elif [ $PLATFORM = "solaris64" ]
             then
                 cd solaris64
             fi 
             ../common/copyscripts/make_dist_server_pack-RD
             if [ $? = 0 ]
             then
             cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
             cd ./ReleaseDir
             make
             cd ..
             mv $IMS_ROOT/build/Packages/IDS-sparc-$IMS_VER-$PLATFORM-$IMSCXX $IMS_ROOT/build/Packages/IDS-RD-sparc-$IMS_VER-$PLATFORM-$IMSCXX
              gzip $IMS_ROOT/build/Packages/IDS-RD-sparc-$IMS_VER-$PLATFORM-$IMSCXX

                if [ $cust = "1" ] #### Renaming package with BW-packagename onyl for Bridgewater
		then
                    mv $IMS_ROOT/build/Packages/IDS-RD-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz $IMS_ROOT/build/Packages/IDS-RD-BW-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz
                fi

           fi
      fi
      cd ..

       elif [ $choice = "d" ]
       then
           echo "Select the API type to build a Package"
           echo " 1. For C++ API Client "
           echo " 2. For JAva API Client "
           read apiType
           if [ $apiType = "1" ]
           then
               PKG=IDC
               VERSION=$IMS_VER
               export PKG VERSION
               echo "Preparing the Release Directory as ReleaseDir"
               echo "Package Name will start with "$PKG""
               if [ $PLATFORM = "solaris" ]
               then 
               cd solaris
               elif [ $PLATFORM = "solaris64" ]
               then 
               cd solaris64
               fi 
               $IMS_ROOT/build/common/copyscripts/make_dist_client_pack
               if [ $? = 0 ]
               then
                   cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
                   cd ./ReleaseDir
                   make
                   cd ..
                   gzip $IMS_ROOT/build/Packages/IDC-sparc-$IMS_VER-$PLATFORM-$IMSCXX

                if [ $cust = "1" ] #### Renaming package with BW-packagename onyl for Bridgewater
		then
                    mv $IMS_ROOT/build/Packages/IDC-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz $IMS_ROOT/build/Packages/IDC-BW-sparc-$IMS_VER-$PLATFORM-$IMSCXX.gz
                fi

               fi
           elif [ $apiType = "2" ]
           then
               PKG=JIDC
               VERSION=$IMS_VER
               export PKG VERSION
               echo "Preparing the Release Directory as ReleaseDir"
               echo "Package Name will start with "$PKG""
               if [ $PLATFORM = "solaris" ]
               then 
                   cd solaris
               elif [ $PLATFORM = "solaris64" ]
               then
                   cd solaris64
               fi 
               ../common/copyscripts/make_dist_jdiaapp_pack
               if [ $? = 0 ]
               then
                   cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
                   cd ./ReleaseDir
                   make
                   cd ..
               fi
           fi
           cd ..

       elif [ $choice = "e" ]
       then
           cd solaris

           # Building static package.
           PKG=IMSDIA
           VERSION=$IMS_VER
           export PKG VERSION
           echo "Preparing the Release Directory as ReleaseDir"
           echo "Package Name will start with "$PKG""
           ../common/copyscripts/make_diaapp_pack
           if [ $? = 0 ]
           then
               cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
               cd ./ReleaseDir
               make

               cd ..
           fi

           # Building Dist server package
           PKG=IDS
           VERSION=$IMS_VER
           export PKG VERSION
           echo "Preparing the Release Directory as ReleaseDir"
           echo "Package Name will start with "$PKG""
           ../common/copyscripts/make_dist_server_pack
           if [ $? = 0 ]
           then
               cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
               cd ./ReleaseDir
               make
               cd ..
           fi

           # Building Dist client package
           PKG=IDC
           VERSION=$IMS_VER
           export PKG VERSION
           ECho "Preparing the Release Directory as ReleaseDir"
           echo "Package Name will start with "$PKG""
           ../common/copyscripts/make_dist_diaapp_pack
           if [ $? = 0 ]
           then
               cp ./pscripts/PackageMakefile ./ReleaseDir/makefile
               cd ./ReleaseDir
               make
               cd ..
           fi
           cd ..

       elif [ $choice = "f" ]
       then
           echo "Select the New Interface type to build a Package"
           echo " 1. For GX API "
           echo " 2. For TX API "
           echo " 3. For RX API "
           echo " 4. For WX API "
           echo " 5. For TY API "
           echo " 6. For CX-3GPP2 API "
           echo " 7. For E2 API "
           echo " 8. For E4 API "
           echo " 9. For EAP API "
           echo " 10. For MIP API "
           echo " 11. For NASREQ API "
           echo " 12. For RQ API "
           echo " 13. For SH-3GPP2 API "
           echo " 14. For WM API "
           echo " 99. For ALL API " 
           read apiType
           if [ $apiType = "1" ]
           then
               solarisInf_pkg GX gx; 
           elif [ $apiType = "2" ]
           then
               solarisInf_pkg TX tx; 
           elif [ $apiType = "3" ]
           then
               solarisInf_pkg RX rx; 
           elif [ $apiType = "4" ]
           then
               solarisInf_pkg WX wx; 
           elif [ $apiType = "5" ]
           then
               solarisInf_pkg TY ty; 
           elif [ $apiType = "6" ]
           then
               solarisInf_pkg CX-3GPP2 cx_3gpp2; 
           elif [ $apiType = "7" ]
           then
               solarisInf_pkg E2 e2; 
           elif [ $apiType = "8" ]
           then
               solarisInf_pkg E4 e4; 
           elif [ $apiType = "9" ]
           then
               solarisInf_pkg EAP eap; 
           elif [ $apiType = "10" ]
           then
               solarisInf_pkg MIP mip; 
           elif [ $apiType = "11" ]
           then
               solarisInf_pkg NASREQ nasreq; 
           elif [ $apiType = "12" ]
           then
               solarisInf_pkg RQ rq; 
           elif [ $apiType = "13" ]
           then
               solarisInf_pkg SH-3GPP2 sh_3gpp2; 
           elif [ $apiType = "14" ]
           then
               solarisInf_pkg WM wm; 
           elif [ $apiType = "99" ]
           then
               solarisInf_pkg GX gx; 
               solarisInf_pkg TX tx; 
               solarisInf_pkg RX rx; 
               solarisInf_pkg WX wx; 
               solarisInf_pkg TY ty; 
               solarisInf_pkg CX-3GPP2 cx_3gpp2; 
               solarisInf_pkg E2 e2; 
               solarisInf_pkg E4 e4; 
               solarisInf_pkg EAP eap; 
               solarisInf_pkg MIP mip; 
               solarisInf_pkg NASREQ nasreq; 
               solarisInf_pkg RQ rq; 
               solarisInf_pkg SH-3GPP2 sh_3gpp2; 
               solarisInf_pkg WM wm; 
           else
               echo "Wrong choice"
           fi
       elif [ $choice = "g" ]
       then
           if [ $cust = "2" ]
           then
               SourceMotoPsg_pkg;
           fi
       fi

}


#Script Starts from Here

   if [ `id | cut -d "(" -f1 | cut -d "=" -f2` != 0 ]
       then
       echo ""
       echo "THIS SCRIPT MUST BE RUN AS ROOT";
       echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
       echo "Please use "su" command, dont use "su -""
       echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
       exit 0;
   fi

   echo "Select the Platform that you need to build a Package"
   echo " 1. For Linux "
   echo " 2. For Solaris "
   read plt
   echo "Please enter the version number::"
   read imsversion
   IMS_VER=$imsversion
   echo "Please enter the Sub version number::"
   read imssubversion
   IMS_SUBVER=$imssubversion
   export IMS_VER
   export IMS_SUBVER
   if [ $plt = "1" ]
   then

      if [ $PLATFORM = "linux" ]
      then
      linux_pkg;
      else
      echo "Please select the proper Platform"
      fi

   elif [ $plt = "2" ]
   then
      if [ ! -d $IMS_ROOT/build/Packages ]
      then
          mkdir -p $IMS_ROOT/build/Packages
      fi 
      if [ $PLATFORM = "solaris" ]
      then
      solaris_pkg;
      elif [ $PLATFORM = "solaris64" ]
      then
      solaris_pkg;
      else
      echo "Please select the proper Platform"
      fi

   else
      echo "You have selected the invalid option"
   fi
else
echo "Please finish compilation first "
fi

exit 0
