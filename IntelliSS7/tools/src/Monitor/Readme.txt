			Process monitoring Utility

This process is a service that monitors other console applications.

1) The processes that need to be monitored are to specified in the file its_monitor.dat

2) The path of its_monitor.dat is in the environment variable ITS_MONITOR_PATH. By default
it is C:\Winnt\system32

3) The format of its_monitor.dat is as follows

  task MyProcess
  group 1 (Optional: Processes can be clustered into groups. 
	  So a restart action is taken on the whole group)
  directory C:\MyDirectory\MyProcess
  minimize/hide/maximize
  no restart/no start (Optional: if you dont want this process to restart or start in the begin)
  sleep seconds
  run MyProgram (Path of the the program to be executed)

4) To install the ITS_Monitor service, type
   ITS_Monitor -install

5) To remove the ITS_Monitor service, type
   ITS_Monitor -remove

6) After you install the service, start the service from the Services Panel.

7) To stop the service, stop the service from the Services Panel.

8) The environment under which the service operates is outputted in C:\Winnt\system32\env.txt

9) Events are generated in the Event Log under the name ITS_Monitor.

10) Report the bugs in the file bugs.txt
