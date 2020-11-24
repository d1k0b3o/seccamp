// Deterministic Weighted Finite Automata

#include<../include/params.hpp>
#include<../include/trgsw.hpp>


namespace myTFHE{

    // C ext_pro [(a1[x],b1[x])-(a0[x],b0[x])] + (a0[x],b0[x])

    void CMUX_lvl1(TRLWElvl1 &res, const TRGSWFFTlvl1 &cs, TRLWElvl1 &c1, TRLWElvl1 &c0){

        // [(a1[x],b1[x])-(a0[x],b0[x])]
        for(int i=0;i<DEF_N;i++){
            // a1[x] - a0[x]
            res[0][i] = c1[0][i] - c0[0][i];
            
            // b1[x] - b0[x]
            res[1][i] = c1[1][i] - c0[1][i];
        }

        // C ext_pro [(a1[x],b1[x])-(a0[x],b0[x])]

        trgsw_External_Product_lvl1(res,res,cs);

        // C ext_pro [(a1[x],b1[x])-(a0[x],b0[x])] + (a0[x],b0[x])

        for(int i=0;i<DEF_N;i++){
            // 
            res[0][i] += c0[0][i];
            res[1][i] += c0[1][i];
        }

    }

}