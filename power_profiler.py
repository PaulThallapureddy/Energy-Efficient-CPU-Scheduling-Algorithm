import os
import time
import psutil 
import matplotlib.pyplot as plt 

def get_cpu_power():
    try:
        with open("/sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj", "r") as f:
            return int(f.read()) / 1_000_000  
    except FileNotFoundError:
        return psutil.cpu_percent() * 0.1 

def log_power(interval=1, duration=10):
    timestamps, power = [], []
    for _ in range(duration):
        timestamps.append(time.time())
        power.append(get_cpu_power())
        time.sleep(interval)