#include<vector>
#include<array>
#include<limits>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{
    
    template<typename T = uint32_t, uint32_t N=DEF_N, uint32_t l=DEF_l, uint32_t Bgbit=DEF_Bgbit, T offset>
    inline void Decomposition(array<array<T,N>,2*l> &decvec,const array<array<T,N>,2> &trlwe){

        constexpr T mask = static_cast<T>((1UL << Bgbit) - 1);
        constexpr T halfBg = (1UL << (Bgbit -1));

        for(int j=0;j<N;j++){
            T temp0 = trlwe[0][j] + offset;
            T temp1 = trlwe[1][j] + offset;
            for(int i=0;i<l;i++){
                decvec[i][j]=((temp0 >> (numeric_limits<T>::digits - (i+1)*Bgbit)) & mask) - halfBg;
            }
            for(int i=0;i<l;i++){
                decvec[i+l][j]=((temp1 >> (numeric_limits<T>::digits - (i+1)*Bgbit)) & mask) - halfBg;
            }
        }
        
    }

    constexpr uint32_t offsetgenlvl1(){
        uint32_t offset = 0;
        for(int i=1;i<=DEF_l;i++){
            // 各桁にBg/2を足す
            offset+=DEF_Bg/2 * (1U << (32 - i * DEF_Bgbit));
        }
        return offset;
    }

    inline void Decompositionlvl1(DecomposedTRLWElvl1 &decvec, const TRLWElvl1 &trlwe){
        static constexpr uint32_t offset = offsetgenlvl1();
        Decomposition<uint32_t,DEF_N,DEF_l,DEF_Bgbit,offset>(decvec,trlwe);
    }

    inline void DecompositionFFTlvl1(DecomposedTRLWEInFDlvl1 &decvecfft,const TRLWElvl1 &trlwe);
    {
        DecomposedTRLWElvl1 decvec;
        Decompositionlvl1(decvec,trlwe);
        for(int i=0;i<2*DEF_l;i++){
            TwistIFFTlvl1(decvecfft[i],decvec[i]);
        }
    }

}// myTFHE