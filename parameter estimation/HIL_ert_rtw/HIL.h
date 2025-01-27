/*
 * File: HIL.h
 *
 * Code generated for Simulink model 'HIL'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Tue Dec 31 16:00:42 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_HIL_h_
#define RTW_HEADER_HIL_h_
#ifndef HIL_COMMON_INCLUDES_
#define HIL_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_arduino_digitalio.h"
#include "MW_PWM.h"
#include "MW_ArduinoEncoder.h"
#include "encoder_arduino.h"
#endif                                 /* HIL_COMMON_INCLUDES_ */

#include "HIL_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real_T revtodegree;                  /* '<S3>/rev to degree' */
  real_T Gain1;                        /* '<S6>/Gain1' */
  real_T DataTypeConversion2;          /* '<S3>/Data Type Conversion2' */
  real_T RateTransition;               /* '<S4>/Rate Transition' */
  real_T Add;                          /* '<S5>/Add' */
  real_T Merge;                        /* '<S8>/Merge' */
  real_T TmpRTBAtDerivativeInport1;    /* '<S4>/Degrees to Radians' */
  real_T DataTypeConversion2_l;        /* '<S4>/Data Type Conversion2' */
  real_T DataTypeConversion3;          /* '<S3>/Data Type Conversion3' */
  real_T Switch;                       /* '<S9>/Switch' */
  real_T ControlAction;                /* '<S1>/Linearity checker' */
  real_T Scaling;                      /* '<S2>/Scaling' */
  real_T pwm;                          /* '<S2>/remove any negative pwm sign' */
} B_HIL_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_i_T obj; /* '<S3>/Encoder' */
  Encoder_arduino_HIL_T obj_b;         /* '<S4>/MATLAB System' */
  codertarget_arduinobase_block_T obj_j;/* '<S2>/Digital Output1' */
  codertarget_arduinobase_block_T obj_n;/* '<S2>/Digital Output' */
  codertarget_arduinobase_inter_T obj_f;/* '<S2>/PWM' */
  real_T TimeStampA;                   /* '<S3>/Derivative' */
  real_T LastUAtTimeA;                 /* '<S3>/Derivative' */
  real_T TimeStampB;                   /* '<S3>/Derivative' */
  real_T LastUAtTimeB;                 /* '<S3>/Derivative' */
  real_T RateTransition_Buffer0;       /* '<S4>/Rate Transition' */
  real_T TmpRTBAtDerivativeInport1_Buffe;/* synthesized block */
  real_T TimeStampA_f;                 /* '<S4>/Derivative' */
  real_T LastUAtTimeA_b;               /* '<S4>/Derivative' */
  real_T TimeStampB_e;                 /* '<S4>/Derivative' */
  real_T LastUAtTimeB_o;               /* '<S4>/Derivative' */
  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S1>/Scope1' */

  struct {
    void *LoggedData[2];
  } Scope1_PWORK_m;                    /* '<S2>/Scope1' */

  struct {
    void *LoggedData[2];
  } Scope2_PWORK;                      /* '<S5>/Scop e2' */

  struct {
    void *LoggedData[4];
  } Scope1_PWORK_b;                    /* '<Root>/Scope1' */

  struct {
    void *LoggedData[2];
  } Scope_PWORK;                       /* '<S5>/Scope' */

  struct {
    void *LoggedData;
  } Scope_PWORK_f;                     /* '<S3>/Scope' */

  int8_T IfActionSubsystem2_SubsysRanBC;/* '<S8>/If Action Subsystem2' */
  int8_T IfActionSubsystem1_SubsysRanBC;/* '<S8>/If Action Subsystem1' */
  int8_T IfActionSubsystem_SubsysRanBC;/* '<S8>/If Action Subsystem' */
} DW_HIL_T;

/* Parameters (default storage) */
struct P_HIL_T_ {
  real_T K[4];                         /* Variable: K
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T Encoder_SampleTime;           /* Expression: -1
                                        * Referenced by: '<S3>/Encoder'
                                        */
  real_T MATLABSystem_SampleTime;      /* Expression: 0.1
                                        * Referenced by: '<S4>/MATLAB System'
                                        */
  real_T Constant_Value;               /* Expression: 2*pi
                                        * Referenced by: '<S10>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 2*pi
                                        * Referenced by: '<S11>/Constant1'
                                        */
  real_T Bias_Bias;                    /* Expression: pi
                                        * Referenced by: '<S9>/Bias'
                                        */
  real_T Bias1_Bias;                   /* Expression: -pi
                                        * Referenced by: '<S9>/Bias1'
                                        */
  real_T Bias2_Bias;                   /* Expression: -pi
                                        * Referenced by: '<S9>/Bias2'
                                        */
  real_T Bias3_Bias;                   /* Expression: +pi
                                        * Referenced by: '<S9>/Bias3'
                                        */
  real_T revtodegree_Gain;             /* Expression: (360/(500*4))
                                        * Referenced by: '<S3>/rev to degree'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * Referenced by: '<S6>/Gain1'
                                        */
  real_T RateTransition_InitialCondition;/* Expression: 0
                                          * Referenced by: '<S4>/Rate Transition'
                                          */
  real_T Pi_Value;                     /* Expression: pi
                                        * Referenced by: '<S5>/Pi'
                                        */
  real_T TmpRTBAtDerivativeInport1_Initi;/* Expression: 0
                                          * Referenced by:
                                          */
  real_T Constant_Value_n;             /* Expression: 2*pi
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Constant1_Value_g;            /* Expression: 2*pi
                                        * Referenced by: '<S9>/Constant1'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S9>/Switch'
                                        */
  real_T Constant_Value_m;             /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Linearitychecker_Threshold;   /* Expression: pi/7
                                        * Referenced by: '<S1>/Linearity checker'
                                        */
  real_T Scaling_Gain;                 /* Expression: 1/10
                                        * Referenced by: '<S2>/Scaling'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 255
                                        * Referenced by: '<S2>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -255
                                        * Referenced by: '<S2>/Saturation'
                                        */
  real_T Constant_Value_e;             /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant1_Value_n;            /* Expression: 1
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S2>/Switch1'
                                        */
  real_T revtodegree_Gain_l;           /* Expression: (360/600)/4
                                        * Referenced by: '<S4>/rev to degree'
                                        */
  real_T Gain1_Gain_h;                 /* Expression: pi/180
                                        * Referenced by: '<S7>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_HIL_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTick2;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    struct {
      boolean_T TID1_2;
    } RateInteraction;

    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_HIL_T HIL_P;

/* Block signals (default storage) */
extern B_HIL_T HIL_B;

/* Block states (default storage) */
extern DW_HIL_T HIL_DW;

/* External function called from main */
extern void HIL_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void HIL_initialize(void);
extern void HIL_step0(void);
extern void HIL_step2(void);
extern void HIL_terminate(void);

/* Real-time Model object */
extern RT_MODEL_HIL_T *const HIL_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Conversion3' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'HIL'
 * '<S1>'   : 'HIL/Controller'
 * '<S2>'   : 'HIL/motor drive'
 * '<S3>'   : 'HIL/motor encoder'
 * '<S4>'   : 'HIL/pendulum encoder'
 * '<S5>'   : 'HIL/waraper'
 * '<S6>'   : 'HIL/motor encoder/Degrees to Radians'
 * '<S7>'   : 'HIL/pendulum encoder/Degrees to Radians'
 * '<S8>'   : 'HIL/waraper/range keeper'
 * '<S9>'   : 'HIL/waraper/waraper'
 * '<S10>'  : 'HIL/waraper/range keeper/If Action Subsystem'
 * '<S11>'  : 'HIL/waraper/range keeper/If Action Subsystem1'
 * '<S12>'  : 'HIL/waraper/range keeper/If Action Subsystem2'
 */
#endif                                 /* RTW_HEADER_HIL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
