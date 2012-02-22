// ====================================================================
function demo_camera()
  r = messagebox("Do you really have a camera?", "modal", "info", ["Yes" "No"])

  if r == 1 then
    n = camopen();
    if isdef('n') then
      if n > 0 then
        for idx = 1:100,
          im = avireadframe(n);
          imshow(im);
        end;
        aviclose(n);
      end;
    end;
  end
endfunction  
// ====================================================================
demo_camera();
clear demo_camera;
// ====================================================================
