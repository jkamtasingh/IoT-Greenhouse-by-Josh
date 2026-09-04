# IoT-Greenhouse-by-Josh
An Internet of Things (IoT) greenhouse powered by the ESP32 Dev Module.

# Technologies used
Software
- Arduino IDE (C++)
  - Arduino Libraries: ESP32 library, Firebase Arduino Client Library for ESP8266 and ESP32, and Firebase ESP32 Client
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

Then, I began adding the database code to the Arduino code, initially adding the current status of the pump, moisture, and eventually adding the manual dispense data and plants moisture levels.

After confirming that the database is connected to the ESP32 and is actively reading/storing data, I began designing the frontend using HTML and Visual Studio Code.

The API Key and database URL had to be added to the frontend to link the Realtime Database and web app together.

Chart.js was utilized in creating the frontend as it would update with the plant's moisture levels every 5 minutes.

Going back to the Arduino IDE, arrays were created to check the current time and functions were created to manually dispense water, and pull up the current time and update the scheduled times.

Now that the ESP32 code, frontend and backend were working cohesively, it was time to host the web app using Node.js.

Node.js was the runtime used to install and run the Firebase CLI, which was then used to deploy the web app through Firebase Hosting. 

# What I Learned

