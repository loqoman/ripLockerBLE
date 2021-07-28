// Purpose => Provide a framework to manage, decode, and encode messages sent between the two boards

#include <Arduino.h> // Needed for the String object

#ifdef PERIPHERAL
const String DEVICE = "PERIPHERAL";
#endif

#ifdef CLIENT
const String DEVICE = "CLIENT";
#endif

// Caps for struct?
int decodingBuffer[3];

// It is implied that each message is sourced from the client and is responded to by the peripheral
// A message has two timestamps assoicated with it: The time it was sent and the time it was responded to
struct Message {
    // Pulled directly from the README
    enum messageType {REQBATT, KEEPALIVE, REQREAD, REQRUONDTRIP};

    double timeSent;        // in ms
    double timeResponded;   // in ms
    double payload; // I.E 'data'

    messageType type;



    // QUESTION: Should there be constructors that are defiend without a known usecase??
    Message(double time) {timeSent = time;};
    Message(double time, messageType inputType) {timeSent = time; type = inputType;};


    String encodeToWire(double myTime) {
        // TODO: Struct --> String 
        timeSent = myTime;

        // FORMAT   : "[TX:<DEVICE>][type:<messageType>][payload:<payload>]"
        // EXAMPLE  : "[TX:client][type:REQBATT][payload:0]"
    
        // Each part individually
        // This code is scaleable -- Whenever we add a new charateristic we just add another line here
        String identificationStr = String("[TX:") + DEVICE + String("]");

        String timeStr = String("[sentTime:") + timeSent + String("]");
        String typeStr = String("[type:") + String(type) + String("]");
        String payloadStr = String("[payload:") + String(payload) + String("]");

        // Final Message
        String finalMessage = identificationStr + timeStr + typeStr + payloadStr;
        
        return finalMessage;

    }

    static Message decodeFromWire(String inputStringFromWire) {
        // TODO: Check that the decoder of the message is not the #DEVICE as the message src.
        // Oh boy this one's gonna be interesting
    
        // Create the object we're going to return
        Message returnDecoded(millis());
        String deviecStr;
        String typeStr;
        String payloadStr;
        String timeSent;

        // WRITE BETTER CODE
        while (inputStringFromWire.length() > 0) {
            int startLoc = inputStringFromWire.indexOf(":");
            int endLoc = inputStringFromWire.indexOf("]");
        
            String paramTypeStr = inputStringFromWire.substring(1, startLoc);
            String paramBodyStr = inputStringFromWire.substring(startLoc+1, endLoc);

            // TODO: There's almost 100% a better way to do with with an enum switch satement
            if (paramTypeStr == String("TX")) {
                deviecStr = paramBodyStr;
            } else if (paramTypeStr == String("type")) {
                typeStr = paramBodyStr;
            } else if (paramTypeStr == String("payload")) {
                payloadStr = paramBodyStr;
            } else if (paramTypeStr == String("sentTime")) {
                timeSent = paramBodyStr;
            } else  { // This is where another paramater would go when created
                String error = String("[") + DEVICE + String("]") + String(" Error when decoding string. Found an unknown paramType:");
                Serial.println(error);
                Serial.println(paramTypeStr);
            }    

            // "pops" the firest paramater in the message off the message
            inputStringFromWire.remove(0, endLoc + 1); // pop() characters from 0 to the end of the body

        };

        returnDecoded.timeSent = timeSent.toFloat();
        returnDecoded.payload = payloadStr.toFloat();
        returnDecoded.type = static_cast<messageType>(typeStr.toInt()); // Casts the int to an enum messageType
        
        

        return returnDecoded;
    }
};
