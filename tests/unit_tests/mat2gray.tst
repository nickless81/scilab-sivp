//==============================================================================
// Allan CORNET - 2012 - DIGITEO
//==============================================================================
// unit test mat2gray
//==============================================================================
M = [0:10;0:10];
I = mat2gray(M);
I_REF = [0.    0.1    0.2    0.3    0.4    0.5    0.6    0.7    0.8    0.9    1. ; ..
         0.    0.1    0.2    0.3    0.4    0.5    0.6    0.7    0.8    0.9    1.];
assert_checkequal(I, I_REF);
//==============================================================================
