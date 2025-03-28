# Energy-Efficient CPU Scheduler

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
![Python](https://img.shields.io/badge/Python-3.6%2B-blue)
![C](https://img.shields.io/badge/C-99%20standard-green)

An adaptive CPU scheduler that optimizes power consumption without compromising performance, designed for resource-constrained systems.

## Features

- **Real-time power profiling** (simulated in VMware)
- **Dynamic frequency scaling** (performance/powersave modes)
- **Live performance monitoring dashboard**
- **Hardware-agnostic design** (works on VMs and bare metal)


## Installation

### Prerequisites
- Ubuntu 18.04/20.04/22.04
- Python 3.6+
- GCC (for C components)

```bash
# Clone repository
git clone https://github.com/PaulThallapureddy/Energy-Efficient-CPU-Scheduling-Algorithm.git
cd energy-scheduler

# Install dependencies
sudo apt update && sudo apt install -y \
    python3-pip \
    python3-venv \
    gcc \
    make \
    libncurses-dev

# Set up Python environment
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt

# Terminal 1: Power profiler (generates graphs)
python3 power_profiler.py

# Terminal 2: Scheduler (core algorithm)
gcc scheduler.c -o scheduler && ./scheduler

# Terminal 3: Live monitor (performance dashboard)
gcc monitor.c -o monitor -lncurses && ./monitor

