# fxp-sort
Scan directories containing .fxp files and determine the target synth. Currently supports Serum and Sylenth files.

# Compilation:

`gcc Main.c -o fxp-sort`

OR

`mingw32-make`

OR 

`mingw32-make all`

# Usage:

`fxp-sort <target_folder> <rename?>`
  
If the rename parameter is not provided then the program will not rename files.
