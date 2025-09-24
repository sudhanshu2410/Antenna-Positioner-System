# Antenna Positioner System

A **GPS-based automated antenna positioning system** designed to **precisely align satellite antennas** for enhanced signal reception and reliable SATCOM communication.

The project is implemented using **Code Composer Studio (CCS)** and **BeagleBone Black**.

---

## 🌟 Features

- **GPS Integration** – Uses real-time GPS data for accurate antenna orientation.  
- **Automated Control** – Stepper motors adjust the antenna automatically.  
- **Microcontroller-Based** – Built with BeagleBone Black.  
- **Real-Time Feedback** – Monitors status and diagnostics via CCS console.  
- **Modular Design** – Adaptable for different SATCOM setups.  

---

## 🛠️ Components

| Component           | Details                                 |
| ------------------ | --------------------------------------- |
| Microcontroller     | BeagleBone Black                        |
| GPS Module          | CW46S GPS Sensor by NavSync             |
| Actuators           | Stepper Motor + Motor Driver (ULN2003) |
| Power Supply        | 12V, 0.09A                              |
| Debugging Interface | JTAG Debugging Emulator (TI USB100v2)  |

---

## ⚡ Installation & Setup

1. **Clone the Repository**

```bash
git clone https://github.com/sudhanshu2410/Antenna-Positioner-System.git
````

2. **Open in Code Composer Studio (CCS)**

* Launch CCS → Select workspace → Import project via `File → Import → CCS Projects`.

3. **Build & Upload Code**

* Select **BeagleBone Black** as the target board.
* Build and flash the project.

4. **Hardware Connections**

* Connect GPS sensor (CW46S) to BeagleBone Black.
* Connect stepper motor via ULN2003 driver.
* Power the system with 12V, 0.09A supply.
* Use JTAG emulator for debugging.

---

## 🎮 Usage

1. Power on the system; it initializes and acquires GPS signals.
2. The system calculates the optimal antenna orientation.
3. Stepper motors move the antenna automatically.
4. Monitor real-time status via CCS debug console.

---

## 📚 Documentation 

* **Project Report:** [https://drive.google.com/file/d/1WuRgGRI2FgILwS2xlT3J-KLTtQW1D9xv/view?usp=drivesdk]
* **Wiring Diagram:** [https://drive.google.com/file/d/1lp4puPCLWbaWf2jrtEc3RiPkecDDlwD5/view?usp=drivesdk]
* **Block Diagram:** [https://drive.google.com/file/d/17mX0GAvuNmAX3qesalYnVaJXO0o4L3uh/view?usp=drivesdk]
* **Working Project Screenshot:** [https://drive.google.com/file/d/1BMXHwiS1jXoIfnlLPBBNhnkgbQGx-whB/view?usp=drivesdk]


