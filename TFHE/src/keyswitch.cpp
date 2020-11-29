/*

*/

#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{

    TLWElvl0 Id_Key_Switch(TLWElvl0 &res_tlwe0,const TLWElvl1 tlwe1){
        res_tlwe0[DEF_n] = tlwe1[DEF_N];

        // prec_offset
        uint32_t prec_offset = 1U << (32 - (1+DEF_basebit));

        for(int i=0; i<DEF_N ; i++){
            // Torus -> integer
            res_tlwe0[i] = tlwe1[i] + prec_offset;
            
            for(int j=0; j<t ; j++){
                uint32_t (res_tlwe0[i] >> (32 - (j+1)*DEF_basebit)) & (2)
            }


        }
    }

}