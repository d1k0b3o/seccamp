#include<vector>
#include<array>
#include<limits>
#include<iostream>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>
#include<../include/mulfft.hpp>
#include<../include/common.hpp>
#include<../include/trlwe.hpp>


namespace myTFHE{
    using namespace std;

    // trgsw enc
    inline TRGSWlvl1 trgsw_Enc_lvl1(int32_t p, double abk, lwekeylvl1 &key){
        
        // trgsw の平文のl桁分解
        array<uint32_t,DEF_l> h;
        for(int i=0;i<DEF_l;i++) h[i]=1U<<(32-(i+1)*DEF_Bgbit);

        // array<TRLWElvl1,2*DEF_l>
        // array<array<array<uint32_t,DEF_N>,2>,2*DEF_l>
        // ((2*l) x 2 x N)
        TRGSWlvl1 trgsw;

        // 零行列生成
        for(TRLWElvl1 &trlwe_zero : trgsw) trlwe_zero=trlwe_Enc_Zero_lvl1(abk,key);

        // 零行列加算
        for(int i=0;i<DEF_l;i++){ 
            trgsw[i][0][0] += static_cast<uint32_t>(p)*h[i];
            trgsw[i+DEF_l][1][0] += static_cast<uint32_t>(p)*h[i];
        }
        return trgsw;
    }

    // trgsw fft 
    TRGSWFFTlvl1 trgsw_fft_Enc_lvl1(int32_t p, double abk, lwekeylvl1 &key){
        
        // 0の暗号文
        TRGSWlvl1 trgsw = trgsw_Enc_lvl1(p,abk,key);

        //　trgswfft の型定義
        TRGSWFFTlvl1 trgswfft;

        for(int i=0;i<2*DEF_l;i++){
            for(int j=0;j<2;j++){
                // trgsw -> trgswfft  FFT
                Twist_IFFT_lvl1(trgswfft[i][j],trgsw[i][j]);
            }
        }
        return trgswfft;


    }

    // offset Decomposition
    template<typename T = uint32_t, uint32_t N=DEF_N, uint32_t l=DEF_l, uint32_t Bgbit=DEF_Bgbit, T offset>
    inline void Decomposition(array<array<T,N>,2*l> &decvec,const array<array<T,N>,2> &trlwe){

        constexpr T mask = static_cast<T>((1UL << Bgbit) - 1);
        constexpr T halfBg = (1UL << (Bgbit -1));

        for(int j=0;j<N;j++){
            // trlwe の各値に Bg/2 足して、Bg/2 ずらす
            // a[x]
            T temp0 = trlwe[0][j] + offset;     // trlwe {a[x],b[x]} の　a[x] 0~l-1
            
            // b[x]
            T temp1 = trlwe[1][j] + offset;     // trlwe {a[x],b[x]} の　b[x] l~2*l-1

            // a[x]
            for(int i=0;i<l;i++){
                decvec[i][j]=((temp0 >> (32- (i+1)*Bgbit)) & mask) - halfBg;
            }

            // b[x]
            for(int i=0;i<l;i++){
                decvec[i+l][j]=((temp1 >> (32 - (i+1)*Bgbit)) & mask) - halfBg;
            }
        }
    }

    constexpr uint32_t offset_gen_lvl1(){
        // offset = 000000 000000 000000 000000 000000 00 
        uint32_t offset = 0;
        
        // DEF_Bg = (64)_10 = (1000000)_2
        // DEF_Bg/2= (32)_10 = (10000)_2
        // i=1
        // offset = 

        for(int i=0;i<DEF_l;i++){
            // 各桁にBg/2を足すために、それぞれの桁にBg/2 を用意する
            offset+=DEF_Bg/2 * (1U << (32 - (i+1) * DEF_Bgbit));
        }
        
        return offset;
    }

    // Naive Decomposition
    template<typename T = uint32_t, uint32_t N=DEF_N, uint32_t l=DEF_l, uint32_t Bgbit=DEF_Bgbit >
    inline void myDecomposition(array<array<T,N>,2*l> &decvec,const array<array<T,N>,2> &trlwe){
        
        constexpr T mask = static_cast<T>(1UL << Bgbit)-1;
        constexpr T halfBg = (1UL << (Bgbit-1));

        for(int i=1;i<=l;i++){
            for(int j=0;i<N;j++){
                // trlwe の l桁分解
                // a[x] の l桁分解
                decvec[i][j]= (trlwe[0][j]>>(numeric_limits<T>::digits-Bgbit*i)) & mask;
                // b[x] の l桁分解
                decvec[i+l][j]= (trlwe[1][j]>>(numeric_limits<T>::digits-Bgbit*i)) & mask;
            }
        }
        // l桁目からみて、その桁がBg/2より大きければ一つ上の桁に繰り上げる
        for(int i=l;i>0;i--){
            for(int j=0;j<N;j++){
                // 繰り上げ
                // a[x]

                if(decvec[i][j] >= halfBg){
                    decvec[i][j] - DEF_Bg;
                    decvec[i-1][j] +=1;
                }else{ 
                    //
                }
                // b[x]
                if(decvec[i+l][j] >= halfBg){
                    decvec[i+l][j] - DEF_Bg;
                    decvec[i+l-1][j] +=1; 
                }else{
                    //
                }

            }
        }
    }

    inline void Decomposition_lvl1(DecomposedTRLWElvl1 &decvec, const TRLWElvl1 &trlwe){
        // offset_ver
            static constexpr uint32_t offset = offset_gen_lvl1();
            Decomposition<uint32_t,DEF_N,DEF_l,DEF_Bgbit,offset>(decvec,trlwe);
        
        // // naive_ver
        //     myDecomposition<uint32_t,DEF_N,DEF_l,DEF_Bgbit>(decvec,trlwe);
    }

    // decomposition を fft で計算するために 
    inline void Decomposition_FFT_lvl1(DecomposedTRLWEInFDlvl1 &decvecfft,const TRLWElvl1 &trlwe)
    {
        // Decompostion後のTRLWE
        // array<array<uint32_t,DEF_N>,2*DEF_l>
        DecomposedTRLWElvl1 decvec;        

        // "trlwe" をDecompostionして結果を "decvec" に
        Decomposition_lvl1(decvec,trlwe);

        // 各桁の多項式を
        for(int i=0;i<2*DEF_l;i++){
            // フーリエ変換　decvec -> decvecfft
            Twist_IFFT_lvl1(decvecfft[i],decvec[i]);
        }
    }

    // External Product lvl1
    // trgswfft は既にフーリエ変換された状態
    // trlwe -> decvecfft, restrlwefft = Mul(decvecfft,trgswfft), restrlwefft = FMA(decvecfft,trgswfft), restrlwefft -> res  
    void trgsw_External_Product_lvl1(TRLWElvl1 &res, const TRLWElvl1 &trlwe, const TRGSWFFTlvl1 &trgswfft){

        // Decomposition した trlwe をフーリエ変換したもの
        // array<array<double,DEF_N>,2*DEF_l>
        DecomposedTRLWEInFDlvl1 decvecfft;

        // trlwe を　Decomposition してフーリエ変換　trlwe -> decvecfft
        Decomposition_FFT_lvl1(decvecfft,trlwe);

        // 返す res のフーリエ変換してある状態
        // array<array<double,DEF_N>,2>
        TRLWEInFDlvl1 restrlwefft;

        // TRLWEとTRGSWの多項式乗算
        Mul_In_FD<DEF_N> (restrlwefft[0],decvecfft[0],trgswfft[0][0]);
        Mul_In_FD<DEF_N> (restrlwefft[1],decvecfft[0],trgswfft[0][1]);

        // 積和
        for(int i=1;i<2*DEF_l;i++){
            FMA_In_FD<DEF_N> (restrlwefft[0],decvecfft[i],trgswfft[i][0]);
            FMA_In_FD<DEF_N> (restrlwefft[1],decvecfft[i],trgswfft[i][1]);
        }

        // フーリエ逆変換
        // restrlwefft -> res
        Twist_FFT_lvl1(res[0],restrlwefft[0]);
        Twist_FFT_lvl1(res[1],restrlwefft[1]);
    }



}// myTFHE