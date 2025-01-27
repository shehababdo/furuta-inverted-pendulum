/*
 * File: HIL.c
 *
 * Code generated for Simulink model 'HIL'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu Jan  2 11:09:06 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "HIL.h"
#include "rtwtypes.h"
#include "HIL_private.h"
#include <math.h>
#include "HIL_types.h"
#include "rt_nonfinite.h"
#include <float.h>

/* Block signals (default storage) */
B_HIL_T HIL_B;

/* Block states (default storage) */
DW_HIL_T HIL_DW;

/* Real-time model */
static RT_MODEL_HIL_T HIL_M_;
RT_MODEL_HIL_T *const HIL_M = &HIL_M_;
real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      q = ceil(u1);
    } else {
      q = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != q)) {
      q = fabs(u0 / u1);
      if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void HIL_step(void)
{
  {
    codertarget_arduinobase_inter_T *obj;
    real_T lastTime;
    real_T rtb_Saturation;
    real_T *lastU;
    int32_T rtb_Encoder_0;
    uint8_T tmp;

    /* MATLABSystem: '<S3>/Encoder' */
    if (HIL_DW.obj.SampleTime != HIL_P.Encoder_SampleTime) {
      HIL_DW.obj.SampleTime = HIL_P.Encoder_SampleTime;
    }

    if (HIL_DW.obj.TunablePropsChanged) {
      HIL_DW.obj.TunablePropsChanged = false;
    }

    MW_EncoderRead(HIL_DW.obj.Index, &rtb_Encoder_0);

    /* Gain: '<S3>/rev to degree' incorporates:
     *  DataTypeConversion: '<S3>/Data Type Conversion1'
     *  MATLABSystem: '<S3>/Encoder'
     */
    HIL_B.revtodegree = 8.1818181818181817 / HIL_P.gear_box_ratio * (real_T)
      rtb_Encoder_0;

    /* Gain: '<S6>/Gain1' */
    HIL_B.Gain1 = HIL_P.Gain1_Gain * HIL_B.revtodegree;

    /* Derivative: '<S3>/Derivative' incorporates:
     *  Derivative: '<S4>/Derivative'
     */
    rtb_Saturation = HIL_M->Timing.t[0];
    if ((HIL_DW.TimeStampA >= rtb_Saturation) && (HIL_DW.TimeStampB >=
         rtb_Saturation)) {
      /* DataTypeConversion: '<S3>/Data Type Conversion2' */
      HIL_B.DataTypeConversion2 = 0.0;
    } else {
      lastTime = HIL_DW.TimeStampA;
      lastU = &HIL_DW.LastUAtTimeA;
      if (HIL_DW.TimeStampA < HIL_DW.TimeStampB) {
        if (HIL_DW.TimeStampB < rtb_Saturation) {
          lastTime = HIL_DW.TimeStampB;
          lastU = &HIL_DW.LastUAtTimeB;
        }
      } else if (HIL_DW.TimeStampA >= rtb_Saturation) {
        lastTime = HIL_DW.TimeStampB;
        lastU = &HIL_DW.LastUAtTimeB;
      }

      /* DataTypeConversion: '<S3>/Data Type Conversion2' */
      HIL_B.DataTypeConversion2 = (HIL_B.Gain1 - *lastU) / (rtb_Saturation -
        lastTime);
    }

    /* End of Derivative: '<S3>/Derivative' */

    /* MATLABSystem: '<S4>/MATLAB System' */
    if (HIL_DW.obj_b.SampleTime != HIL_P.MATLABSystem_SampleTime) {
      HIL_DW.obj_b.SampleTime = HIL_P.MATLABSystem_SampleTime;
    }

    /*         %% Define output properties */
    /*  Call: int enc_output(int enc) */
    rtb_Encoder_0 = enc_output(0.0);

    /* Gain: '<S7>/Gain1' incorporates:
     *  DataTypeConversion: '<S4>/Data Type Conversion1'
     *  Gain: '<S4>/rev to degree'
     *  MATLABSystem: '<S4>/MATLAB System'
     */
    HIL_B.Gain1_g = HIL_P.revtodegree_Gain * (real_T)rtb_Encoder_0 *
      HIL_P.Gain1_Gain_h;

    /* Sum: '<S5>/Add' incorporates:
     *  Constant: '<S5>/Pi'
     */
    HIL_B.Add = HIL_B.Gain1_g + HIL_P.Pi_Value;

    /* Switch: '<S8>/Switch' */
    if (HIL_B.Add > HIL_P.Switch_Threshold_g) {
      /* Switch: '<S8>/Switch' incorporates:
       *  Bias: '<S8>/Bias'
       *  Bias: '<S8>/Bias1'
       *  Constant: '<S8>/Constant'
       *  Math: '<S8>/Rem'
       */
      HIL_B.Switch = rt_remd_snf(HIL_B.Add + HIL_P.Bias_Bias_n,
        HIL_P.Constant_Value) + HIL_P.Bias1_Bias_j;
    } else {
      /* Switch: '<S8>/Switch' incorporates:
       *  Bias: '<S8>/Bias2'
       *  Bias: '<S8>/Bias3'
       *  Constant: '<S8>/Constant1'
       *  Math: '<S8>/Rem1'
       */
      HIL_B.Switch = rt_remd_snf(HIL_B.Add + HIL_P.Bias2_Bias_d,
        HIL_P.Constant1_Value) + HIL_P.Bias3_Bias_e;
    }

    /* End of Switch: '<S8>/Switch' */

    /* Derivative: '<S4>/Derivative' */
    if ((HIL_DW.TimeStampA_f >= rtb_Saturation) && (HIL_DW.TimeStampB_e >=
         rtb_Saturation)) {
      /* DataTypeConversion: '<S4>/Data Type Conversion2' */
      HIL_B.DataTypeConversion2_l = 0.0;
    } else {
      lastTime = HIL_DW.TimeStampA_f;
      lastU = &HIL_DW.LastUAtTimeA_b;
      if (HIL_DW.TimeStampA_f < HIL_DW.TimeStampB_e) {
        if (HIL_DW.TimeStampB_e < rtb_Saturation) {
          lastTime = HIL_DW.TimeStampB_e;
          lastU = &HIL_DW.LastUAtTimeB_o;
        }
      } else if (HIL_DW.TimeStampA_f >= rtb_Saturation) {
        lastTime = HIL_DW.TimeStampB_e;
        lastU = &HIL_DW.LastUAtTimeB_o;
      }

      /* DataTypeConversion: '<S4>/Data Type Conversion2' */
      HIL_B.DataTypeConversion2_l = (HIL_B.Gain1_g - *lastU) / (rtb_Saturation -
        lastTime);
    }

    /* DataTypeConversion: '<S3>/Data Type Conversion3' */
    HIL_B.DataTypeConversion3 = HIL_B.Gain1;

    /* Switch: '<S1>/Linearity checker' incorporates:
     *  Abs: '<S1>/Abs'
     *  Switch: '<S9>/Switch'
     */
    if (fabs(HIL_B.Switch) > HIL_P.Linearitychecker_Threshold) {
      /* Switch: '<S1>/Linearity checker' incorporates:
       *  Constant: '<S1>/Constant'
       */
      HIL_B.ControlAction = HIL_P.Constant_Value_m;
    } else {
      if (HIL_B.DataTypeConversion3 > HIL_P.Switch_Threshold) {
        /* Switch: '<S9>/Switch' incorporates:
         *  Bias: '<S9>/Bias'
         *  Bias: '<S9>/Bias1'
         *  Constant: '<S9>/Constant'
         *  Math: '<S9>/Rem'
         */
        rtb_Saturation = rt_remd_snf(HIL_B.DataTypeConversion3 + HIL_P.Bias_Bias,
          HIL_P.Constant_Value_o) + HIL_P.Bias1_Bias;
      } else {
        /* Switch: '<S9>/Switch' incorporates:
         *  Bias: '<S9>/Bias2'
         *  Bias: '<S9>/Bias3'
         *  Constant: '<S9>/Constant1'
         *  Math: '<S9>/Rem1'
         */
        rtb_Saturation = rt_remd_snf(HIL_B.DataTypeConversion3 +
          HIL_P.Bias2_Bias, HIL_P.Constant1_Value_h) + HIL_P.Bias3_Bias;
      }

      /* Switch: '<S1>/Linearity checker' incorporates:
       *  Gain: '<S1>/Gain1'
       *  SignalConversion generated from: '<S1>/Gain1'
       *  Switch: '<S9>/Switch'
       */
      HIL_B.ControlAction = ((-HIL_P.K[0] * rtb_Saturation + -HIL_P.K[1] *
        HIL_B.Switch) + -HIL_P.K[2] * HIL_B.DataTypeConversion2) + -HIL_P.K[3] *
        HIL_B.DataTypeConversion2_l;
    }

    /* End of Switch: '<S1>/Linearity checker' */
    /* Gain: '<S2>/Scaling' */
    HIL_B.Scaling = HIL_P.Scaling_Gain * HIL_B.ControlAction;

    /* Saturate: '<S2>/Saturation' */
    if (HIL_B.Scaling > HIL_P.Saturation_UpperSat) {
      rtb_Saturation = HIL_P.Saturation_UpperSat;
    } else if (HIL_B.Scaling < HIL_P.Saturation_LowerSat) {
      rtb_Saturation = HIL_P.Saturation_LowerSat;
    } else {
      rtb_Saturation = HIL_B.Scaling;
    }

    /* End of Saturate: '<S2>/Saturation' */

    /* Abs: '<S2>/remove any negative pwm sign' */
    HIL_B.pwm = fabs(rtb_Saturation);

    /* MATLABSystem: '<S2>/PWM' */
    obj = &HIL_DW.obj_f;
    obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(6UL);
    if (HIL_B.pwm <= 255.0) {
      lastTime = HIL_B.pwm;
    } else {
      lastTime = 255.0;
    }

    if (!(lastTime >= 0.0)) {
      lastTime = 0.0;
    }

    MW_PWM_SetDutyCycle(HIL_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE, lastTime);

    /* End of MATLABSystem: '<S2>/PWM' */
    /* Switch: '<S2>/Switch1' */
    if (rtb_Saturation >= HIL_P.Switch1_Threshold) {
      /* Switch: '<S2>/Switch1' incorporates:
       *  Constant: '<S2>/Constant'
       */
      HIL_B.Switch1 = HIL_P.Constant_Value_e;
    } else {
      /* Switch: '<S2>/Switch1' incorporates:
       *  Constant: '<S2>/Constant1'
       */
      HIL_B.Switch1 = HIL_P.Constant1_Value_n;
    }

    /* End of Switch: '<S2>/Switch1' */

    /* Logic: '<S2>/NOT' */
    HIL_B.NOT = !(HIL_B.Switch1 != 0.0);

    /* MATLABSystem: '<S2>/Digital Output' */
    writeDigitalPin(7, (uint8_T)HIL_B.NOT);

    /* MATLABSystem: '<S2>/Digital Output1' */
    rtb_Saturation = rt_roundd_snf(HIL_B.Switch1);
    if (rtb_Saturation < 256.0) {
      if (rtb_Saturation >= 0.0) {
        tmp = (uint8_T)rtb_Saturation;
      } else {
        tmp = 0U;
      }
    } else {
      tmp = MAX_uint8_T;
    }

    writeDigitalPin(8, tmp);

    /* End of MATLABSystem: '<S2>/Digital Output1' */
  }

  {
    real_T *lastU;

    /* Update for Derivative: '<S3>/Derivative' */
    if (HIL_DW.TimeStampA == (rtInf)) {
      HIL_DW.TimeStampA = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeA;
    } else if (HIL_DW.TimeStampB == (rtInf)) {
      HIL_DW.TimeStampB = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeB;
    } else if (HIL_DW.TimeStampA < HIL_DW.TimeStampB) {
      HIL_DW.TimeStampA = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeA;
    } else {
      HIL_DW.TimeStampB = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeB;
    }

    *lastU = HIL_B.Gain1;

    /* End of Update for Derivative: '<S3>/Derivative' */

    /* Update for Derivative: '<S4>/Derivative' */
    if (HIL_DW.TimeStampA_f == (rtInf)) {
      HIL_DW.TimeStampA_f = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeA_b;
    } else if (HIL_DW.TimeStampB_e == (rtInf)) {
      HIL_DW.TimeStampB_e = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeB_o;
    } else if (HIL_DW.TimeStampA_f < HIL_DW.TimeStampB_e) {
      HIL_DW.TimeStampA_f = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeA_b;
    } else {
      HIL_DW.TimeStampB_e = HIL_M->Timing.t[0];
      lastU = &HIL_DW.LastUAtTimeB_o;
    }

    *lastU = HIL_B.Gain1_g;

    /* End of Update for Derivative: '<S4>/Derivative' */
  }

  {                                    /* Sample time: [0.0s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
      ((HIL_M->Timing.clockTick0 * 1) + 0)
      ;

    /* Trigger External Mode event */
    errorCode = extmodeEvent(0,currentTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  {                                    /* Sample time: [0.01s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
      ((HIL_M->Timing.clockTick1 * 1) + 0)
      ;

    /* Trigger External Mode event */
    errorCode = extmodeEvent(1,currentTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  HIL_M->Timing.t[0] =
    ((time_T)(++HIL_M->Timing.clockTick0)) * HIL_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    HIL_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void HIL_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&HIL_M->solverInfo, &HIL_M->Timing.simTimeStep);
    rtsiSetTPtr(&HIL_M->solverInfo, &rtmGetTPtr(HIL_M));
    rtsiSetStepSizePtr(&HIL_M->solverInfo, &HIL_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&HIL_M->solverInfo, (&rtmGetErrorStatus(HIL_M)));
    rtsiSetRTModelPtr(&HIL_M->solverInfo, HIL_M);
  }

  rtsiSetSimTimeStep(&HIL_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&HIL_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(HIL_M, &HIL_M->Timing.tArray[0]);
  rtmSetTFinal(HIL_M, -1);
  HIL_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  HIL_M->Sizes.checksums[0] = (2398177085U);
  HIL_M->Sizes.checksums[1] = (202644248U);
  HIL_M->Sizes.checksums[2] = (2797773435U);
  HIL_M->Sizes.checksums[3] = (3987871663U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[11];
    HIL_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(HIL_M->extModeInfo,
      &HIL_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(HIL_M->extModeInfo, HIL_M->Sizes.checksums);
    rteiSetTPtr(HIL_M->extModeInfo, rtmGetTPtr(HIL_M));
  }

  {
    codertarget_arduinobase_inter_T *obj;

    /* InitializeConditions for Derivative: '<S3>/Derivative' */
    HIL_DW.TimeStampA = (rtInf);
    HIL_DW.TimeStampB = (rtInf);

    /* InitializeConditions for Derivative: '<S4>/Derivative' */
    HIL_DW.TimeStampA_f = (rtInf);
    HIL_DW.TimeStampB_e = (rtInf);

    /* Start for MATLABSystem: '<S3>/Encoder' */
    HIL_DW.obj.Index = 0U;
    HIL_DW.obj.matlabCodegenIsDeleted = false;
    HIL_DW.obj.SampleTime = HIL_P.Encoder_SampleTime;
    HIL_DW.obj.isInitialized = 1L;
    MW_EncoderSetup(2UL, 3UL, &HIL_DW.obj.Index);
    HIL_DW.obj.isSetupComplete = true;
    HIL_DW.obj.TunablePropsChanged = false;

    /* InitializeConditions for MATLABSystem: '<S3>/Encoder' */
    MW_EncoderReset(HIL_DW.obj.Index);

    /* Start for MATLABSystem: '<S4>/MATLAB System' */
    /*  Constructor */
    /*  Support name-value pair arguments when constructing the object. */
    HIL_DW.obj_b.matlabCodegenIsDeleted = false;

    /*  Do not generate code for sprintf */
    HIL_DW.obj_b.SampleTime = HIL_P.MATLABSystem_SampleTime;
    HIL_DW.obj_b.isInitialized = 1L;

    /*         %% Define output properties */
    /*  Call: void enc_init(int enc, int pinA, int pinB) */
    enc_init(0.0, 18.0, 19.0);
    HIL_DW.obj_b.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/PWM' */
    HIL_DW.obj_f.matlabCodegenIsDeleted = false;
    obj = &HIL_DW.obj_f;
    HIL_DW.obj_f.isInitialized = 1L;
    obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(6UL, 0.0, 0.0);
    HIL_DW.obj_f.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Output' */
    HIL_DW.obj_n.matlabCodegenIsDeleted = false;
    HIL_DW.obj_n.isInitialized = 1L;
    digitalIOSetup(7, 1);
    HIL_DW.obj_n.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/Digital Output1' */
    HIL_DW.obj_j.matlabCodegenIsDeleted = false;
    HIL_DW.obj_j.isInitialized = 1L;
    digitalIOSetup(8, 1);
    HIL_DW.obj_j.isSetupComplete = true;
  }
}

/* Model terminate function */
void HIL_terminate(void)
{
  codertarget_arduinobase_inter_T *obj;

  /* Terminate for MATLABSystem: '<S3>/Encoder' */
  if (!HIL_DW.obj.matlabCodegenIsDeleted) {
    HIL_DW.obj.matlabCodegenIsDeleted = true;
    if ((HIL_DW.obj.isInitialized == 1L) && HIL_DW.obj.isSetupComplete) {
      MW_EncoderRelease();
    }
  }

  /* End of Terminate for MATLABSystem: '<S3>/Encoder' */

  /* Terminate for MATLABSystem: '<S4>/MATLAB System' */
  if (!HIL_DW.obj_b.matlabCodegenIsDeleted) {
    HIL_DW.obj_b.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S4>/MATLAB System' */
  /* Terminate for MATLABSystem: '<S2>/PWM' */
  obj = &HIL_DW.obj_f;
  if (!HIL_DW.obj_f.matlabCodegenIsDeleted) {
    HIL_DW.obj_f.matlabCodegenIsDeleted = true;
    if ((HIL_DW.obj_f.isInitialized == 1L) && HIL_DW.obj_f.isSetupComplete) {
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(6UL);
      MW_PWM_SetDutyCycle(HIL_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE, 0.0);
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(6UL);
      MW_PWM_Close(HIL_DW.obj_f.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/PWM' */
  /* Terminate for MATLABSystem: '<S2>/Digital Output' */
  if (!HIL_DW.obj_n.matlabCodegenIsDeleted) {
    HIL_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Output' */
  /* Terminate for MATLABSystem: '<S2>/Digital Output1' */
  if (!HIL_DW.obj_j.matlabCodegenIsDeleted) {
    HIL_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/Digital Output1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
