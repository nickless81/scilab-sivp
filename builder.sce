////////////////////////////////////////////////////////////
// SIVP - Scilab Image and Video Processing toolbox
// Copyright (C) 2005-2006  Shiqi Yu
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
////////////////////////////////////////////////////////////
// =============================================================================
mode(-1);

function main_builder();
  TOOLBOX_NAME  = "SIVP";
  TOOLBOX_TITLE = "SIVP - Scilab Image and Video Processing Toolbox";
  toolbox_dir   = get_absolute_file_path("builder.sce");

  // Check Scilab's version
  // =============================================================================
  try
	  v = getversion("scilab");
  catch
	  error(gettext("Scilab 5.4 or more is required."));
  end

  if v(2) < 4 then
	  // new API in scilab 5.4
	  error(gettext('Scilab 5.4 or more is required.'));  
  end
  
  // Check modules_manager module availability
  // =============================================================================
  if ~isdef('tbx_build_loader') then
    error(msprintf(gettext('%s module not installed."), 'modules_manager'));
  end

  // Action
  // =============================================================================
  tbx_builder_macros(toolbox_dir);
  //tbx_builder_src(toolbox_dir);
  tbx_builder_gateway(toolbox_dir);
  tbx_builder_help(toolbox_dir);
  tbx_build_loader(TOOLBOX_NAME, toolbox_dir);
  tbx_build_cleaner(TOOLBOX_NAME, toolbox_dir);  
endfunction
// =============================================================================
main_builder();
clear main_builder;
// =============================================================================

