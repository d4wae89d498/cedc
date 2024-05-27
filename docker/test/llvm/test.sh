echo "CC: $CC"
echo "CXX: $CXX"
echo "Clang location: $(type clang)"
echo "Clang++ location: $(type clang++)"
echo "cc location: $(type cc)"
echo "c++ location: $(type c++)"
$CC /test.cpp -o /test_cc && echo "CC compilation successful"
$CXX /test.cpp -o /test_cxx && echo "CXX compilation successful"
clang /test.cpp -o /test_clang && echo "Clang compilation successful"
clang++ /test.cpp -o /test_clangpp && echo "Clang++ compilation successful"
cc /test.cpp -o /test_cc_alias && echo "cc alias compilation successful"
c++ /test.cpp -o /test_cxx_alias && echo "c++ alias compilation successful"
echo "Running CC compiled binary:"
./test_cc
echo "Running CXX compiled binary:"
./test_cxx
echo "Running Clang compiled binary:"
./test_clang
echo "Running Clang++ compiled binary:"
./test_clangpp
echo "Running cc alias compiled binary:"
./test_cc_alias
echo "Running c++ alias compiled binary:"
./test_cxx_alias
