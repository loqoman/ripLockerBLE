// Purpose => Provide a framework to manage, decode, and encode messages sent between the two boards

#include <Arduino.h> // Needed for the String object

// E.G messageType =
// Caps for struct?
struct Message {
    // Pulled directly from the README
    enum messageType {REQBATT, KEEPALIVE, REQREAD, REQRUONDTRIP};

    double timeCreated;
    double timeReceived;
    double payload;

    messageType type;



    // QUESTION: Should there be constructors that are defiend without a known usecase??
    Message(double time) {timeCreated = time;};
    Message(double time, messageType inputType) {timeCreated = time; type = inputType;};


    String encodeToWire(double myTime) {
        // TODO: Struct --> String 
    }

    Message decodeFromWire() {
        // TODO: String --> Struct
    }

};
