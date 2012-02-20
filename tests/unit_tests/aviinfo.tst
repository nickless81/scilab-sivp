//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test aviinfo
//==============================================================================
info = aviinfo(fullpath(getSIVPpath() + "/images/video.avi"));
assert_checkequal(type(info), 17);
assert_checkequal(getfield('VideoCompression', info), 'xvid');
assert_checkequal(getfield('NumFrames', info), 224);
//==============================================================================