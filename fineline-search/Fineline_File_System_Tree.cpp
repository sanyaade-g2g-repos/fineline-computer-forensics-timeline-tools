
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
   Fineline_File_System_Tree.cpp

   Title : FineLine Computer Forensics Image Search file browser tree
   Author: Derek Chadwick
   Date  : 05/05/2014

   Purpose: Displays a file system in a tree widget, the file records are stored
            in a map for fast lookups based on the filename key value. This allows
            easy mapping from the FLTK tree nodes to the corresponding file records.

   Notes: EXPERIMENTAL

*/



#include <iostream>

#include "Fineline_File_System_Tree.h"

using namespace std;

Fineline_File_System_Tree::Fineline_File_System_Tree(int x, int y, int w, int h) : Fl_Tree(x, y, w, h)
{

   tooltip("File System Browser");
   box(FL_DOWN_BOX);
   color((Fl_Color)55);
   selection_color(FL_SELECTION_COLOR);
   labeltype(FL_NORMAL_LABEL);
   labelfont(0);
   labelsize(14);
   labelcolor(FL_FOREGROUND_COLOR);
   callback((Fl_Callback*)file_system_tree_callback, (void*)(1234));
   align(Fl_Align(FL_ALIGN_TOP));
   when(FL_WHEN_RELEASE);
   end();

}

Fineline_File_System_Tree::~Fineline_File_System_Tree()
{
   //dtor
}

void Fineline_File_System_Tree::file_system_tree_callback(Fl_Tree *flt, void *vp)
{

   return;
}

int Fineline_File_System_Tree::add_file(string filename, fl_file_record_t *flrp)
{
   add(filename.c_str());
   file_map[filename] = flrp;
   return(file_map.size());
}

fl_file_record_t *Fineline_File_System_Tree::find_file(string filename)
{
   map< string, fl_file_record_t* >::iterator p = file_map.find(filename);

   if(p == file_map.end())
   {
      cout << "Fineline_File_System_Tree::find_file() <INFO> " << filename << " is not in the tree." << endl;
      return(NULL);
   }
   return(p->second);
}

int Fineline_File_System_Tree::remove_file(string filename)
{
   return(file_map.size());
}

int Fineline_File_System_Tree::save_tree()
{
   return(0);
}

int Fineline_File_System_Tree::print_tree()
{
   return(0);
}

int Fineline_File_System_Tree::tree_size()
{
   return(file_map.size());
}

int Fineline_File_System_Tree::clear_tree()
{
   file_map.clear();
   return(file_map.size());
}

void Fineline_File_System_Tree::assign_user_icons()
{
  static const char *L_folder_xpm[] = {
      "11 11 3 1",
      ".  c None",
      "x  c #d8d833",
      "@  c #808011",
      "...........",
      ".....@@@@..",
      "....@xxxx@.",
      "@@@@@xxxx@@",
      "@xxxxxxxxx@",
      "@xxxxxxxxx@",
      "@xxxxxxxxx@",
      "@xxxxxxxxx@",
      "@xxxxxxxxx@",
      "@xxxxxxxxx@",
      "@@@@@@@@@@@"};
  static Fl_Pixmap L_folderpixmap(L_folder_xpm);

   static const char *L_document_xpm[] = {
      "11 11 3 1",
      ".  c None",
      "x  c #d8d8f8",
      "@  c #202060",
      ".@@@@@@@@@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@xxxxxxx@.",
      ".@@@@@@@@@."};
   static Fl_Pixmap L_documentpixmap(L_document_xpm);

  // Assign user icons to tree items
   for ( Fl_Tree_Item *item = first(); item; item=item->next())
   {
      item->usericon(item->has_children() ? &L_folderpixmap : &L_documentpixmap);
   }
   redraw();
}
