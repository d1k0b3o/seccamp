#pragma once

#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../include/common.hpp>
#include<../SPQLIOS/spqlios-fft.h>

namespace myTFHE{
    using namespace std;

    inline void TwistFFTlvl1(Polynomiallvl1 &res,const PolynomialInFDlvl1 &a){
        fftplvl1.execute_direct_torus32(res.data(),a.data());
    }

    inline void TwistIFFTlvl1(PolynomialInFDlvl1 &res,const Polynomiallvl1 &a){
        fftplvl1.execute_reverse_torus32(res.data(),a.data());
    }

    inline void PolyMullvl1(const Polynomiallvl1 &res,const Polynomiallvl1 &a,const lwekeylvl1 &b){
        
        PolynomialInFDlvl1 ffta;    // array<double,DEF_N>
        TwistIFFTlvl1(ffta,a);

        PolynomialInFDlvl1 fftb;
        TwistIFFTlvl1(fftb,b);

        MulInFD<DEF_N>(ffta,ffta,fftb);

        TwistFFTlvl1(res,ffta);

    }


}// myTFHE