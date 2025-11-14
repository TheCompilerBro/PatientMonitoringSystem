#                                                                                   <h1> PatientMonitoringSystem </h1>


Paralyzed Patient Monitoring System (IoT + ESP32 + Firebase + Web Dashboard)


                      The Compiler Bro       MediPulse
# 🧑‍⚕️ Paralyzed Patient Monitoring System (ESP32 + Firebase + Web Dashboard)

A smart IoT solution built to help **paralyzed & semi-paralyzed patients** communicate their needs and alert caregivers **without speaking or pressing buttons**.  
This project uses **ESP32**, **Flex Sensor**, **ADXL335**, **LM35**, and **Firebase Realtime Database** to monitor patient health and show instant alerts on a modern web dashboard.

---

# 📌 Features

### ✔ Flex-Based Patient Request  
Small finger/wrist movement triggers:
- “GIVE SOME FOOD”
- “NEED HELP”

### ✔ Fall Detection (ADXL335)  
Detects sudden jerks or falls:  
**“FALL DETECTED — NEED HELP”**

### ✔ Body Temperature Monitoring (LM35)  
Detects fever or abnormal temperature:
**“HIGH TEMPERATURE — NEED HELP”**

### ✔ Real-Time Firebase Dashboard  
- Live sensor data  
- Big alert banner  
- Beeping alarm  
- History tracking  
- Mobile vibration support  

### ✔ LED Emergency Indicator  
Turns ON for any alert.

---

# 🧩 Hardware Components

| Component | Purpose |
|----------|---------|
| **ESP32 Dev Board** | WiFi + controller |
| **Flex Sensor** | Patient request detection |
| **ADXL335** | Fall detection |
| **LM35** | Temperature measuring |
| **LED** | Visual alert |
| **10k Resistors** | Voltage dividers |

---

# 🧰 Software Tools

- Arduino IDE  
- Firebase Realtime Database  
- HTML / CSS / JavaScript (Firebase v9 Modules)  
- VS Code (Live Server) or Python HTTP Server  

---

# 📡 Firebase Realtime Database Structure

|||
alerts: {
  "flex": "YES/NO",
  "fall": "YES/NO",
  "temperature": "HIGH/NORMAL",
  "time": "DD-MM-YYYY HH:MM:SS",
  "message": "text OR none"
}

<h1>  🏗 System Architecture </h1>
Sensors → ESP32 → Firebase → Web Dashboard → Caregiver 

<h1> 🖥 Web Dashboard </h1>
![Dashboard]
<img width="1710" height="1073" alt="dashboard" src="https://github.com/user-attachments/assets/a0c6f46a-fd68-4890-8582-29bb543d919d" />


![Alert Example]
<img width="1710" height="1107" alt="alert" src="https://github.com/user-attachments/assets/05e078a8-761d-4342-9640-38e8408338ff" />

<h2> 🚀 Installation </h2>

1️⃣ Clone the repository
git clone https://github.com/YOUR_USERNAME/patient-monitoring-system.git

2️⃣ Upload ESP32 code
Open ESP32_Code.ino in Arduino
Add WiFi + Firebase details
Upload

3️⃣ Firebase Setup
Create Firebase project
Enable Realtime Database
Set rules to read/write
Copy database URL into code

4️⃣ Run the dashboard
Using a local server:
Option A — VS Code Live Server
Right-click index.html → Open with Live Server
Option B — Python Server
python3 -m http.server 8000
Open:
http://localhost:8000
 


<h2> 🩺 Real Use Cases
Paralysis rehabilitation
Elderly care centers
Hospital ICUs
Home patient monitoring
Disabled assistance
🔮 Future Scope
Heartbeat/Pulse sensor
SpO2 monitoring
Voice alerts
Multi-patient dashboard
Mobile App (PWA)
GPS tracking
</h2>

<h1> ⭐ Author :-Puspendu Mallick </h1>

████████╗██╗  ██╗███████╗     ██████╗ ██████╗ ███╗   ███╗██████╗ ██╗██╗     ███████╗██████╗ 
╚══██╔══╝██║  ██║██╔════╝    ██╔════╝ ██╔══██╗████╗ ████║██╔══██╗██║██║     ██╔════╝██╔══██╗
   ██║   ███████║█████╗      ██║  ███╗██████╔╝██╔████╔██║██████╔╝██║██║     █████╗  ██████╔╝
   ██║   ██╔══██║██╔══╝      ██║   ██║██╔══██╗██║╚██╔╝██║██╔══██╗██║██║     ██╔══╝  ██╔══██╗
   ██║   ██║  ██║███████╗    ╚██████╔╝██║  ██║██║ ╚═╝ ██║██████╔╝██║███████╗███████╗██║  ██║
   ╚═╝   ╚═╝  ╚═╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═════╝ ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝
   Paralyzed Patient Monitoring System (ESP32 + Firebase)

