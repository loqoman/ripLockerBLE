# ripLockerBLE

### Client (I.E Server) (What goes outside the chamber)

- The part that controls the periphral

**Charateristics**
- Always on
    - Radio is always on
    - CPU is always on
- Has constant conncetion to the RaspberryPi (working name for the device controlling the client)

### Peripheral (What goes IN the chamber)

### Message Structure

**Order of Operations**

1. Client scans for BLE beacons with the bleUART service
2. Client makes contact (`connect()`) with the peripheral
3. Client logs the connection
4. 

**Types of Messages**

- Set Next Wakeup
- Keep Alive
    - Just exists to see if there is someone on the other end. Acts as a verifcation of the Message format.
- Request for Reading
    - Asking the peripheral for the current reading from the peripheral
- Request Battery life
    - Asking the peripheral for the current estimated battery life 
- Request Time of Transit 
    - Sending a time to the peripheral 
    - Asking the peripheral to reutrn the time of travel for the message


**Communication Protocol**

- The primary method of communication (A smalls straw) is through `bleuart.write(String input)`. We have to be able to break that down all the complicated classes / objects for `peripheralManager` between `clientManager`. Assembling a `struct` or a `Class` on either end is not very useful as a communication framework.

# Code

