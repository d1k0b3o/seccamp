# seccamp
Work on seccamp!!

Homomorphic Encryption

# Reference

[here](https://nindanaoto.github.io/)

# Implement test
```
cd TFHE
mkdir build
cd build
cmake ..
make
./test/{実行ファイル}
```

# directry 
```
-TFHE/
   -CMakeLists.txt
   -src/
     -CMakeLists.txt
     -tlwe.cpp
     -trlwe.cpp
     -trgsw.cpp
   -include/
     -common.hpp
     -params.hpp
     -key.hpp
     -tfhe++.hpp
     -mulfft.hpp
     -tlwe.hpp
     -trlwe.hpp
   -test/
     -CMakeLists.txt
     -tlwemain.cpp
     -trlwemain.cpp
   -RANDEN/
     -CMakeLists.txt
     -randen.cc
     -randen.h
     -vector128.h
   -SPQLIOS/
     -
```