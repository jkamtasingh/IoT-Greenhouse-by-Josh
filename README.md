# IoT-Greenhouse-by-Josh
An Internet of Things (IoT) greenhouse powered by the ESP32 Dev Module.

# Technologies used
Software
- Arduino IDE (C++)
  - Arduino Libraries: ESP32 core library, Firebase Arduino Client Library for ESP8266 and ESP32
- Google Firebase
   - Firebase hosting
   - Firebase authentication
- Visual Studio Code
- HTML
- Node.js
- Chart.js

Hardware
- ESP32 Dev Module
- Irrigation Kit
  - Water Pump
  - 50cm Silicone Tubing
  - Capacitive Soil Moisture Sensor
  - 5V Relay Module
  - AA Power Box
- Jumper Wires (Male to Male, Female to Male)

# Features
- This project utilizes the ESP32 microcontroller and the capacitive soil moisture sensor to detect the moisture from a plant's soil.
- Once the soil's moisture passes a certain threshold (for example: in my code, the threshold is set to 3000), the 5V relay module will activate, allowing the water pump to turn on and dispense water to increase the plant's moisture levels.
- Additionally, the ESP32 collects specific information from the greenhouse (when the pump is activated and the plant's moisture every 5 minutes) and stores this information inside of a Realtime Database inside of Google's Firebase software.
- The Realtime Database is secured using Firebase Authentication, which is locked down by requiring anonymous authentication for all reading/writing.
- Furthermore, the backend information from the Realtime Database uploads and displays itself onto a frontend web app created using HTML.
- The webapp allows the user to see Soil Moisture levels from their device's web browser, schedule a time to dispense water into the plants, manually dispense water, and see a chart of the plant's moisture levels every 5 minutes.
  - The ESP32 pulls real-world time to allow accurate scheduling through NTP time sync.
  - The webapp can be installed as a mobile web app as a manifest and icons were added so it can be installed to a phone's home screen.
  - Additionally, the webapp is deployed live using Firebase Hosting through Node.js, current link: https://iot-greenhouse-by-josh.web.app/

# The Process
I began this project by wiring the irrigation kit to the ESP32 microcontroller, and drafted code in the Arduino IDE that turns the relay module on when it is wet and vice versa. 

Next, I created a new project on the Google's Firebase console, Authentication and the Realtime Database products were added.

Immediately, I turned on anonymous authentication to protect the data as only my ESP32 will anonymously sign in to the Realtime Database. 

Additionally, the project had to be added as a web app to get its API key and database URL.

Then, I began adding the database code to the Arduino code, initially adding the current status of the pump, moisture, and eventually adding the manual dispense data and plant's moisture levels.

After confirming that the database is connected to the ESP32 and is actively reading/storing data, I began designing the frontend using HTML and Visual Studio Code.

The API Key and database URL had to be added to the frontend to link the Realtime Database and web app together.

Chart.js was utilized in creating the frontend as it would update with the plant's moisture levels every 5 minutes.

Going back to the Arduino IDE, functions were created to manually dispense water, check scheduled times to dispense water, and NTP time sync was added to pull the current time.

Now that the ESP32 code, frontend and backend were working cohesively, it was time to host the web app using Node.js.

Node.js was the runtime used to install and run the Firebase CLI, which was then used to deploy the web app through Firebase Hosting. 

# What I Learned
Throughout this project, I learned multiple new skills through using Google Firebase, coding in HTML and reinforcing my current coding skills in the Arduino IDE.

# Google Firebase
- This was my first time building a web app, by using Google's Firebase, the process was simplified and much easier to follow.
- I learned how to create a backend, how to connect my backend to a frontend and ESP32 code and how to host it live.

# HTML
- I had prior experience with HTML in the past and this project allowed to truly test my coding capabilities inside of HTML
- Throughout this process, I was able to pick up a new skill in creating charts in HTML using Chart.js

# Arduino IDE
- This project created many debugging sessions with trying to get the Realtime Database communicating with the ESP32 code, but ultimately strengthened my coding abilities.
- Additionally, my abilities to create complex functions were strengthened as I had to use a variety of data bases together.

# Future Improvements
To improve this project in the future, a smart plug could be coded using ESPHome, possibly allowing an LED Growth Light to be added to the project. Additionally, I would like to add a temperature sensor and weather forecasts in my area to help determine whether the plants should be watered at a certain time.

# References
- [Add Firebase to your JavaScript project](https://firebase.google.com/docs/web/setup) - referenced for initializing firebase in the frontend
- [Installation & Setup in JavaScript](https://firebase.google.com/docs/database/web/start) - referenced for reading/writing data from the realtime database into the frontend
- [ESP32 NTP Client-Server: Get Date and Time (Arduino IDE)](https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/) - referenced for creating the NTP time sync
- [How to make Automatic Plant Watering System using Arduino UNO and Soil Sensor || Techie Lagan](https://www.youtube.com/watch?v=iwkE_HWU-6M) - Creator: Techie Lagan, referenced for physical wiring of the irrigation kit
- [Arduino Firebase project: send data to Firebase using Nodemcu esp8266, firebase library, auth, iot/Electronic Clinic](https://www.youtube.com/watch?v=oS7fdTDajmw) - referenced for adding the realtime database to the ESP32 code

# Demo Videos
# General Use
https://github.com/user-attachments/assets/9fa8de62-88b0-43d6-bb88-db7d45149c7e

# Manual Dispense


# Scheduled Dispensing
