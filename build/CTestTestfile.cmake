# CMake generated Testfile for 
# Source directory: /mnt/hgfs/share/server
# Build directory: /mnt/hgfs/share/server/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(mytest "/mnt/hgfs/share/server/build/bin/main")
SUBDIRS(lib)
SUBDIRS(bin)
