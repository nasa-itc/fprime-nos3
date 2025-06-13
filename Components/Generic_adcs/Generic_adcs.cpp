// ======================================================================
// \title  Generic_adcs.cpp
// \author jstar
// \brief  cpp file for Generic_adcs component implementation class
// ======================================================================

#include "Components/Generic_adcs/Generic_adcs.hpp"
#include "FpConfig.hpp"

#include <math.h>

namespace Components {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  Generic_adcs ::
    Generic_adcs(const char* const compName) :
      Generic_adcsComponentBase(compName)
  {
    ingest_init(&DIPacket.Payload);
    init_ad_and_ac(&ADPacket.Payload, &GNCPacket.Payload, &ACSPacket.Payload);
    init_output(&DOPacket.Payload);
    
  }

  Generic_adcs ::
    ~Generic_adcs()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_adcs ::
    Placeholder_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->tlmWrite_PH(0);

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  void Generic_adcs :: ingest_init(Generic_ADCS_DI_Tlm_Payload_t *DI)
  {
    //hardcoded instead of from the cfg

    //mag
    DI->Mag.qbs[0] = 0.0;
    DI->Mag.qbs[1] = 0.0;
    DI->Mag.qbs[2] = 0.0;
    DI->Mag.qbs[3] = 1.0;

    //fss
    DI->Fss.qbs[0] = 0.0;
    DI->Fss.qbs[1] = -0.7071;
    DI->Fss.qbs[2] = 0.0;
    DI->Fss.qbs[3] = 0.7071;

    //css
    DI->Css.Sensor[0].axis[0] = 1.0;
    DI->Css.Sensor[0].axis[1] = 0.0;
    DI->Css.Sensor[0].axis[2] = 0.0;
    DI->Css.Sensor[0].scale   = 0.001;

    DI->Css.Sensor[1].axis[0] = -1.0;
    DI->Css.Sensor[1].axis[1] = 0.0;
    DI->Css.Sensor[1].axis[2] = 0.0;
    DI->Css.Sensor[1].scale   = 0.001;

    DI->Css.Sensor[2].axis[0] = 0.0;
    DI->Css.Sensor[2].axis[1] = 1.0;
    DI->Css.Sensor[2].axis[2] = 0.0;
    DI->Css.Sensor[2].scale   = 0.001;

    DI->Css.Sensor[3].axis[0] = 0.0;
    DI->Css.Sensor[3].axis[1] = -1.0;
    DI->Css.Sensor[3].axis[2] = 0.0;
    DI->Css.Sensor[3].scale   = 0.001;

    DI->Css.Sensor[4].axis[0] = 0.0;
    DI->Css.Sensor[4].axis[1] = 0.0;
    DI->Css.Sensor[4].axis[2] = 1.0;
    DI->Css.Sensor[4].scale   = 0.001;

    DI->Css.Sensor[5].axis[0] = 0.0;
    DI->Css.Sensor[5].axis[1] = 0.0;
    DI->Css.Sensor[5].axis[2] = -1.0;
    DI->Css.Sensor[5].scale   = 0.001;

    //imu
    DI->Imu.qbs[0] = 0.0;
    DI->Imu.qbs[1] = 0.0;
    DI->Imu.qbs[2] = 0.0;
    DI->Imu.qbs[3] = 1.0;

    DI->Imu.pos[0] = 0.5;
    DI->Imu.pos[1] = 1.0;
    DI->Imu.pos[2] = 1.5;


    //rw
    double h_max[3] = {0.0, 0.0, 0.0};
    DI->Rw.whl_axis[0][0] =1.0;
    DI->Rw.whl_axis[0][1] =0.0;
    DI->Rw.whl_axis[0][2] =0.0;
    h_max[0] =0.01082;

    DI->Rw.whl_axis[1][0] =0.0;
    DI->Rw.whl_axis[1][1] =1.0;
    DI->Rw.whl_axis[1][2] =0.0;
    h_max[1] =0.01082;

    DI->Rw.whl_axis[2][0] =0.0;
    DI->Rw.whl_axis[2][1] =0.0;
    DI->Rw.whl_axis[2][2] =1.0;
    h_max[2] =0.01082;

    double H_in_body[3] = {0.0, 0.0, 0.0};
    for(int i = 0; i < 3; i++)
    {
      DI->Rw.H_maxB[i] = 0.0;
    }

    for (int whl = 0; whl < 3; whl++)
    {
        SxV(h_max[whl], DI->Rw.whl_axis[whl], H_in_body);
        for (int i = 0; i < 3; i++)
        {
            DI->Rw.H_maxB[i] += H_in_body[i];
        }
    }


    //st
    DI->St.qbs[0] = 0.0;
    DI->St.qbs[1] = 0.0;
    DI->St.qbs[2] = 0.0;
    DI->St.qbs[3] = 1.0;
  }

  void Generic_adcs :: init_ad_and_ac(Generic_ADCS_AD_Tlm_Payload_t *AD,
                                      Generic_ADCS_GNC_Tlm_Payload_t *GNC,
                                      Generic_ADCS_AC_Tlm_Payload_t  *ACS)
  {
    //Hardcode instead of reading from the cfg

    AD->Imu.alpha = 0.0;

    GNC->DT = 0.1;
    GNC->MaxMcmd = 1.42;

    ACS->Bdot.b_range = 4.096E-6;
    ACS->Bdot.Kb = 200.0;

    ACS->Sunsafe.Kp[0] = 0.0047;
    ACS->Sunsafe.Kp[1] = 0.0047;
    ACS->Sunsafe.Kp[2] = 0.0047;
    ACS->Sunsafe.Kr[0] = 0.1329;
    ACS->Sunsafe.Kr[1] = 0.1329;
    ACS->Sunsafe.Kr[2] = 0.1329;

    ACS->Sunsafe.sside[0] = 1.0;
    ACS->Sunsafe.sside[1] = 0.0;
    ACS->Sunsafe.sside[2] = 0.0;
    ACS->Sunsafe.vmax = 0.1;
    ACS->Sunsafe.cmd_wbn[0] = 0.0;
    ACS->Sunsafe.cmd_wbn[1] = 0.0;
    ACS->Sunsafe.cmd_wbn[2] = 0.0;

    for(int i = 0; i < 3; i++)
    {
      ACS->Sunsafe.therr[i] = ACS->Sunsafe.werr[i] = ACS->Sunsafe.Tcmd[i] = 0;
    }

    //skipped inertial

    GNC->Hmgmt.Kb = 1.0;
    GNC->Hmgmt.b_range = 4.096E-6;
    GNC->Hmgmt.loFrac = 0.1;
    GNC->Hmgmt.hiFrac = 0.5;
  }

  void Generic_adcs :: init_output(Generic_ADCS_DO_Tlm_Payload_t *DO)
  {
    DO->Trq.qba[0] = 0.0;
    DO->Trq.qba[1] = 0.0;
    DO->Trq.qba[2] = 0.0;
    DO->Trq.qba[3] = 1.0;

    DO->Rw.axis[0][0] = 1.0;
    DO->Rw.axis[0][1] = 0.0;
    DO->Rw.axis[0][2] = 0.0;

    DO->Rw.axis[1][0] = 0.0;
    DO->Rw.axis[1][1] = 1.0;
    DO->Rw.axis[1][2] = 0.0;

    DO->Rw.axis[2][0] = 0.0;
    DO->Rw.axis[2][1] = 0.0;
    DO->Rw.axis[2][2] = 1.0;
  }

  void Generic_adcs :: ingest_mag(I32 MagIntX, I32 MagIntY, I32 MagIntZ, Generic_ADCS_DI_Mag_Tlm_Payload_t *Mag)
  {
    double bvs[3] = {(double)MagIntX, (double)MagIntY, (double)MagIntZ};

    QxV(Mag->qbs, bvs, Mag->bvb);

    Mag->bvb[0] *= NANO;
    Mag->bvb[1] *= NANO;
    Mag->bvb[2] *= NANO;
  }

  void Generic_adcs :: ingest_fss(U32 Alpha, U32 Beta, U8 Error, Generic_ADCS_DI_Fss_Tlm_Payload_t *Fss)
  {
    Fss->valid = 0;
    if(Error == 0) Fss->valid = 1;

    if(Fss->valid == 1)
    {
      double svs[3];
      double ta = tan(Alpha);
      double tb = tan(Beta);
      svs[2] = 1.0 / sqrt(1 + ta*tb + tb*tb);
      svs[0] = svs[2] * ta;
      svs[1] = svs[2] * tb;
      QxV(Fss->qbs, svs, Fss->svb);
    }
    else
    {
      Fss->svb[0] = 0.0;
      Fss->svb[1] = 0.0;
      Fss->svb[2] = 0.0;
    }
  }

  void Generic_adcs :: ingest_css(U16 ADCV0, U16 ADCV1, U16 ADCV2, U16 ADCV3, U16 ADCV4, U16 ADCV5, Generic_ADCS_DI_Css_Tlm_Payload_t *Css)
  {
    Css->Sensor[0].percenton      = ADCV0 * Css->Sensor[0].scale;
    Css->Sensor[1].percenton      = ADCV1 * Css->Sensor[1].scale;
    Css->Sensor[2].percenton      = ADCV2 * Css->Sensor[2].scale;
    Css->Sensor[3].percenton      = ADCV3 * Css->Sensor[3].scale;
    Css->Sensor[4].percenton      = ADCV4 * Css->Sensor[4].scale;
    Css->Sensor[5].percenton      = ADCV5 * Css->Sensor[5].scale;

    double svb[3] = {0.0, 0.0, 0.0};
    for (int i = 0; i < 6; i++)
    {
        svb[0] += Css->Sensor[i].axis[0] * Css->Sensor[i].percenton;
        svb[1] += Css->Sensor[i].axis[1] * Css->Sensor[i].percenton;
        svb[2] += Css->Sensor[i].axis[2] * Css->Sensor[i].percenton;
    }
    UNITV(svb);

    Css->svb[0] = svb[0];
    Css->svb[1] = svb[1];
    Css->svb[2] = svb[2];
    if (MAGV(svb) > 0.0)
    {
        Css->valid = 1;
    }
    else
    {
        Css->valid = 0;
    }
  }

  void Generic_adcs :: ingest_imu(F32 LinX, F32 LinY, F32 LinZ, F32 AngX, F32 AngY, F32 AngZ, Generic_ADCS_DI_Imu_Tlm_Payload_t *Imu)
  {
    double wsn[3] = {AngX, AngY, AngZ};
    QxV(Imu->qbs, wsn, Imu->wbn);

    double acc[3] = {LinX, LinY, LinZ};
    QxV(Imu->qbs, acc, Imu->acc);
    Imu->valid = 1;
  }

  void Generic_adcs :: ingest_rw(F64 RW0, F64 RW1, F64 RW2, Generic_ADCS_DI_Rw_Tlm_Payload_t *Rw)
  {
    double H_in_body[3] = {0.0, 0.0, 0.0};
    double rwMomentums[3] = {RW0, RW1, RW2};

    for(int i = 0; i < 3; i++)
    {
      Rw->HwhlB[i] = 0.0;
    }
    
    for(int whl = 0; whl < 3; whl++)
    {
      SxV(rwMomentums[whl], Rw->whl_axis[whl], H_in_body);

      for(int i = 0; i < 3; i++)
      {
        Rw->HwhlB[i] += H_in_body[i];
      }
    }
  }

  void Generic_adcs :: ingest_st(F64 Q0, F64 Q1, F64 Q2, F64 Q3, U8 IsValid, Generic_ADCS_DI_St_Tlm_Payload_t *St)
  {
    St->valid = IsValid;
    double q[4] = {Q0, Q1, Q2, Q3};
    QxQ(q, St->qbs, St->q);
  }

}
