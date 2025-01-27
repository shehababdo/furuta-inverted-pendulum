/*
 * File: HIL_data.c
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

#include "HIL.h"

/* Block parameters (default storage) */
P_HIL_T HIL_P = {
  /* Variable: K
   * Referenced by: '<S1>/Gain1'
   */
  { 0.31622776601687785, 34.753771375103916, 0.76531170228972256,
    22.360250935538545 },

  /* Expression: -1
   * Referenced by: '<S3>/Encoder'
   */
  -1.0,

  /* Expression: 0.1
   * Referenced by: '<S4>/MATLAB System'
   */
  0.1,

  /* Expression: 2*pi
   * Referenced by: '<S10>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S11>/Constant1'
   */
  6.2831853071795862,

  /* Expression: pi
   * Referenced by: '<S9>/Bias'
   */
  3.1415926535897931,

  /* Expression: -pi
   * Referenced by: '<S9>/Bias1'
   */
  -3.1415926535897931,

  /* Expression: -pi
   * Referenced by: '<S9>/Bias2'
   */
  -3.1415926535897931,

  /* Expression: +pi
   * Referenced by: '<S9>/Bias3'
   */
  3.1415926535897931,

  /* Expression: (360/(500*4))
   * Referenced by: '<S3>/rev to degree'
   */
  0.18,

  /* Expression: pi/180
   * Referenced by: '<S6>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 0
   * Referenced by: '<S4>/Rate Transition'
   */
  0.0,

  /* Expression: pi
   * Referenced by: '<S5>/Pi'
   */
  3.1415926535897931,

  /* Expression: 0
   * Referenced by:
   */
  0.0,

  /* Expression: 2*pi
   * Referenced by: '<S9>/Constant'
   */
  6.2831853071795862,

  /* Expression: 2*pi
   * Referenced by: '<S9>/Constant1'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S9>/Switch'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Constant'
   */
  0.0,

  /* Expression: pi/7
   * Referenced by: '<S1>/Linearity checker'
   */
  0.44879895051282759,

  /* Expression: 1/10
   * Referenced by: '<S2>/Scaling'
   */
  0.1,

  /* Expression: 255
   * Referenced by: '<S2>/Saturation'
   */
  255.0,

  /* Expression: -255
   * Referenced by: '<S2>/Saturation'
   */
  -255.0,

  /* Expression: 0
   * Referenced by: '<S2>/Constant'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S2>/Constant1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S2>/Switch1'
   */
  0.0,

  /* Expression: (360/600)/4
   * Referenced by: '<S4>/rev to degree'
   */
  0.15,

  /* Expression: pi/180
   * Referenced by: '<S7>/Gain1'
   */
  0.017453292519943295
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
