# seccamp
Work on seccamp!!

TFHE (Fast Fully Homomorphic Encryption on Torus)


## Reference

[here](https://nindanaoto.github.io/)

## Implement test
```
cd TFHE
mkdir build
cd build
cmake ..
make
./test/{ a Executable File }
```

## directry 
```
.
├── LICENSE
├── README.md
└── TFHE
    ├── CMakeLists.txt
    ├── RANDEN
    │   ├── CMakeLists.txt
    │   ├── randen.cc
    │   ├── randen.h
    │   └── vector128.h
    ├── SPQLIOS
    │   ├── CMakeLists.txt
    │   ├── LICENSE
    │   ├── Makefile.old
    │   ├── fft_processor_spqlios.cpp
    │   ├── spqlios-bench.cpp
    │   ├── spqlios-fft-avx.s
    │   ├── spqlios-fft-fma.s
    │   ├── spqlios-fft-impl.cpp
    │   ├── spqlios-fft-unaligned.s
    │   ├── spqlios-fft.h
    │   ├── spqlios-ifft-avx.s
    │   ├── spqlios-ifft-fma.s
    │   ├── spqlios-ifft-unaligned.s
    │   ├── spqlios-model.cpp
    │   └── todo.sh
    ├── include
    │   ├── cloudkey.hpp
    │   ├── common.hpp
    │   ├── detwfa.hpp
    │   ├── gatebootstrapping.hpp
    │   ├── key.hpp
    │   ├── keyswitch.hpp
    │   ├── mulfft.hpp
    │   ├── params.hpp
    │   ├── tfhe++.hpp
    │   ├── tlwe.hpp
    │   ├── trgsw.hpp
    │   └── trlwe.hpp
    ├── src
    │   ├── CMakeLists.txt
    │   ├── detwfa.cpp
    │   ├── gatebootstrapping.cpp
    │   ├── keyswitch.cpp
    │   ├── tlwe.cpp
    │   ├── trgsw.cpp
    │   └── trlwe.cpp
    └── test
        ├── CMakeLists.txt
        ├── a.out
        ├── blind_rotate_main.cpp
        ├── cmux_main.cpp
        ├── external_product_main.cpp
        ├── id_key_switch_main.cpp
        ├── tlwe_main.cpp
        └── trlwe_main.cpp
```