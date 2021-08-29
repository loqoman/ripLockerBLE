# RipeLockerBLE

## Introduction
---
RipeLockerBLE is a research embedded design project done by Darwin Clark during the summer of 2021 for [RipeLocker LLC](https://ripelocker.com/). The goal of this project was primarily to act as real-world design experience, however it also showed an alternative design path to solve similar power and communication requirements.


## A Full-System View
---
<div>
<p align="center">
 <strong>Full-System Overview Flowchat V2</strong> 
 <br>
 <img src="https://raw.githubusercontent.com/loqoman/ripeLockerBLE/main/docs/assets/HighLevelDiagramV2.png" alt="Full-System Overview Flowchat V2" width="500px"/>
 <br>
</p>

## Individual Modules
---
### Client (I.E Server) (What goes outside the chamber)

- The part that controls the periphral

**Charateristics**
- Always on
    - Radio is always on
    - CPU is always on
- Has constant conncetion to the RaspberryPi (working name for the device controlling the client)

#### Serial Control of the Client

**Debugging**
Assuming that the assoicated control program / setup is on the fritz, a more bare-bones control scheme can be used with the linux tool `screen`. With the client board plugged into the Raspberry Pi via USB, running the following command will open a terminal emulation of the serial port.

```
screen /dev/ttyUSB0 115200
```

From there, messages can be simply typed into the terminal to be sent to the client. There are a couple of caviats to this however:
    - The default timeout for `screen` may inturrupt you when typing mid-message, resulting in a botched message to the client
    - 

### Peripheral (What goes IN the chamber)

- Connected to the MODBUS chip.
- Required to sleep for extended periods of time



### Message Liberary

**Order of Operations**

1. Client scans for BLE beacons with the bleUART service
2. Client makes contact (`connect()`) with the peripheral
3. Client logs the connection
4. Client sends required messages to peripheral
    - (Sample Message Order)
    1. `KEEPALIVE`
    2. `REQBATT`
    3. `REQREAD`
    4. `SETSLEEPTIME`
    5. `GOTOSLEEP`
5. Peripheral disconnects from client
6. Client continues to active scan waiting for peripheral to wake up

**Types of Messages**

- Set Next Wakeup
    - Sets the time that will be used in the `softwareTimer()` inturrupt once the peripheral receives the "Go to Sleep" message
- Keep Alive
    - Just exists to see if there is someone on the other end. Acts as a verifcation of the Message format.
- Request for Reading
    - Asking the peripheral for the current reading from the peripheral
- Request Battery life
    - Asking the peripheral for the current estimated battery life 
- Request Time of Transit 
    - Sending a time to the peripheral 
    - Asking the peripheral to reutrn the time of travel for the message
    - This message will likely be collated with the "Keep Alive" message
- Go to Sleep
    - Instructus the peripheral that there is no more information needed, and to re-enter a sleep mode.
        - N.B, "Go to Sleep" is different from "Set Next Wakeup


# Code

## Formatting

The codebase employs the following formatting decisions:

- Tabs: 4 spaces
- Brackets: Same line
