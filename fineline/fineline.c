/*  Copyright 2014 Derek Chadwick

    This file is part of the FineLine Computer Forensics Timeline Tools.

    FineLine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    FineLine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FineLine.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
   fineline.c

   Title : FineLine Computer Forensics Timeline Constructor
   Author: Derek Chadwick
   Date  : 22/12/2013

   Purpose: FineLine Main Function.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libevtx.h"
#include "fineline.h"

int main(int argc, char *argv[])
{
   char evtx_in_file[FL_PATH_MAX];
   char fl_out_file[FL_PATH_MAX];
   char gui_ip_address[FL_IP_ADDR_MAX];
   char filter_file[FL_PATH_MAX];
   int mode;
   int res = open_log_file(argv[0]);

   if (res < 0)
   {
      printf("main() <ERROR> Could not open log file.\n");
      exit(FILE_ERROR);
   }
   print_log_entry("main() <INFO> Starting FineLine 1.0\n");

   mode = parse_command_line_args(argc, argv, fl_out_file, evtx_in_file, gui_ip_address, filter_file);
   if (mode > 0)
   {

      if (mode & FL_EVT_IN)
      {
         parse_evt_event_log(evtx_in_file, fl_out_file, mode, gui_ip_address, filter_file);
      }
      else if (mode & FL_EVTX_IN)
      {
         parse_evtx_event_log(evtx_in_file, fl_out_file, mode, gui_ip_address, filter_file);
      }
      else
      {
         print_log_entry("main() <ERROR> Invalid command line options!\n");
         print_help();
      }
   }
   else
   {
      print_log_entry("main() <ERROR> Invalid command line options!\n");
      print_help();
   }

   close_log_file();

   exit(0);
}

/*
   Function: parse_command_line_args
   Purpose : Validates command line arguments.
   Input   : argc, argv, log file and db file handles.
   Return  : mode of operation and database file handle if required.
*/
int parse_command_line_args(int argc, char *argv[], char *fl_event_filename, char *in_file, char *gui_ip_address, char *filter_file)
{
   int retval = 0;
   int input_file_specified = 0;
   char timestr[100];
   int tlen;

   tlen = get_time_string(timestr, 99);

   memset(fl_event_filename, 0, FL_PATH_MAX);
   memset(in_file, 0, FL_PATH_MAX);
   memset(filter_file, 0, FL_PATH_MAX);
   strncpy(fl_event_filename, EVENT_FILE, strlen(EVENT_FILE)); /* the default event filename */

   if (tlen > 0)
   {
      strncat(fl_event_filename, timestr, tlen);
   }
   else
   {
      print_log_entry("parse_command_line_args() <WARNING> Invalid time string.\n");
   }
   strncat(fl_event_filename, EVENT_FILE_EXT, 4);

   if (argc < 2)
   {
	  print_log_entry("parse_command_line_args(): invalid arguments < 2\n");
      return(-1);
   }
   else
   {
      int i;
      for (i = 1; i < argc; i++)
      {
         if (strncmp(argv[i], "-w", 2) == 0)
         {
            retval = retval | FL_FILE_OUT; /* Create FineLine event file */
         }
         else if (strncmp(argv[i], "-s", 2) == 0)
         {
            retval = retval | FL_GUI_OUT; /* Send event records to GUI */
         }
         else if (strncmp(argv[i], "-b", 2) == 0)
         {
            retval = retval | FL_FILE_OUT | FL_GUI_OUT; /* Create FineLine event file and send to GUI */
         }
         else if (strncmp(argv[i], "-o", 2) == 0)
         {
            /* FineLine event file name to use for output of event records */
            if ((i+1) < argc)
            {
               printf("parse_command_line_args() <INFO> FineLine event file: %s\n", argv[i+1]);
               strncpy(fl_event_filename, argv[i+1], strlen(argv[i+1]));
            }
            else
            {
               print_log_entry("parse_command_line_args() <ERROR> Missing event file name.\n");
               return(-1);
            }
         }
         else if (strncmp(argv[i], "-i", 2) == 0)
         {
            /* Windows event file name to use for input */
            if ((i+1) < argc)
            {
               printf("parse_command_line_args() <INFO> Windows event file: %s\n", argv[i+1]);
               strncpy(in_file, argv[i+1], strlen(argv[i+1]));
			      input_file_specified = 1;
			      if (strstr(in_file, ".evtx"))
			      {
				      retval = retval | FL_EVTX_IN;
			      }
			      else if (strstr(in_file, ".evt"))
			      {
				      retval = retval | FL_EVT_IN;
			      }
               else
               {
                  print_log_entry("parse_command_line_args() <ERROR> Unknown event file type.\n");
                  return(-1);
               }
            }
            else
            {
               print_log_entry("parse_command_line_args() <ERROR> Missing Windows event file name.\n");
               return(-1);
            }
         }
		   else if (strncmp(argv[i], "-a", 2) == 0)
		   {
			   if ((i+1) < argc)
			   {
			      printf("parse_command_line_args() <INFO> GUI IP address: %s\n", argv[i+1]);
               strncpy(gui_ip_address, argv[i+1], strlen(argv[i+1]));
			      if (validate_ipv4_address(gui_ip_address) < 0)
			      {
				      print_log_entry("parse_command_line_args() <ERROR> Invalid IPv4 address.\n");
                  return(-1);
			      }
			   }
			   else
			   {
			      print_log_entry("parse_command_line_args() <ERROR> Missing IPv4 address.\n");
               return(-1);
			   }
		   }
         else if (strncmp(argv[i], "-f", 2) == 0)
         {
            /* Filter event file name */
            if ((i+1) < argc)
            {
               printf("parse_command_line_args() <INFO> Filter file: %s\n", argv[i+1]);
               strncpy(filter_file, argv[i+1], strlen(argv[i+1]));
			      retval = retval | FL_FILTER_ON;
            }
            else
            {
               print_log_entry("parse_command_line_args() <ERROR> Missing filter file name.\n");
               return(-1);
            }
         }
      }
   }

   /* Check for input file on command line, if none then do the live system log. */
   if (input_file_specified == 0)
   {
	   strncpy(in_file, EVENT_LOG_PATH, strlen(EVENT_LOG_PATH));
	   strncat(in_file, PATH_SEPARATOR, strlen(PATH_SEPARATOR));
	   strncat(in_file, SECURITY_LOG_FILE, strlen(SECURITY_LOG_FILE));
	   retval = retval | FL_EVTX_IN;
	   print_log_entry("parse_command_line_args() <INFO> Default input file = Security.evtx\n");
   }

   print_log_entry("parse_command_line_args() <INFO> Finished processing command line arguments.\n");

   return(retval);
}


