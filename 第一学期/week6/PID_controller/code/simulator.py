import numpy as np
import matplotlib.pyplot as plt

# --- Simulation Parameters ---
DT = 0.01  # Time step (s)
SIMULATION_TIME = 50.0  # Total simulation time (s)
TARGET_POSITION = 10.0  # Target position (m)
DISTURBANCE_FORCE = -10.0  # Constant disturbance force (N)

# --- Dynamics Model ---
class Block:
    def __init__(self, mass=1.0, x0=0.0, v0=0.0, disturbance=0.0):
        self.m = mass
        self.x = x0
        self.v = v0
        self.disturbance = disturbance
    
    def update(self, force, dt):
        # F = ma => a = (F + F_dist) / m
        a = (force + self.disturbance) / self.m
        self.v += a * dt
        self.x += self.v * dt
        return self.x, self.v

# --- Controllers ---

class BangBangController:
    def __init__(self, max_force=5.0, deadband=0.1):
        self.max_force = max_force
        self.deadband = deadband
        
    def get_control(self, target, current, velocity):
        error = target - current
        if abs(error) < self.deadband:
            return 0.0
        return self.max_force if error > 0 else -self.max_force

class PController:
    def __init__(self, kp):
        self.kp = kp
        
    def get_control(self, target, current, velocity):
        error = target - current
        return self.kp * error

class PDController:
    def __init__(self, kp, kd):
        self.kp = kp
        self.kd = kd
        
    def get_control(self, target, current, velocity):
        error = target - current
        # D term acts on velocity (derivative of error if target is static is -velocity)
        # u = Kp * e + Kd * e_dot = Kp * e - Kd * v
        return self.kp * error - self.kd * velocity

class PIDController:
    def __init__(self, kp, ki, kd, dt):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.dt = dt
        self.integral = 0.0
        
    def get_control(self, target, current, velocity):
        error = target - current
        self.integral += error * self.dt
        # Anti-windup could be added here, but keeping it simple
        return self.kp * error + self.ki * self.integral - self.kd * velocity

class CascadePController:
    def __init__(self, kp_pos, kp_vel):
        self.kp_pos = kp_pos
        self.kp_vel = kp_vel
        
    def get_control(self, target, current, velocity):
        # Outer loop (Position Control) -> Velocity Setpoint
        pos_error = target - current
        v_target = self.kp_pos * pos_error
        
        # Inner loop (Velocity Control) -> Force/Acceleration
        vel_error = v_target - velocity
        return self.kp_vel * vel_error

# --- Simulation Runner ---
def run_simulation(controller, name):
    block = Block(disturbance=DISTURBANCE_FORCE)
    time_history = np.arange(0, SIMULATION_TIME, DT)
    pos_history = []
    vel_history = []
    
    for _ in time_history:
        pos_history.append(block.x)
        vel_history.append(block.v)
        
        force = controller.get_control(TARGET_POSITION, block.x, block.v)
        block.update(force, DT)
        
    return time_history, pos_history, vel_history

# --- Main Execution ---
if __name__ == "__main__":
    # Define Controllers
    controllers = [
        # (BangBangController(max_force=10.0, deadband=0.1), "Bang-Bang Control"),
        # (PController(kp=2.0), "P Control (Kp=2.0)"),
        # (PDController(kp=10000.0, kd=35.0), "PD Control 1 (Kp=10000, Kd=35)"),
        # (PDController(kp=50.0, kd=100.0), "PD Control 2 (Kp=50, Kd=100)"),
        (PDController(kp=50.0, kd=30.0), "PD Control (Kp=50, Kd=30)"),
        (PIDController(kp=50.0, ki=10.0, kd=20.0, dt=DT), "PID Control (Kp=50, Ki=10, Kd=20)"),
        # (CascadePController(kp_pos=3.0, kp_vel=3.5), "Cascade P Control (Pos=3, Vel=3.5)")
    ]
    
    results = []
    print(f"{'Controller Name':<35} | {'Final Error (m)':<15}")
    print("-" * 55)
    for ctrl, name in controllers:
        t, x, v = run_simulation(ctrl, name)
        results.append((name, t, x, v))
        final_error = TARGET_POSITION - x[-1]
        print(f"{name:<35} | {final_error:.6f}")
        
    # --- Plotting ---
    try:
        plt.style.use('seaborn-v0_8-whitegrid')
    except:
        plt.style.use('ggplot') # Fallback if style not found

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10), sharex=True)
    
    colors = ['k', 'r', 'g', 'b', 'm']
    linestyles = ['-', '--', '-.', ':', '-']
    
    for i, (name, t, x, v) in enumerate(results):
        ax1.plot(t, x, label=name, color=colors[i], linestyle=linestyles[i], linewidth=1.5)
        ax2.plot(t, v, label=name, color=colors[i], linestyle=linestyles[i], linewidth=1.5)
        
    ax1.axhline(y=TARGET_POSITION, color='gray', linestyle='--', alpha=0.5, label='Target Position')
    ax1.set_ylabel('Position (m)')
    ax1.set_title('Position Response Comparison')
    ax1.legend(loc='lower right')
    ax1.grid(True)
    
    ax2.set_ylabel('Velocity (m/s)')
    ax2.set_xlabel('Time (s)')
    ax2.set_title('Velocity Response Comparison')
    ax2.legend(loc='upper right')
    ax2.grid(True)
    
    plt.tight_layout()
    plt.show()
