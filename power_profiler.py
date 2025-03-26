import numpy as np
import matplotlib.pyplot as plt
from dataclasses import dataclass
from typing import List, Tuple
import psutil
import time

@dataclass
class PowerMeasurement:
    timestamp: float
    cpu_utilization: float
    frequency: float
    power_consumption: float

class PowerProfiler:
    def __init__(self, sample_interval: float = 1.0, duration: float = 30.0):
        self.sample_interval = sample_interval
        self.duration = duration
        self.measurements: List[PowerMeasurement] = []
        
    def _simulate_frequency(self, utilization: float) -> float:
        base_freq = 1200.0
        boost_freq = 3000.0
        threshold = 0.7
        return boost_freq if utilization > threshold else base_freq
    
    def _calculate_power(self, freq: float, utilization: float) -> float:
        static_power = 5.0
        dynamic_power = utilization * (freq / 3000.0) * 25.0
        return static_power + dynamic_power
    
    def collect_metrics(self):
        start_time = time.time()
        while (time.time() - start_time) < self.duration:
            utilization = psutil.cpu_percent(interval=self.sample_interval) / 100.0
            freq = self._simulate_frequency(utilization)
            power = self._calculate_power(freq, utilization)
            
            measurement = PowerMeasurement(
                timestamp=time.time() - start_time,
                cpu_utilization=utilization * 100,
                frequency=freq,
                power_consumption=power
            )
            self.measurements.append(measurement)
            
            print(f"Time {measurement.timestamp:.1f}s: "
                  f"CPU={measurement.cpu_utilization:.1f}% "
                  f"Freq={measurement.frequency:.0f}MHz "
                  f"Power={measurement.power_consumption:.2f}W")
    
    def visualize(self):
        timestamps = [m.timestamp for m in self.measurements]
        powers = [m.power_consumption for m in self.measurements]
        utils = [m.cpu_utilization for m in self.measurements]
        
        fig, ax1 = plt.subplots(figsize=(10, 5))
        
        color = 'tab:red'
        ax1.set_xlabel('Time (s)')
        ax1.set_ylabel('Power (W)', color=color)
        ax1.plot(timestamps, powers, color=color)
        ax1.tick_params(axis='y', labelcolor=color)
        
        ax2 = ax1.twinx()
        color = 'tab:blue'
        ax2.set_ylabel('CPU Utilization (%)', color=color)
        ax2.plot(timestamps, utils, color=color)
        ax2.tick_params(axis='y', labelcolor=color)
        
        plt.title('CPU Power Consumption Profile')
        plt.savefig('power_analysis.png')
        plt.close()

if __name__ == "__main__":
    profiler = PowerProfiler(sample_interval=1.0, duration=20.0)
    profiler.collect_metrics()
    profiler.visualize()