SPREAD: A Reliable Multicast and Group Communication Toolkit
-----------------------------------------------------------

/===========================================================================\
| The Spread Group Communication Toolkit.                                   |
| Copyright (c) 1993-2001 Spread Concepts LLC                               |
| All rights reserved.                                                      |
|                                                                           |
| The Spread package is licensed under the Spread Open-Source License.      |
| You may only use this software in compliance with the License.            |
| A copy of the license can be found at http://www.spread.org/license       |
|                                                                           |
| This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF     |
| ANY KIND, either express or implied.                                      |
|                                                                           |
| Spread is developed at the Center for Networking and Distributed Systems, |
| The Johns Hopkins University.                                             |
|                                                                           |
| Creators:                                                                 |
|    Yair Amir             yairamir@cs.jhu.edu                              |
|    Michal Miskin-Amir    michal@spread.org                                |
|    Jonathan Stanton      jonathan@cs.jhu.edu                              |
|                                                                           |
| Major Contributors:                                                       |
|    Dan Schoenblum   dansch@cnds.jhu.edu - Java Interface Developer.       |
|    John Schultz     jschultz@cnds.jhu.edu - contribution to process group |
|                              membership.      |
|    Theo Schlossnagle theos@cnds.jhu.edu - Perl library and Skiplists      |
|                                                                           |
| Special thanks to the following for providing ideas and/or code:          |
|    Ken Birman, Danny Dolev, Mike Goodrich, Ben Laurie,                    |
|    David Shaw, Robbert VanRenesse.                                        |
|                                                                           |
| Contributors:                                                             |
|    Ben Laurie        ben@algroup.co.uk - FreeBSD port and warning fixes   |
|                                                                           |
| WWW    : http://www.spread.org  and  http://www.cnds.jhu.edu              |
| Contact: spread@spread.org                                                |
|                                                                           |
| Version 3.16.0 Built 25/June/2001                                         |
\===========================================================================/

June 25, 2001 Ver 3.16.0
-------------------------
Changes:
1) Add support for configuring multiple interfaces on daemons. Each daemon
   can now choose which interfaces to listen on for client connections, monitor
   requests, and daemon-to-daemon communication.
2) Added support for MacOSX. Thanks to Julien Defour and Dirk-Willem van Gulik.
3) Agreed messages for join/leave instead of SAFE messages.
4) Fixed bug with membership messages for more then 42 members in a group.
5) Document how to monitor packing effectiveness.
6) SP_connect assigns unique private name if user gives a zero length string as
   the user name.
7) Slightly loosen valid field checking for service_type field to allow
   flush and secure spread libraries to work.
8) Fix events to work with low priority events for Splash.
9) Adds modular access control and authentication system that allows the 
   daemon to authenticate client connections and allow or disallow various
   actions (such as joining groups, sending messages or connecting) based
   on the authenticated user. This changes the client-server network
   protocol, but is backward compatible with clients linked with old libraries.
   This also adds new functions to the API. A sample module that
   provides access control based on the IP address of the client is 
   included. Also a module that provides the same "allow all clients" 
   policy as older versions of Spread. The Java API has also been 
   updated to support the new access control framework.
10) New license for Spread. BSD based open-source license.
11) Updated Perl library with some bug fixes and compatibility with new C lib.
12) Added support for 64 bit platforms (alpha, ultrasparc & ia64) Note only
    alpha is actually tested.
13) Fix bug in sp.c where if a message was not completely received because 
    of a short buffer and the next call had an invalid message scatter the
    data in the messages would get corrupted. Probably difficult to trigger 
    unless you are trying hard.
14) Changed names of programs included with spread to have "sp" as a prefix.
    This should help avoid conflicts with all the other utilities called 
    "user" or "monitor".
15) Small bugfixes to the Java library. 
16) Bugfix which removes a costly, and unnecessary, recalculation when 
    several network level membership events occur in close (time) proximity.
 
March 20, 2001 Ver 3.15.2
-------------------------

Changes:
1) Bugfix to java library to fix exception caused when trying to establish
   connection. This is a new bug in 3.15.1. Thanks to Julien Dufour.
2) Add #define SPREAD_VERSION to sp.h so client applications can test for
   what version of the spread API to use. This allows applications to compile
   against multiple incompatible versions of the spread library. Specifically,
   this can be used for an app to support both the old 'float SP_version()'
   and new 'int SP_version(int, int, int)' functions.
3) Fix memory leak in Perl module. Thanks to Theo Schlossnagle.

February 26, 2001 Ver. 3.15.1
-----------------------------
Changes:
1) Make sess_read() non-blocking so slow clients sending messages don't slow
   or block daemon.
2) Implement input validation on all messages received from clients. This
   is to address the possibility of clients overflowing the servers buffers.
   These problems were uncovered in a security audit by Olaf Kirch of Caldera.
3) Use chroot to isolate spread and drop priveledges if spread is run by root.
   If it is run as a normal user, then no chroot is done and it runs just as 
   before. The user to run as and the location of the chroot jail can be 
   configured in the spread_params.h file at compile time.
4) Fix a bug that causes a significant memory leak when retransmissions are 
   required. This memory leak exists in versions 3.13, 3.14 and 3.15.0.
5) SP_version() no longer returns a float, instead it returns in 3 separate
   parameters the 3 components of the version number.
 
December 20, 2000 -- Unreleased 3.15.0
-----------------
Changes:
1) New version number scheme with 3 components: Major, Minor, and Patch.
2) Small bugfix to prevent clients from sending to too many groups and
   crashing spread.
3) Copyright changed to Spread Concepts LLC for code by original
   developers.

0ctober 31, 2000 
---------------
Changes:
1) Bugfixes to skiplist implementation.
2) Critical fixes to group membership that removes bugs introduced in 
   optimization work of 3.13.
3) Critical bugfix to membership which solves problem introduced in 3.13 
   with using configurations of more then one segment.
4) Changes to spread.conf parser, but nothing that should be user visable.
5) Better error/problem reporting in a few cases.
6) Enforce message length limit. SP_mcast* will now return an error
   if a message body is too long.
7) Minor memory leak at initialization fixed.
8) Fix to events.c to prevent an illegal message bug. Bug is triggered
   when messages are sent very fast during a membership merge.

August 07, 2000
---------------
Changes:
1) To compile the Linux version on systems based on glibc2.0 (such as 
   RedHat 5.2) you need to comment out the #define of HAVE_STDINT_H in the 
   arch.h file before compiling.

2) Major scalability improvements. Should now support upto 990 connections
   to each daemon, thousands of groups, and faster throughput with
   small messages.

3) Configuration file changes. 
    a) The default name of the configuration file 
       has changed from config.dat to spread.conf. The default locations 
       checked if nothing is specified on the command line is 
       /etc/spread.conf and ./spread.conf (i.e. the current directory 
       where the binary is run from).
    b) The format of the spread.conf file is improved. You no longer
       have to specify the number of members of a segment or the number
       of segments by hand. The format is also more standard and has a 
       lex/yacc grammer defining it. See the sample.spread.conf file 
       for an example or the documention for details.
    c) More configuration variables. 
        EventLogFile: You can now have all the Spread event messages 
                  that print to the screen print to a file instead.
                  To have each daemon log to a separate file use the
                  '%h' or '%H' special characters in the log filename.
                  Spread will replace those characters with the hostname
                  of the machine which the daemon is running on. An 
                  example can be found in the sample.spread.conf file.
        DebugFlags: The event mask that determines which messages
                to print to the screen is now configurable at
                runtime.
        EventTimeStamp: Add a timestamp in front of all logged event 
                messages and set the format of the timestamp.

        DangerousMonitor: Certain monitor commands like partition, kill
                  and flow_control are disabled by default now.
                  To enable them set this to true.

4) Fix membership bug when under high load and a late data message arrives.
   Also fix membership bug where the assertion 
"spread: membership.c:1835: Backoff_membership: Assertion `pack_entry != -1' failed."
   triggered.
   Also fix membership bug where several machines will get trapped in 
   State 3 (GATHER state) and will never complete the membership.

5) Some documentation on how to tune Spread using some of the internal variables.
   This is contained in the new Spread User Guide Chapter 2 which can be 
   downloaded from www.spread.org.

6) Fix bug in new No Drop semantics. When a BUFFER_TOO_SHORT error occured
   the endian_mismatch field was incorrectly set to the size of the app buffer
   instead of the size of the data message. So it was useless. This is fixed and
   the semantics are extended to set the num_groups and endian_mismatch fields to 0
   if the corresponding buffers ARE large enough, and to the needed size 
   (as a negative) when they are NOT large enough. This allows you to know when 
   you receive a GROUPS_TOO_SHORT whether the buffer is also too short without 
   any calculation...Just check if endian_mismatch is 0.

7) License updated to version 1.2. The only change is a small addition to the
   attribution requirement, a capitalization of Spread, and a clarification of
   the Spread version.

May 01, 2000
---------------
Changes:
1) Integrated FreeBSD port. A Big thanks to Ben Laurie <ben@algroup.co.uk>
   for this port and a lot of compile warnings, type cleanups and 2 bugfixes.

2) Removed some compile warnings.

3) 2 bugs fixed. One in SP_group_ids_equal() and one in the 
   daemon that would never trigger in reality.

4) Updated java interface to most recent version.

5) Updated events (E_* functions) to most recent version. This
   adds the ability to attach to file descriptors for 
   Exceptions and Write events as well as reads. It also 
   adds a void* data pointer to the callback parameters.

6) Change SP_recv semantics to be "No Drop" by default. The 
   old "drop" semantics are still available by setting the 
   service_type parameter to SP_recv to DROP_RECV before calling it.
   *** 
   See the file "Short_Buffer_Handling.txt" for detailed comments
   on this change and what application modifications might be necessary
   ***

7) Documentation updates.

8) Changed the way arch.h is implemented. This might require 
   some additions for Ports that we do not support natively.

9) Added Is_self_leave() macro which matches documentation for testing
   self-leaves.

10) Changed SP_* and E_* functions to use 'const' appropriately.

11) Reserved fields are listed in sp.h to prevent collisions.

12) Make MAX_PROC_NAME and MAX_PRIVATE_GROUP sizes available in sp.h.

13) Added Perl library interface. You can now write Spread client 
    programs in perl. Thanks to Theo Schlossnagle <theos@cnds.jhu.edu>.

14) License updated to version 1.1. Main change is a reformatting and 
    updated email addresses. 

July 27, 1999 Official Release
---------------------------------------------------

1) Has new license (license.txt) and copyright notices

2) New Java interface included

3) Location of license has moved to: 
        http://www.spread.org/license/
        http://www.cnds.jhu.edu/spread/license/

4) Minor documentation and example program improvements.

5) One minor bug fixed in group handling.

May 26, 1999 Release:
---------------------
1) Expiration Date Removed from Binary version
   This release of the executatbles will not expire.

2) New Copyright Statement
   The copyright of Spread has been finalized. The statement at the top of 
   this file shows it.

3) Source release soon & new license
   a) As soon as a few final issues are resolved we will release the source
      to Spread under the CNDS Non-Commercial and Development License. 
   b) A draft of the new license can be found at 
      http://www.cnds.jhu.edu/spread/CNCL/.
      Please email us any comments or concerns you have at spread@spread.org

4) Bugs Fixed:
   a) Bug fix to the SP_scatter_recv() call to make receives into 
      scatter structures of multiple entries of different sizes work.
   b) The Linux platform also had scatter-gather functionality enabled 
      (now that glibc has working sendmsg, recvmsg calls)
   c) Fixed bug where packets which are delayed a long time in the network
      but then actually arrive at a spread daemon cause a crash.


October 30,1998 Release:
-----------
1) Multi-threading:
   Libsp.a has split into two libraries, libsp.a and libtsp.a, they
   are identical except that libtsp.a is thread-safe and libsp.a is not.
   Both versions are provided so that single-threaded programs who don't 
   need a safe library can avoid the (admittedly pretty small) overhead of 
   locking. The libtsp.a can be used identically with libsp.a with the 
   addition that all SP_* functions can be called by multiple threads 
   at the same time.  Thread safety in libtsp.a is provided optimally,
   with the most possible parallelism allowed.  Threads acting on separate
   mailboxes will never block each other, threads writing to a mailbox will
   never block other threads reading from the same mailbox and vice versa.
   The one time thread calls to SP_ functions will be serialzed is when 
   multiple threads are reading the same mailbox or writing the same mailbox.
   There is minimal locking of internal structures which can temporarily 
   block another thread, but since a thread never blocks while in one of 
   these structure critical sections and the duration of the lock is at 
   most a fewinstructions the delay should be minimal.  
   
2) IP-Multicast:
   Spread now allows you to specifiy IP-Multicast addresses(i.e. 224.0.0.1) 
   as the broadcast address for a segment in the spread.conf file. This will 
   work transparently in the same segment, and is guaranteed not to spill 
   multicast packets beyond that segment. If multi-segment ip-multicast is 
   desired, please contact us.

3) Fixed several minor bugs.

4) Included man pages for SP functions. The old html documentation is also 
   included.

5) None of these changes effect the Java version which has not changed.

SOURCE INSTALL:
---------------

The source install is a work in progress, but the included makefiles should
build spread on any currently supported platform. Any not-currently supported
platform that has reasonably close to normal sockets networking should also 
be easily portable. See the file PORTING for hints on porting.

From the directory where you unpacked the Spread source distribution do 
the following:

1) Pick the appropriate makefile for your platform and symlink it to 
Makefile. For example, on linux do:
         [jonathan@commedia]$ ln -s LINUX_makefile Makefile

2) Run "make"

3) Copy the resulting "spread,spflooder,spmonitor,spuser,sptuser" binaries to 
wherever you want.
Probably somewhere in your path like /usr/local/bin/

4) Copy the library "libsp.a, libtsp.a" to a library location, 
like /usr/local/lib.

5) Copy the man pages to the appropriate location (i.e. 
/usr/local/man/man{1,3} )

6) Copy the header files "sp.h", "sp_func.h" and "sp_events.h"  to /usr/local/include.

7) Create a spread.conf file appropriate to your local configuration. For 
more info on how to do this look below in the binary install instructions.

To build on Windows (95/NT) we use a MSVC project. We currently do not 
include the project files in the source distribution, but talk to us if 
you want to build it there.
It is not too hard, just a few quirks about linking and DEFINE flags.


BINARY INSTALL:
--------

We recommend that if you are experimenting with spread you create a special
'spread' directory (for example /usr/local/spread or /opt/spread) and keep
all the files together there so it is easy to find stuff.  That also makes 
it easier to run multiple architectures as the binaries for each are in their
own subdirectory. This is not necessary though. You can create that directory
anywhere (e.g. your own directory).

If you are installing spread for active use it is probably easier to just 
install the correct version of the binaries, headers, man pages, and 
libraries into your standard locations.  The directions below assume you 
are doing this.

1) Unpack the spread.tar.gz file into a temporary directory

2) Look at the Readme for any updates

3) Select the appropriate architecture:
    arch-bsdi
    arch-sgi
    arch-sunos
    arch-sunsol
    arch-pcsol
    arch-linux

4) Type 'make arch-????' with your architecture as the option to make

5) Now you need to copy the files, 
   I will assume you use /usr/local/{bin,include,lib,man}
   Replace "ARCH" with the directory for your architecure.

    cp -p include/* /usr/local/include/
    cp -p ARCH/libsp.a /usr/local/lib/
    cp -p ARCH/spread /usr/local/bin/
    cp -p ARCH/spmonitor /usr/local/bin/
    cp -p ARCH/spuser /usr/local/bin/
    cp -p ARCH/sptuser /usr/local/bin/
    cp -p ARCH/simple_user /usr/local/bin/
    cp -p ARCH/spflooder /usr/local/bin/
    cp -p docs/*.3 /usr/local/man/man3/
    cp -p docs/*.1 /usr/local/man/man1/

6) To run spread you need to modify the 'spread/sample.spread.conf' file for
   your network configuration.  Comments in the sample file explain this.
   Then cp -p sample.spread.conf /usr/local/bin/spread.conf
   (Notice the name change.  The config file must be named that to be found.
    Alternatively you can run spread -c <config_file_name> )

    You can run "spread usage" to see the spread running options.


To use the Java classes and examples you need to have a copy of the 
main 'spread' daemon running.  Then the sp.class file gives you the 
equivelent of the libsp.a as a java class.  The user.java, user.html, 
and user.class files give you a demonstration applet and source code.  
The tree.html AllNames.html and packages.html give some documentation 
for the java interface.

For Windows (95/NT) systems use the spread.exe daemon and the libsp.lib 
to link with your programs.


OVERVIEW:
---------

Spread consists of two parts, an executable daemon which is executed on 
each machine which is part of the heavyweight 'machine' group, and a library
 which provides a programming interface for writing group multicast 
applications and which is linked into the application.

    The daemon, called "spread", should be run as a non-priveledged 
user (we created a 'spread' user) and only needs permissions to create a 
socket in /tmp and read its config file which should be in the same 
directory as the executable.  By default the daemon binds to and runs 
off the non-priveledged port 4803 unless the config file indicates otherwise.
    Each daemon can be started independently and if it does not find 
any other members of its defined configuration currently active it runs as 
a machine group of 1 machine.  When other daemons are started they will join
this machine group.

    The machines which are running a daemon with a common config file 
form a 'machine group' (in contrast to a 'process group').  The daemons 
handle multicasting mesages between each other,providing ordering and 
delivery guarantees, detecting and handling failures of nodes or links, and 
managing all applications which are connected to each daemon.

    Each application utilizing the spread system needs to link with 
the 'libsp.a', 'libtsp.a', 'libtsp.lib' or 'libsp.lib' library and needs 
to use the calls defined in the 'sp.h' and 'sp_func.h' header files.  
Documentation for the interface is currenly incomplete, but a basic 
application must do at least the following:

1) Before using any other spread calls you need to 'connect' to a daemon 
   by calling the
    SP_connect(...) call.  This will set a mbox which is an integer 
representing your connection to the daemon.  You use this when making other
spread calls.  You CAN connect to daemons multiple times from the same 
application (and we know of times when this is very useful).

2) If you want to receive messages from a group you need to call SP_join().
Groups are named with standard alphanumeric strings.

3) To send to a group you do NOT need to join it, just call SP_multicast() 
with an appropriate group name.  You will not receive the messages back if 
you are not a member of the group.

4) To be nice to everyone else you should call SP_disconnect() when your 
program is finished using the spread system, if you do not your program's 
disconnection will eventually be detected. 

Some important observations when writing spread programs:

1) All the messages for a particular connection are received during an 
SP_receive() call.  This includes messages from different groups and 
membership messages(like group leave and join), so you must demultiplex 
them yourself.  This is a feature. You can opt to avoid getting membership 
messages all together by indicating that to SP_connect().

2) Spread handles endian differences correctly for metadata and our headers 
but does NOT convert your data for you.  It DOES tell you in the SP_receive 
call whether or not the data originated at machine with a different 
endianness then yours so you can easily use this to convert it yourself 
if necessary. 

3) Each connection to a daemon has a unique 'private group' name which 
can be used to send a message to a particular, and only to a particular, 
application connection.  

4) Spread supports the following ordering/delivery guarantees for messages:

    Unreliable  (least)
    Reliable    (will get there, no ordering)
    Fifo        (reliable and ordered fifo by source)
    Causal      (reliable and all mesg from any source of this level
            are causally ordered)
    Agreed      (reliable and all mesg from any source of this level 
            are totally ordered)
    Safe        (Agreed ordering and mesg will not be delivered to 
            application until the mesg has reached ALL 
            receipients' daemons)

For more detail, much of which IS important, see papers on 
Extended Virtual Sychrony, Transis and Totem.


UTILITY PROGRAMS:
-----------------

    Spread comes with several demonstration programs and useful tools.

1) spmonitor:
    This program has a special interface to spread which allows it to 
control a machine group.  It can terminate all the spread daemons in the 
group, change flow control parameters, and monitor the stats for one or all 
of the machines.  It needs to know the spread.conf file used for a particular
 set of spread daemons.

2) spuser:

    This program is provided with source and uses all the functions of 
the spread interface.  It also acts as a simple client which is useful for 
testing. Reading the source code to this program should show you how to use
all the features of spread, and answer many questions about syntax details.

3) simple_user:

    This is just about the simplest spread program possible and is 
provided with source.  It sends and receives text strings.

4) spflooder:
    
    This is used as one type of performace test.  It 'floods' a spread 
group with data messages. It is provided with source.


CONTACT:
--------

If you have any questions please feel free to contact:

    commedia@cnds.jhu.edu
    yairamir@cs.jhu.edu
    jonathan@cs.jhu.edu
