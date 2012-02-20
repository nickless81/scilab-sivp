// -------------------------------------------------------------------------
// SIVP - Scilab Image Processing toolbox
// Copyright (C) 2012 - DIGITEO - Allan CORNET
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// -------------------------------------------------------------------------
//
// =============================================================================
function cleaner_help()
  path = get_absolute_file_path("cleaner_help.sce");
  langdirs = dir(path);
  langdirs = langdirs.name(langdirs.isdir);

  for l = 1:size(langdirs, '*')
    masterfile = fullpath(path + filesep() + langdirs(l) + "/master_help.xml");
    mdelete(masterfile);
   
    jarfile = fullpath(path + "/../jar/scilab_" + langdirs(l) + "_help.jar");
    mdelete(jarfile);
    
    tmphtmldir = fullpath(path + "/" + langdirs(l) + "/scilab_" + langdirs(l) + "_help");
    rmdir(tmphtmldir, 's');
  end
endfunction
// =============================================================================
cleaner_help();
clear cleaner_help;
// =============================================================================
