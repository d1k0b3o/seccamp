/*

*/

#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{

    void gen_Key_Switching_Key(KeySwitchingKey &ksk, const lwekeylvl1 &keylvl1, const lwekeylvl0 &keylvl0){

        uint32_t base = (1 << DEF_basebit);

        for(int i=0;i<DEF_N;i++){
            for(int j=0;j<DEF_tt;j++){
                for(int k=0;k<base-1;k++){
                    uint32_t in_M = (k+1)*keylvl1[i]*(1U << (32-DEF_basebit*(j+1)));
                    ksk[i][j][k] = tlwe_Enc_lvl0(in_M,DEF_alpha,keylvl0);
                }
            }
        }
    }

    void Id_Key_Switch(TLWElvl0 &res_tlwe0,const TLWElvl1 tlwe1,const KeySwitchingKey &ksk){
        
        // prec_offset
        const uint32_t prec_offset = 1U << (32 - (1+DEF_basebit*DEF_tt));
        // mask
        const uint32_t mask = (1U << DEF_basebit) -1;

        for(int i=0;i<DEF_n;i++) res_tlwe0[i]=0;
        res_tlwe0[DEF_n] = tlwe1[DEF_N];

        for(int i=0; i<DEF_N ; i++){
            // Torus -> integer
            const uint32_t a_bar = tlwe1[i] + prec_offset;
            
            for(int j=0; j<DEF_tt ; j++){
                uint32_t k =(a_bar >> (32 - (j+1)*DEF_basebit)) & mask;

                if(k!=0){
                    for(int l=0;l<=DEF_n;l++){
                        res_tlwe0[l] -= ksk[i][j][k-1][l];
                    }
                }
            }
        }
    }

}