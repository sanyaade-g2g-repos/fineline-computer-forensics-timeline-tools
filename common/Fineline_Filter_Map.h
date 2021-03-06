
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
   Fineline_Filter_Map.h

   Title : FineLine Computer Forensics Timeline Constructor
   Author: Derek Chadwick
   Date  : 10/04/2014

   Purpose:  Loads in the file filter list into a hashmap. Each filter value can be
             a partial or full filename/path or just a keyword.

             Filter List Format: plain text file, place each file/keyword on a separate line.

             Examples:

             C:\temp
             exploit
             shellcode.bin
             warez.doc
             accounts.xls
             C:\temp\utils\exploit.txt

*/


#ifndef FINELINE_FILTER_MAP_H
#define FINELINE_FILTER_MAP_H

class Fineline_Filter_Map
{
   public:
      Fineline_Filter_Map();
      virtual ~Fineline_Filter_Map();
   protected:
   private:
};

#endif // FINELINE_FILTER_MAP_H
