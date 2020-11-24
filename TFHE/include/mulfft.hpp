#pragma once

#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../include/common.hpp>
#include<../SPQLIOS/spqlios-fft.h>

// 

namespace myTFHE{
    using namespace std;

    // フーリエ逆変換
    inline void Twist_FFT_lvl1(Polynomiallvl1 &res,const PolynomialInFDlvl1 &a){
        fftplvl1.execute_direct_torus32(res.data(),a.data());
    }

    // フーリエ変換
    inline void Twist_IFFT_lvl1(PolynomialInFDlvl1 &res,const Polynomiallvl1 &a){
        fftplvl1.execute_reverse_torus32(res.data(),a.data());
    }


    // 畳み込み乗算
    inline void Poly_Mul_lvl1(Polynomiallvl1 &res,const Polynomiallvl1 &a,const lwekeylvl1 &b){
        
        // 多項式a[X]をフーリエ変換     a[x]->ffta
        PolynomialInFDlvl1 ffta;    // array<double,DEF_N>
        Twist_IFFT_lvl1(ffta,a);

        // 多項式b[X]をフーリエ変換     b[x]->fftb
        PolynomialInFDlvl1 fftb;
        Twist_IFFT_lvl1(fftb,b);

        // フーリエ変換した結果の要素ごとの積をとったものの
        Mul_In_FD<DEF_N>(ffta,ffta,fftb);     //res,ffta,fftb;

        // 逆変換は、入力の畳み込みになっている     MulInFD の res を逆変換 ffta -> a[x]/x^n + 1
        Twist_FFT_lvl1(res,ffta);

    }


}// myTFHE