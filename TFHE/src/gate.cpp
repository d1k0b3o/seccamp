#include<array>
#include<vector>
#include<../include/params.hpp>
#include<../include/tfhe++.hpp>

namespace myTFHE{
    
    // HomNAND
    void HomNAND(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk){

        TLWElvl0 tlwe;
        for(int i=0;i<=DEF_n;i++){
            tlwe[i] = -tlweA[i] -tlweB[i];
        }
        tlwe[DEF_n] += 1U << 29; //- tlweA[DEF_n] -tlweB[DEF_n];

        // gatebootstrapping
        TLWElvl1 tlwe1;
        gatebootstrapping_tlwe_to_tlwe(tlwe1,tlwe,gk);

        // identity key switching
        Id_Key_Switch(res_tlwe,tlwe1,gk);
    }

    void HomAND(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk){

        // TLWElvl0 tlwe;
        // HomNAND(tlwe,tlweA,tlweB,gk);

        // HomNAND(res_tlwe,tlwe,tlwe,gk);

        TLWElvl0 tlwe;
        for(int i=0;i<=DEF_n;i++){
            tlwe[i]=tlweA[i]+tlweB[i];
        }
        tlwe[DEF_n] -= DEF_myu;
        // gatebootstapping
        TLWElvl1 tlwe1;
        gatebootstrapping_tlwe_to_tlwe(tlwe1,tlwe,gk);

        // identity key switching
        Id_Key_Switch(res_tlwe,tlwe1,gk);

    }

    void HomNOT(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const GateKey &gk){
        TLWElvl0 tlwe;
        for(int i=0;i<=DEF_n;i++){
            tlwe[i]=-tlweA[i]-tlweA[i];
        }
        tlwe[DEF_n] +=DEF_myu;

        TLWElvl1 tlwe1;
        gatebootstrapping_tlwe_to_tlwe(tlwe1,tlwe,gk);
        Id_Key_Switch(res_tlwe,tlwe1,gk);
    }

    void HomOR(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk){
        // TLWElvl0 tlweAA;
        // HomNAND(tlweAA,tlweA,tlweA,gk);

        // TLWElvl0 tlweBB;
        // HomNAND(tlweBB,tlweB,tlweB,gk);

        // HomNAND(res_tlwe,tlweAA,tlweBB,gk);

        TLWElvl0 tlwe;
        for(int i=0;i<=DEF_n;i++){
            tlwe[i]=tlweA[i]+tlweB[i];
        }
        tlwe[DEF_n] += DEF_myu;

        TLWElvl1 tlwe1;
        gatebootstrapping_tlwe_to_tlwe(tlwe1,tlwe,gk);

        Id_Key_Switch(res_tlwe,tlwe1,gk);

    }

    void HomNOR(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk){

        // TLWElvl0 tlwe;
        // HomOR(tlwe,tlweA,tlweB,gk);
        // HomNAND(res_tlwe,tlwe,tlwe,gk);

        
        TLWElvl0 tlwe;
        for(int i=0;i<=DEF_n;i++){
            tlwe[i]=tlweA[i]+tlweB[i];
        }
        tlwe[DEF_n] -= 3*DEF_myu;

        TLWElvl1 tlwe1;
        gatebootstrapping_tlwe_to_tlwe(tlwe1,tlwe,gk);

        Id_Key_Switch(res_tlwe,tlwe1,gk);

    }

    void HomXOR(TLWElvl0 &res_tlwe,const TLWElvl0 &tlweA,const TLWElvl0 &tlweB,const GateKey &gk){

        // TLWElvl0 NA;
        // HomNOT(NA,tlweA,gk);

        // TLWElvl0 NAB;
        // HomAND(NAB,NA,tlweB,gk);

        // TLWElvl0 NB;
        // HomNOT(NB,tlweB,gk);

        // TLWElvl0 NBA;
        // HomAND(NBA,NB,tlweA,gk);

        // HomOR(res_tlwe,NAB,NBA,gk);

        // TLWElvl0 AorB;
        // HomOR(AorB,tlweA,tlweB,gk);

        // TLWElvl0 AandB;
        // HomAND(AandB,tlweA,tlweB,gk);

        // TLWElvl0 NAB;
        // HomNOT(NAB,AandB,gk);

        // HomAND(res_tlwe,NAB,AandB,gk);

        TLWElvl0 tlwe;
        for(int i=0;i<=DEF_n;i++){
            tlwe[i]=2*(tlweA[i]+tlweB[i]);
        }
        tlwe[DEF_n] += DEF_myu;

        TLWElvl1 tlwe1;
        gatebootstrapping_tlwe_to_tlwe(tlwe1,tlwe,gk);

        Id_Key_Switch(res_tlwe,tlwe1,gk);
    }

} // myTFHE