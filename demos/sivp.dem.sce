
// ====================================================================
demopath = get_absolute_file_path("sivp.dem.sce");

subdemolist = ["Image reading and showing", "image.sce"; ..
"Canny edge detector",       "canny.sce"; ..
"Add Gussian noise",         "noise.sce"; ..
"Video reading and showing", "video.sce"; ..
"Grab frames from a camera", "camera.sce"; ..
"Track object using CamShift", "camshift.sce"; ..
"Foreground detection", "bgfg.sce"; ..
"Face detection", "face.sce"; ..
"Eye detection", "eye.sce";];

subdemolist(:,2) = demopath + subdemolist(:,2);
// ====================================================================

