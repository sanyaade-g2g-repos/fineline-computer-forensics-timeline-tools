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
   Fineline_UI.h

   Title : FineLine Computer Forensics Image Search GUI
   Author: Derek Chadwick
   Date  : 02/04/2014

   Purpose: FineLine FLTK GUI.

   Notes: EXPERIMENTAL

*/


#ifndef FINELINE_UI_H
#define FINELINE_UI_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/filename.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Native_File_Chooser.H>

#include "Fineline_Thread_FLTK.h"
#include "Fineline_File_System.h"
#include "Fineline_File_System_Tree.h"

class Fineline_UI
{
   public:
      Fineline_UI();
      ~Fineline_UI();

      void show(int argc, char *argv[]);

	   static void main_menu_callback(Fl_Widget *w, void *x);
	   static void open_menu_callback(Fl_Widget *w, void *x);
	   static void save_menu_callback(Fl_Widget *w, void *x);
	   static void export_menu_callback(Fl_Widget *w, void *x);
	   static void popup_menu_callback(Fl_Widget *w, void *x);
	   static void update_screeninfo(Fl_Widget *b, void *p);
	   static void button_callback(Fl_Button *b, void *p);
	   static int load_forensic_image(const char *filename);
	   static int start_image_process_thread(const char *filename);



   protected:
   private:

      Fl_Double_Window *window;
      Fl_Menu_Bar *menu;
      Fl_Menu_Button *popup_menu;
      Fl_Box *box;

      static Fineline_Thread *socket_thread;
      static Fl_Browser *event_browser;
      static Fineline_File_System_Tree *file_system_tree;
      static Fineline_File_System *file_system;
      static Fl_Native_File_Chooser *fc;
      static Fineline_Log *flog;

};

#endif // FINELINE_UI_H
