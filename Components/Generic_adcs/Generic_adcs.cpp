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
    init_adac(&ADPacket.Payload, &GNCPacket.Payload, &ACSPacket.Payload);
    init_output(&DOPacket.Payload);
    
  }

  Generic_adcs ::
    ~Generic_adcs()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void Generic_adcs :: IMUin_handler(NATIVE_INT_TYPE portNum, F32 XLin, F32 YLin, F32 ZLin, F32 XAng, F32 YAng, F32 ZAng)
  {
    ingest_imu(XLin, YLin, ZLin, XAng, YAng, ZAng, &DIPacket.Payload.Imu);
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

  void Generic_adcs :: init_adac(Generic_ADCS_AD_Tlm_Payload_t *AD,
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

    for(int i = 0; i < 3; i++) CurrentMtb[i] = {1, 0};
    for(int i = 0; i < 3; i++) CurrentRw[i] = 0;
  }

  void Generic_adcs :: ingest_mag(I32 MagIntX, I32 MagIntY, I32 MagIntZ, Generic_ADCS_DI_Mag_Tlm_Payload_t *Mag)
  {
    double bvs[3] = {(double)MagIntX, (double)MagIntY, (double)MagIntZ};

    QxV(Mag->qbs, bvs, Mag->bvb);

    Mag->bvb[0] *= NANO;
    Mag->bvb[1] *= NANO;
    Mag->bvb[2] *= NANO;

    this->tlmWrite_ingestMagCount(++ingestMagCount);
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

    this->tlmWrite_ingestFSSCount(++ingestFSSCount);
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

    this->tlmWrite_ingestCSSCount(++ingestCSSCount);
  }

  void Generic_adcs :: ingest_imu(F32 LinX, F32 LinY, F32 LinZ, F32 AngX, F32 AngY, F32 AngZ, Generic_ADCS_DI_Imu_Tlm_Payload_t *Imu)
  {
    double wsn[3] = {AngX, AngY, AngZ};
    QxV(Imu->qbs, wsn, Imu->wbn);

    double acc[3] = {LinX, LinY, LinZ};
    QxV(Imu->qbs, acc, Imu->acc);
    Imu->valid = 1;

    this->tlmWrite_ingestIMUCount(++ingestIMUCount);
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

    this->tlmWrite_ingestRWCount(++ingestRWCount);
  }

  void Generic_adcs :: ingest_st(F64 Q0, F64 Q1, F64 Q2, F64 Q3, U8 IsValid, Generic_ADCS_DI_St_Tlm_Payload_t *St)
  {
    St->valid = IsValid;
    double q[4] = {Q0, Q1, Q2, Q3};
    QxQ(q, St->qbs, St->q);

    this->tlmWrite_ingestSTCount(++ingestSTCount);
  }

  void Generic_adcs :: exec_adac(const Generic_ADCS_DI_Tlm_Payload_t *DI,
                                 Generic_ADCS_AD_Tlm_Payload_t       *AD,
                                 Generic_ADCS_GNC_Tlm_Payload_t      *GNC,
                                 Generic_ADCS_AC_Tlm_Payload_t       *ACS)
  {
    AD_imu(&DI->Imu, &AD->Imu);
    AD_mag(&DI->Mag, &AD->Mag);
    AD_sol(&DI->Fss, &DI->Css, &AD->Sol);

    AD_to_GNC(AD, GNC);

    for (int i = 0; i < 3; i++)
        GNC->HwhlB[i] = DI->Rw.HwhlB[i];
    for (int i = 0; i < 3; i++)
        GNC->HwhlMaxB[i] = DI->Rw.H_maxB[i];

    switch (GNC->Mode)
    {
        case BDOT_MODE:
            AC_bdot(GNC, &ACS->Bdot);
            break;

        case SUNSAFE_MODE:
            AC_sunsafe(GNC, &ACS->Sunsafe);
            break;

        case PASSIVE_MODE:
        default:
            for (int i = 0; i < 3; i++)
            {
                GNC->Mcmd[i] = 0.0;
                GNC->Tcmd[i] = 0.0;
            }
            break;
    }
  }

  void Generic_adcs :: AD_imu(const Generic_ADCS_DI_Imu_Tlm_Payload_t *DI_IMU, Generic_ADCS_AD_Imu_Tlm_Payload_t *AD_IMU)
  {
      if (DI_IMU->valid)
      {
          AD_IMU->valid = 1;
          for (int i = 0; i < 3; i++)
          {
              AD_IMU->acc[i] = DI_IMU->acc[i];
          }

          if (AD_IMU->init == 0)
          {
              for (int i = 0; i < 3; i++)
              {
                  AD_IMU->wbn[i] = DI_IMU->wbn[i];
              }
              AD_IMU->init = 1;
          }
          else
          {
              for (int i = 0; i < 3; i++)
              {
                  AD_IMU->wbn[i] = AD_IMU->alpha * AD_IMU->wbn_prev[i] + (1 - AD_IMU->alpha) * DI_IMU->wbn[i];
              }
          }
          for (int i = 0; i < 3; i++)
          {
              AD_IMU->wbn_prev[i] = AD_IMU->wbn[i];
          }
      }
      else
      {
          AD_IMU->valid = 0;
      }
  }

  void Generic_adcs :: AD_mag(const Generic_ADCS_DI_Mag_Tlm_Payload_t *DI_Mag, Generic_ADCS_AD_Mag_Tlm_Payload_t *AD_Mag)
  {
      /* AD very simple for magnetometer... there is only one mag and no fusion with anything else */
      for (int i = 0; i < 3; i++)
      {
          AD_Mag->bvb[i] = DI_Mag->bvb[i];
      }
  }

  void Generic_adcs :: AD_sol(const Generic_ADCS_DI_Fss_Tlm_Payload_t *DI_Fss, const Generic_ADCS_DI_Css_Tlm_Payload_t *DI_Css,
                   Generic_ADCS_AD_Sol_Tlm_Payload_t *AD_Sol)
  {
      if (DI_Fss->valid == 1)
      {
          AD_Sol->SunValid = 1;
          AD_Sol->FssValid = 1;
          AD_Sol->svb[0]   = DI_Fss->svb[0];
          AD_Sol->svb[1]   = DI_Fss->svb[1];
          AD_Sol->svb[2]   = DI_Fss->svb[2];
      }
      else if (DI_Css->valid == 1)
      {
          AD_Sol->SunValid = 1;
          AD_Sol->FssValid = 0;
          AD_Sol->svb[0]   = DI_Css->svb[0];
          AD_Sol->svb[1]   = DI_Css->svb[1];
          AD_Sol->svb[2]   = DI_Css->svb[2];
      }
      else
      {
          AD_Sol->SunValid = 0;
          AD_Sol->FssValid = 0;
          AD_Sol->svb[0]   = 0.0;
          AD_Sol->svb[1]   = 0.0;
          AD_Sol->svb[2]   = 0.0;
      }
  }

  void Generic_adcs :: AD_to_GNC(const Generic_ADCS_AD_Tlm_Payload_t *AD, Generic_ADCS_GNC_Tlm_Payload_t *GNC)
  {
      for (int i = 0; i < 3; i++)
      {
          GNC->bvb[i] = AD->Mag.bvb[i];
          GNC->svb[i] = AD->Sol.svb[i];
          GNC->wbn[i] = AD->Imu.wbn[i];
      }
      GNC->SunValid = AD->Sol.SunValid;
  }

  void Generic_adcs :: AC_bdot(Generic_ADCS_GNC_Tlm_Payload_t *GNC, Generic_ADCS_AC_Bdot_Tlm_t *ACS)
  {
      /* apply control only if b-field is in range */
      if (MAGV(GNC->bvb) > ACS->b_range)
      {
          for (int i = 0; i < 3; i++)
          {
              /* backward difference b-field derivative */
              ACS->bdot[i] = (GNC->bvb[i] - ACS->bold[i]) / GNC->DT;
              /* store old b-field */
              ACS->bold[i] = GNC->bvb[i];
              /* traditional b-dot algorithm */
              GNC->Mcmd[i] = -ACS->Kb * ACS->bdot[i] / MAGV(GNC->bvb);
              /* ensure wheels disabled */
              GNC->Tcmd[i] = 0.0;
          }
      }
      else
      {
          for (int i = 0; i < 3; i++)
          {
              GNC->Mcmd[i] = 0.0;
              GNC->Tcmd[i] = 0.0;
          }
      }
  }

  void Generic_adcs :: AC_sunsafe(Generic_ADCS_GNC_Tlm_Payload_t *GNC, Generic_ADCS_AC_Sunsafe_Tlm_t *ACS)
  {
      int    i;
      double u1[3] = {0.0, 0.0, 0.0}, err_b[3] = {0.0, 0.0, 0.0}; /* angle error calculation parameteres */
      double temp_sside[3] = {0.0, 0.0, 0.0};
      double SoS           = 0.0;

      /* .. Check that SS Vector is valid */
      if (GNC->SunValid)
      {

          /* .. Form attitude error signals */
          SoS = VoV(GNC->svb, ACS->sside);
          if ((SoS > (EPS - 1.0)) && (SoS < (1.0 - EPS)))
          {
              VxV(GNC->svb, ACS->sside, ACS->therr);
          }
          else if (SoS >= (1.0 - EPS))
          {
              ACS->therr[0] = 0.0;
              ACS->therr[1] = 0.0;
              ACS->therr[2] = 0.0;
          }
          else
          {
              err_b[0] = ACS->sside[1];
              err_b[1] = ACS->sside[2];
              err_b[2] = ACS->sside[0];
              if (fabs(err_b[0] - err_b[1]) < EPS && fabs(err_b[0] - err_b[2]) < EPS)
              {
                  err_b[0] = -err_b[0];
              }
              VxV(ACS->sside, err_b, temp_sside);
              VxV(GNC->svb, temp_sside, ACS->therr);
          }

          /* .. Closed-loop attitude control - PD Method */
          for (i = 0; i < 3; i++)
          {
              /* Clip attitude slew rates */
              u1[i]        = Limit(ACS->Kp[i] / ACS->Kr[i] * ACS->therr[i], -ACS->vmax, ACS->vmax);
              ACS->werr[i] = GNC->wbn[i] - ACS->cmd_wbn[i];
              ACS->Tcmd[i] = -ACS->Kr[i] * (u1[i] + ACS->werr[i]);
          }

          /* .. Apply Torque Command */
          for (i = 0; i < 3; i++)
          {
              GNC->Tcmd[i] = -ACS->Tcmd[i];
          }
      }

      else
      { /* during eclipse, reduce attitude rates only */

          for (i = 0; i < 3; i++)
          {
              ACS->werr[i] = GNC->wbn[i];
              ACS->Tcmd[i] = -ACS->Kr[i] * ACS->werr[i];
          }
          /* .. Apply Torque Command  */
          for (i = 0; i < 3; i++)
          {
              GNC->Tcmd[i] = -ACS->Tcmd[i];
          }
      }

      if (GNC->HmgmtOn)
      {
          AC_h_mgmt(GNC);
          for (i = 0; i < 3; i++)
          {
              GNC->Mcmd[i] = GNC->Hmgmt.Mcmd[i];
          }
      }
      else
      {
          for (i = 0; i < 3; i++)
          {
              GNC->Mcmd[i] = 0.0;
          }
      }
  }

  void Generic_adcs :: AC_h_mgmt(Generic_ADCS_GNC_Tlm_Payload_t *GNC)
  {

      double Herr[3] = {0.0, 0.0, 0.0};
      double bvb[3]  = {0.0, 0.0, 0.0};
      double HxB[3]  = {0.0, 0.0, 0.0};
      int    i;

      if (MAGV(GNC->bvb) > GNC->Hmgmt.b_range)
      {
          /*Test if any axis needs to be momentum managed*/
          for (i = 0; i < 3; i++)
          {
              if (fabs(GNC->HwhlB[i]) > GNC->Hmgmt.hiFrac * fabs(GNC->HwhlMaxB[i]))
              {
                  GNC->Hmgmt.mm_active[i] = 1;
              }
              if (fabs(GNC->HwhlB[i]) < GNC->Hmgmt.loFrac * fabs(GNC->HwhlMaxB[i]))
              {
                  GNC->Hmgmt.mm_active[i] = 0;
              }
          }
          for (i = 0; i < 3; i++)
          {
              Herr[i] = 0.0;
              if (GNC->Hmgmt.mm_active[i] == 1)
              {
                  Herr[i] = GNC->HwhlB[i];
              }
          }
          CopyUnitV(GNC->bvb, bvb);
          VxV(Herr, bvb, HxB);
          for (i = 0; i < 3; i++)
          {
              GNC->Hmgmt.Mcmd[i] = GNC->Hmgmt.Kb * HxB[i] / MAGV(GNC->bvb);
          }
      }
      else
      {
          for (i = 0; i < 3; i++)
          {
              GNC->Hmgmt.Mcmd[i] = 0.0;
          }
      }
  }

    void Generic_adcs :: output_actuators(Generic_ADCS_GNC_Tlm_Payload_t *GNC, Generic_ADCS_DO_Tlm_Payload_t *DO,
                                        GENERIC_TORQUER_All_Percent_On_cmd_t *MtbPctOnCmd, GENERIC_RW_Cmd_t *RwCmd)
    {
        send_mtb_commands(GNC->Mcmd, &DO->Trq, MtbPctOnCmd);
        send_rw_commands(GNC->Tcmd, &DO->Rw, RwCmd);
    }

    void Generic_adcs :: send_mtb_commands(double Mcmd[3], Generic_ADCS_DO_Trq_TlmPayload_t *DO,
                                           GENERIC_TORQUER_All_Percent_On_cmd_t *MtbPctOnCmd)
    {
        QTxV(DO->qba, Mcmd, DO->Mcmd);

        mcmd_to_percent_direction(DO->Mcmd[0], &MtbPctOnCmd->PercentOn_0, &MtbPctOnCmd->Direction_0);
        mcmd_to_percent_direction(DO->Mcmd[1], &MtbPctOnCmd->PercentOn_1, &MtbPctOnCmd->Direction_1);
        mcmd_to_percent_direction(DO->Mcmd[2], &MtbPctOnCmd->PercentOn_2, &MtbPctOnCmd->Direction_2);
        if ((MtbPctOnCmd->Direction_0 != CurrentMtb[0].Direction) ||
            (MtbPctOnCmd->PercentOn_0 != CurrentMtb[0].PercentOn) ||
            (MtbPctOnCmd->Direction_1 != CurrentMtb[1].Direction) ||
            (MtbPctOnCmd->PercentOn_1 != CurrentMtb[1].PercentOn) ||
            (MtbPctOnCmd->Direction_2 != CurrentMtb[2].Direction) || (MtbPctOnCmd->PercentOn_2 != CurrentMtb[2].PercentOn))
        {
            //send commands to torquer
            CurrentMtb[0].Direction = MtbPctOnCmd->Direction_0;
            CurrentMtb[0].PercentOn = MtbPctOnCmd->PercentOn_0;
            CurrentMtb[1].Direction = MtbPctOnCmd->Direction_1;
            CurrentMtb[1].PercentOn = MtbPctOnCmd->PercentOn_1;
            CurrentMtb[2].Direction = MtbPctOnCmd->Direction_2;
            CurrentMtb[2].PercentOn = MtbPctOnCmd->PercentOn_2;
        }
    }

    void Generic_adcs :: mcmd_to_percent_direction(double Mcmd, uint8_t *percent, uint8_t *direction)
    {
        double pct = 100.0 * Mcmd / GNCPacket.Payload.MaxMcmd;
        *direction = 1;
        if (pct < 0)
        {
            pct *= -1.0;
            *direction = 0;
        }
        if (pct > 100)
            pct = 100;
        *percent = pct;
    }

    void Generic_adcs :: send_rw_commands(double Tcmd[3], Generic_ADCS_DO_Rw_TlmPayload_t *DO, GENERIC_RW_Cmd_t *RwCmd)
    {
        int16_t torque;
        for (uint8_t i = 0; i < 3; i++)
        {
            DO->Tcmd[i] = Tcmd[i];
            torque      = 10000.0 * VoV(Tcmd, DO->axis[i]); // cmd is in 10^-4 Nm
            if (torque != CurrentRw[i])
            {
                RwCmd->data         = torque;
                RwCmd->wheel_number = i;
                //send commands to RW
                CurrentRw[i] = torque;
            }
        }
    }


}
