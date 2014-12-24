FILE(REMOVE_RECURSE
  "CMakeFiles/hello1.dir/hello.cpp.o"
  "libhello1.pdb"
  "libhello1.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/hello1.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
