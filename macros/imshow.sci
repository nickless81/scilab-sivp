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


function imshow(im, imOutputMode, imParent)
  //============================================================================== 
  function r = imshow_tcltk(im)
    r = [];
    if ~with_tk() then
      warning('Cannot display (no tcl/tk installed).');
      return;
    end

    // get dim of image
    width = size(im, 2);
    height = size(im, 1);
    channel = size(im, 3);
    
    imc = mat2utfimg(im2uint8(im));
    if (channel == 1)
      imc = 'P5' + char(10) + msprintf("%d %d", width, height) + char(10) + '255' + char(10) + char(imc);
    else
      imc = 'P6' + char(10) + msprintf("%d %d", width, height) + char(10) + '255' + char(10) + char(imc);
    end

    TCL_SetVar('imagewidth', msprintf("%d", width));
    TCL_SetVar('imageheight', msprintf("%d", height));
    TCL_SetVar('imagechannel', msprintf("%d", channel));
    TCL_SetVar('imagedata', imc);
    TCL_EvalFile(getSIVPpath() +'/tcl/imshow.tcl');
  endfunction
  //============================================================================== 
  function r = imshow_graphics(im, imParent)
    r = [];
    im = im2double(im);
    [width, height, channel] = size(im);
    if channel == 1 then
      im(:,:,2) = im(:,:,1);
      im(:,:,3) = im(:,:,1);
      channel = 3;
    end
    NumberOfPixels = width * height;    
    ColorMap = matrix(im, NumberOfPixels, channel);
    IndexImage = matrix(1 : NumberOfPixels, width, height);
    if imParent == [] then
      imParent = gcf();
    end

    if imParent.figure_id == 100000 then // demos window
      imParent = scf(); 
    end

    if ~is_handle_valid(imParent) then
      imParent = scf();
    end
    drawlater();
    imParent.color_map = ColorMap;
    Matplot(IndexImage);
    drawnow();
  endfunction
  //============================================================================== 
  function r = imshow_uicontrol(im, imParent)
    r = [];
    im = im2uint8(im);
    [height, width, channel] = size(im);
    imshow_filename = fullpath(TMPDIR + '/imshow_tmp.png');
    if execstr('imwrite(im, imshow_filename);', 'errcatch') == 0 then
      str = "";
      str = str + "<html>";
      str = str + "<img src = ""file:///" + imshow_filename + """ />";
      str = str + "</html>";
      
      if imParent == [] then
        imParent = gcf();
      end

      if imParent.figure_id == 100000 then // demos window
        imParent = scf(); 
      end

      if ~is_handle_valid(imParent) then
        imParent =  scf();
      end

      drawlater();
      imParent.figure_size = [width + 20, height + 100];
      imshow_image = uicontrol("parent", imParent, ..
                               "style", "pushbutton", ..
                               "string", str, ..
                               "units", "pixels", ..
                               "position", [ 0, 0, width, height], ..
                               "background", [1 1 1], ..
                               "tag", "imshow_image", ..
                               "horizontalalignment" , "left", ..
                               "verticalalignment"   , "bottom", ..
                                "Callback", '' );
      imParent.figure_size = [width+20, height+100];
      drawnow();
    end
  endfunction
  //============================================================================== 
  if ~isdef('imParent') then
    imParent = [];
  else
    if type(imParent) <> 9 then
      error(999, msprintf(_("%s: Wrong type for input argument #%d: A handle expected.\n"), 'imshow', 3));
    end
  end

  if ~isdef('imOutputMode') then
    imOutputMode = 0; // output as uicontrol image;
  else
    if type(imOutputMode) <> 1 then
      error(999, msprintf(_("%s: Wrong type for input argument #%d: A scalar double expected.\n"), 'imshow', 2));
    end
    if size(imOutputMode, '*') <> 1 then
      error(999, msprintf(_("%s: Wrong size for input argument #%d: A scalar double expected.\n"), 'imshow', 2));
    end
    if ~or(imOutputMode == [0, 1, 2]) then
      error(999, msprintf(_("%s: Wrong value for input argument #%d: ''%d'' to ''%d'' expected.\n"), 'imshow', 2, 0, 2));
    end
  end
  
  channel = 0;

  //check whether it is an image
  if(size(size(im), 2) == 3) then
    if( size(im, 3) == 3 | size(im, 3) == 1) then
      channel = size(im, 3);
    end
  end
  if(size(size(im), 2) == 2) then
    channel = 1;
  end

  if(channel == 0)
    error("The input should be an image.");
    return;
  end
    
  if imOutputMode == 0 then
     r = imshow_uicontrol(im, imParent);
  else
   if imOutputMode == 1 then
      r = imshow_graphics(im, imParent);
   else
     if imOutputMode == 2 then
       r = imshow_tcltk(im);
     else
       error(999, msprintf(_("%s: Wrong value for input argument #%d: ''%d'' to ''%d'' expected.\n"), 'imshow', 2, 0, 2));
     end
   end
  end
endfunction
