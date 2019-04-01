# WindTel
  The Wind Telemetry project, or WindTel for short, focuses on automating the data acquisition process from a wind tunnel, in this case,
  the wind tunnel located in the Civil Engineering building at the University of Puerto Rico at Mayaguez. This will be done through an 
  embedded system based on micro-controllers, in this case the MSP432P401R, where it will be separated into 4
  modules: 
  1. Master Module - The Master Module will serve as an intermediary micro-controller that will gather the data acquisition from its 
  micro-controller slaves. This module will also have 3 sub-modules:
    1.1. Control Sub-Module - A closed loop control system composed of 2 relays with the purpose of turning on and off the wind blower, as
    well as to manage its velocity.
    1.2. User Interface Sub-Module - A graphic Liquid Crystal Display (LCD) that can be managed by the user to operate the wind tunnel. This 
    will have a variety of options such as: perform experiments, calibration of the system, view results obtained from experiments, and more.
    1.3. Wifi Sub-Module - The Wifi Sub-Module is a hardware development board that will enable the connection to the internet in order to be
    able to store results in the Civil Engineering local database server. In general, it will manage the transmission of data to the 
    database server.
  2. Pressure Module - The Pressure Module will collect the barometric pressure using barometric pressure sensors, in this case the BMP280.
  3. Balance Module - The Balance Module will collect 5 force measurements utilizing an electronic balance located beneath the wind tunnel 
  test section.
  4. Aerodynamic Measurements Module - The Aerodynamic Measurements Module consist of an temperature and humidity sensor (DHT22 sensor), and 
  the anemometer which measures the wind speed inside the wind tunnel.
  
  Another way to operate the wind tunnel will be through a mobile, where the user will have more options than when using the hardware LCD user
  interface, where among the additional features will be to view the results gathered using data visualization tools. This mobile application
  will then have a back end application with the rest api implementation to connect with the database server, using the hardware wifi 
  development board remotely with internet connection.
     
# WindTel back-end application
The back-end application will consist of the rest-api implementation and the connection with the database server, in this case with the one
located at the in the Civil Engineering building.

The ER Diagram entities and the corresponding relationships are as followed:
1. Researcher - Performs - Experiment is a many to many relationship where a researcher can perform many experiments, and an experiment can 
 be performed by many researchers.
2. Experiment - Acquires - Measurements is a one to many relationship since the measurements will depend on the environment in which the 
experiment was conducted. It may be possible that similar or even equal results were generated on different times or day, but not necessarily.
3. Measurements - Contains - Pressure Points is a one to many relationship due to that the amount of pressure points that can be used currently
 is 16, but this may be expanded in the near future. The pressure points will belong to one measurements acquisition since it is not common or
 it would be incorrect to say that the pressure measurements can be the same under different environmental conditions. 
