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
### Hardware Setup
- Motor driver: H-bridge for bidirectional control.
- Sensors: Encoder for \( \alpha \), IMU (MPU6050) for \( \theta \).

### Software
- **Simulation**: MATLAB/Simulink for LQR tuning.  
- **Real-Time**: Simulink Hardware in the Loop
