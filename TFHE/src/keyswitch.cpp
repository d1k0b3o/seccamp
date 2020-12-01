/*

*/

#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{

    void gen_Key_Switching_Key(KeySwitchingKey &ksk, const lwekeylvl1 &keylvl1, const lwekeylvl0 &keylvl0){

        const uint32_t mask = (1U << DEF_basebit) -1;
        for(int i=0;i<DEF_N;i++){
            for(int j=0;j<DEF_t;j++){
                for(int k=1;k<mask;k++){
                    ksk[i][j][k] = tlwe_Enc_lvl0(k*keylvl1[i]*(1U << (32-(DEF_basebit)*(j+1))),DEF_alpha,keylvl0);
                }
            }
        }
    }

    void Id_Key_Switch(TLWElvl0 &res_tlwe0,const TLWElvl1 tlwe1,const KeySwitchingKey &ksk){
        res_tlwe0[DEF_n] = tlwe1[DEF_N];

        // prec_offset
        const uint32_t prec_offset = 1U << (32 - (1+DEF_basebit));
        // mask
        const uint32_t mask = (1U << DEF_basebit) -1;

        for(int i=0;i<DEF_n;i++) res_tlwe0[i]=0;

        for(int i=0; i<DEF_N ; i++){
            // Torus -> integer
            uint32_t a_bar = tlwe1[i] + prec_offset;
            
            for(int j=0; j<DEF_t ; j++){
                uint32_t k =(a_bar >> (32 - (j+1)*DEF_basebit)) & (1 << DEF_basebit -1);

                if(k){
                    res_tlwe0[i] -= ksk[i][j][k][i];
                    res_tlwe0[DEF_n] = ksk[i][j][k][DEF_n];
                }
            }
        }
    }

}