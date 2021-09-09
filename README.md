# Identification Of Mechanical Failures In Rotating Machines Through Cloud-based Vibrational Signature Analysis
* The project's objective was to develop a system to identify mechanical failures in rotating machines, by means of frequency sensor reading, analyzing the vibration of the machines, and also to make this identification remote by sending data to the cloud.

## Materials & Methods

The STM32F401RE and ESP32 Microcontrollers were used to develop the project, along with the STEVAL BFA001V1B frequency analysis sensor (STMicroeletronics). For the development in the cloud were used the Microsoft Azure platforms for the receiving and processing data and PowerBI for visualization

<h4 align="center">
<img src="https://github.com/jvictorrr/IDENTIFICATION-OF-MECHANICAL-FAILURES/blob/307bdf6e8f6872d504ec1207617d9b687e3c1d46/Imagens/stm32.jpg" width="300"><br>
        STM32F401RE
 

 
 <img src="https://github.com/jvictorrr/IDENTIFICATION-OF-MECHANICAL-FAILURES/blob/307bdf6e8f6872d504ec1207617d9b687e3c1d46/Imagens/steaval.jpg" width="300"><br>
        STEVAL-BF001V1B
 
  <img src="https://github.com/jvictorrr/IDENTIFICATION-OF-MECHANICAL-FAILURES/blob/307bdf6e8f6872d504ec1207617d9b687e3c1d46/Imagens/placa_doit_esp32_-_esp-wroom-32_-_wifi_bluetooth.jpg" width="300"><br>
       ESP32
 
 
</h4>


## Development

The development of the project was done in steps, since each small step was extremely important for the whole project, at first a study of the base codes provided by the platform manufacturer of the frequency analysis sensor shown in the figure below, the main change needed in the codes provided would be to make a cleanup in the interface implemented for communication with the user via command prompt, to only display the necessary data in order to implement the JSON compression format 

<h4 align="center">
<img src="https://github.com/jvictorrr/IDENTIFICATION-OF-MECHANICAL-FAILURES/blob/307bdf6e8f6872d504ec1207617d9b687e3c1d46/Imagens/antes.PNG" width="300"><br>
        Source Code 
 

 
 <img src="https://github.com/jvictorrr/IDENTIFICATION-OF-MECHANICAL-FAILURES/blob/307bdf6e8f6872d504ec1207617d9b687e3c1d46/Imagens/depois.PNG" width="300"><br>
        Code after change
 
 
</h4>

The implementation of this form was extremely important due to the need for communication between the devices, due to limitations, this transfer of data from one microcontroller to the other, as the Esp32 has wifi connection. The communication between devices was done via serial communication, the STM32 -F401 RE microcontroller performed the reading along with the sensor kit in a compressed form sent this data via serial to the Esp32, which due to its wifi connection module, could connect directly to the Azure IoT Hub, being responsible only for making the bridge between the sensors available in the STM with the IoT module.

## Hardware 

![conexao](https://user-images.githubusercontent.com/39633395/132637567-ea1be91b-2f60-4315-8bb8-0c38856bc9f3.png)

## Data Flowchart

![sistema_completo](https://user-images.githubusercontent.com/39633395/132637685-a37b2ce0-06de-4428-9a71-d0e49b341c3e.png)


## Results

With all the hardware and software procedures it was possible to finalize the development of an IoT platform with communication between the Frequency Analysis Sensor, with real-time sampling. Due to the pandemic restrictions the readings obtained were only simulated, not being possible to make real readings in the spinning machine that was in the Laboratory of Electronic Instrumentation and Control (LIEC) - UFCG. Therefore, even with the application of a simulated frequency it was obtained the result of Figure 


![power_bi](https://user-images.githubusercontent.com/39633395/132638030-85912d60-e136-40cd-9ad9-a00419bccdd1.jpeg)



