# iot-restaurant-nodemcu

## **introduction**

This is a **college assignment** with the objective of make the payments of a restaurant with Internet of Things concepts.

This repo it's the code of the nodemcu and some reference links.

## **other parts of the project**

1. [App made with Ionic 4](https://github.com/andreiox/iot-restaurant-app)
2. [Backend made with Django](https://github.com/andreiox/iot-restaurant-backend)

## **description**

The code works in the following fashion

1. The nodemcu connect to a wifi network via WiFiManager library
2. When the card is presented, we get the rfid number
3. We make a request to the backend to make a transaction with de rfid number
4. Handle the response
    - If the request return code 200 means that the transation was created without problems and we show the feedback for the client with the green light
    - If not, then the transaction wasn't created and we show the feedback for the client with the red light

## **reference links**

We a custom pinout for this project following these articles

1. [ESP32 com RFID: Controle de Acesso](https://www.fernandok.com/2018/02/esp32-com-rfid-controle-de-acesso.html)
2. [MFRC522 RFID Reader Interfaced With NodeMCU](https://www.instructables.com/id/MFRC522-RFID-Reader-Interfaced-With-NodeMCU/)
3. [Wireless RFID Door Lock Using Nodemcu](https://www.instructables.com/id/Wireless-RFID-Door-Lock-Using-Nodemcu/)
