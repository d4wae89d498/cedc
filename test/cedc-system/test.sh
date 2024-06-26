echo "CC: $CC"
echo "CXX: $CXX"
echo "Clang location: $(type clang)"
echo "Clang++ location: $(type clang++)"
echo "cc location: $(type cc)"
echo "c++ location: $(type c++)"
echo "LDFLAGS: $LDFLAGS"
echo "CXXFLAGS: $CXXFLAGS"
$CC /test.cpp -o ./test_CC && echo "'CC' compilation successful"
$CXX /test.cpp -o ./test_CXX && echo "'CXX' compilation successful"
clang ./test.cpp -o ./test_clang && echo "'clang' compilation successful"
clang++ ./test.cpp -o ./test_clangpp && echo "'Clang++' compilation successful"
cc ./test.cpp -o ./test_cc_alias && echo "'cc' alias compilation successful"
c++ ./test.cpp -o ./test_cxx_alias && echo "'c++' alias compilation successful"
echo "Running 'CC' compiled binary:"
./test_CC
echo "Running 'CXX' compiled binary:"
./test_CXX
echo "Running 'clang' compiled binary:"
./test_clang
echo "Running 'clang++' compiled binary:"
./test_clangpp
echo "Running 'cc' alias compiled binary:"
./test_cc_alias
echo "Running 'c++' alias compiled binary:"
./test_cxx_alias
