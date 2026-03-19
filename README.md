# 💀 Beacon-Ghost: Sub-GHz Heartbeat Auditor

**Beacon-Ghost** is a specialized pentesting tool for the Flipper Zero designed for **Signal Heartbeat Analysis (SHA)**. Unlike standard recorders, Beacon-Ghost focuses on the temporal patterns of repeating Sub-GHz signals.

## 📡 The Theory: Signal Heartbeat Analysis (SHA)
Most "Smart" infrastructure (locks, sensors, industrial controllers) relies on a **Keep-Alive Beacon**. This is a periodic signal sent to a central hub to confirm the device is still online and hasn't been tampered with.

**The Vulnerability:**
If a system expects a heartbeat every 500ms, a pentester can use Beacon-Ghost to:
1. **Identify the Interval:** Determine exactly when the system expects a check-in.
2. **Predictive Injection:** Time a malicious signal or a "denial of service" pulse to hit the exact millisecond between heartbeats, bypassing "collision detection" in higher-end systems.
3. **Watchdog Auditing:** Determine if a security system will trigger an alarm if a signal is missed (Fail-Safe vs. Fail-Secure).

## 🚀 Features
* **Passive Monitoring:** Operates in RX-only mode to remain invisible to RF spectrum analyzers.
* **Precision Timing:** Uses the Flipper's internal clock to calculate intervals down to the millisecond.
* **Momentum Optimized:** Designed specifically for the Momentum firmware's hardware abstraction layer.

## 🛠️ Installation
1. Create a folder: `applications_user/beacon_ghost` in your firmware source.
2. Upload `beaconghost.c` and `application.fam`.
3. Compile using:
```bash
./fbt launch_app APPID=beacon_ghost
Legal Disclaimer
This tool is for Educational and Ethical Testing purposes only. Unauthorized access to or disruption of radio communications is illegal in many jurisdictions. Use only on hardware you own or have explicit permission to audit.
