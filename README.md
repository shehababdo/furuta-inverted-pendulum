# Furuta Pendulum Control Using LQR

This repository documents the design, modeling, and control of a Furuta Pendulum (Rotary Inverted Pendulum) using the Linear Quadratic Regulator (LQR) method. The goal is to stabilize the pendulum in an upright position (θ = 0) and ensure robustness against disturbances.

---

## Table of Contents
1. [Physical System](#physical-system)
   - [CAD Design](#cad-design)
   - [Real-Life Assembly](#real-life-assembly)
2. [Control Requirements](#control-requirements)
3. [Control System Modeling](#control-system-modeling)
4. [Controller Design (LQR)](#controller-design-lqr)
5. [Implementation](#implementation)
6. [Testing and Results](#testing-and-results)
7. [Conclusion](#conclusion)

---

## Physical System
### CAD Design
The Furuta pendulum consists of:
- **Rotating arm**: Driven by a DC motor.
- **Pendulum**: Freely rotating about the arm's pivot.
- **Sensors**: Encoder for arm angle measurement, IMU for pendulum angle.

![image](https://github.com/user-attachments/assets/09eca766-fcd9-48f4-8b30-d90ecdd2da11)

### Real-Life Assembly
The physical system was built using:
- **Actuator**: 12V DC motor with gearbox.
- **Microcontroller**: STM32 or Arduino for real-time control.
- **Power Supply**: 12V battery or regulated power source.

![WhatsApp Image 2025-01-01 at 16 21 51_386557d1](https://github.com/user-attachments/assets/b3099a07-df35-4c9f-8b9c-5675e4ad6c07)

---

## Control Requirements
1. Stabilize the pendulum upright (θ = 0°).
2. Reject disturbances (e.g., manual pushes).
3. Achieve settling time < 3 seconds.
4. Minimize steady-state error (< 1°).

---

## Control System Modeling
The system dynamics were derived using Lagrangian mechanics. The state-space representation is:

\[
\begin{align*}
\dot{\mathbf{x}} &= A\mathbf{x} + B\mathbf{u} \\
\mathbf{y} &= C\mathbf{x} + D\mathbf{u}
\end{align*}
\]

**States**:  
\[
\mathbf{x} = \begin{bmatrix} \alpha & \theta & \dot{\alpha} & \dot{\theta} \end{bmatrix}^T
\]
- \( \alpha \): Arm angle  
- \( \theta \): Pendulum angle  

**Input**:  
\[
\mathbf{u} = V_{\text{motor}}
\]

---

## Controller Design (LQR)
The LQR is an optimal control method that minimizes the cost function:  
\[
J = \int_0^\infty \left( \mathbf{x}^T Q \mathbf{x} + \mathbf{u}^T R \mathbf{u} \right) dt
\]

**Steps**:
1. Linearize the system around the upright equilibrium.
2. Tune weighting matrices \( Q \) (state penalties) and \( R \) (input penalty).  
   Example:  
   \[
   Q = \text{diag}([1, 10, 0.1, 0.5]), \quad R = 0.01
   \]
3. Solve the Algebraic Riccati Equation (ARE) to compute the gain matrix \( K \).  
   \[
   \mathbf{u} = -K\mathbf{x}
   \]

**Why LQR?**  
- Optimally balances performance and control effort.  
- Inherently robust against small disturbances.  

---

## Implementation
 Hardware Setup
- Motor driver: H-bridge for bidirectional control.
- DC motor with magnetic Encoder![image](https://github.com/user-attachments/assets/676f0cb1-ce9f-4770-a1fa-a969909e4b04)
- Optical incremental Encoder 600 ppr ![image](https://github.com/user-attachments/assets/ccf2d52c-9382-443d-9bf8-dbc7663af20a)
- Microcontroller Selection (Arduino Mega 2560) ![image](https://github.com/user-attachments/assets/77fcdaa4-5642-4f02-a002-bdd30d667a83)

 ## Software  
This section details the simulation workflow and hardware implementation.  

---

### Step 1: Parameter Estimation  
To model the DC motor dynamics, critical parameters (e.g., torque constant, back-EMF, inertia) were estimated experimentally:  
1. **Data Collection**:  
   - Applied step voltages to the motor and measured angular velocity using an encoder.  
   - Recorded input-output data for system identification.  
2. **MATLAB System Identification Toolbox**:  
   - Used `tfest` to fit a transfer function to the experimental data.  
   - Estimated motor model:  
     \[
     G(s) = \frac{\omega(s)}{V(s)} = \frac{K}{\tau s + 1}
     \]  
3. **Validation**: Compared simulated vs. real motor responses.  

![Parameter Estimation](images/param_estimation.png) *(Replace with motor step response plot)*  

---

### Step 2: LQR Control Design  
1. **State-Space Linearization**:  
   - Derived linearized model at equilibrium:  
     \[
     \dot{\mathbf{x}} = A\mathbf{x} + B\mathbf{u}, \quad \mathbf{x} = [\alpha, \theta, \dot{\alpha}, \dot{\theta}]^T
     \]  
2. **LQR Tuning in MATLAB**:  
   - Weighting matrices:  
     \[
     Q = \text{diag}([1, 100, 0.1, 10]), \quad R = 0.1
     \]  
   - Solved Riccati equation using `lqr(A, B, Q, R)` to compute gain matrix \( K \).  
3. **Simulink Simulation**:  
   - Added LQR controller block to stabilize \( \theta \).  
   - Tested disturbance rejection by applying impulse torque to the pendulum.  

![LQR Simulation](images/lqr_sim.png) *(Replace with stabilization plot)*  

---

### Step 3: Hardware-in-the-Loop (HIL) Testing  
1. **Simulink Real-Time Integration**:  
   - Generated C code from Simulink using `Simulink Coder`.  
   - Deployed the LQR controller to an STM32/Arduino via USB/UART.  
2. **HIL Workflow**:  
   - Connected Simulink to hardware:  
     - **Inputs**: Encoder (α), IMU (θ).  
     - **Output**: PWM signal to motor driver.  
   - Validated real-time performance with simulated disturbances.  
3. **Validation**:  
   - Compared HIL results with pure simulation.  
   - Adjusted \( Q \) and \( R \) to reduce real-world noise sensitivity.  

![HIL Setup](images/hil_setup.jpg) *(Replace with HIL testing photo)*  

---
## Testing And Results
