#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{
    
    // HomNAND
    void HomNAND(TLWElvl0 &res_tlwe,TLWElvl0 &tlweA,TLWElvl0 &tlweB,const GateKey &gk){

        TLWElvl0 tlwe;
        for(int i=0;i<DEF_n;i++){
            tlwe[i] = -tlweA[i] -tlweB[i];
        }
        tlwe[DEF_n] = DEF_myu - tlweA[DEF_n] -tlweB[DEF_n];

        // gatebootstrapping
        TLWElvl1 tlwe1;
        gatebootstrapping_tlwe_to_tlwe(tlwe1,tlwe,gk);

        // identity key switching
        Id_Key_Switch(res_tlwe,tlwe1,gk);
    }

    void HomAND(TLWElvl0 &res_tlwe,TLWElvl0 &tlweA,TLWElvl0 &tlweB,const GateKey &gk){

        TLWElvl0 tlwe;
        HomNAND(tlwe,tlweA,tlweB,gk);

        HomNAND(res_tlwe,tlwe,tlwe,gk);

    }

    void HomOR(TLWElvl0 &res_tlwe,TLWElvl0 &tlweA,TLWElvl0 &tlweB,const GateKey &gk){
        TLWElvl0 tlweAA;
        HomNAND(tlweAA,tlweA,tlweA,gk);

        TLWElvl0 tlweBB;
        HomNAND(tlweBB,tlweB,tlweB,gk);

        HomNAND(res_tlwe,tlweAA,tlweBB,gk);

    }

    void HomNOR(TLWElvl0 &res_tlwe,TLWElvl0 &tlweA,TLWElvl0 &tlweB,const GateKey &gk){

        TLWElvl0 tlwe;
        HomOR(tlwe,tlweA,tlweB,gk);
        HomNAND(res_tlwe,tlwe,tlwe,gk);


    }

} // myTFHE