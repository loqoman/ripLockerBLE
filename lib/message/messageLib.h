// Purpose => Provide a framework to manage, decode, and encode messages sent between the two boards

#include <Arduino.h> // Needed for the String object

#ifdef PERIPHERAL
const String DEVICE = "PERIPHERAL";
#endif

#ifdef CLIENT
const String DEVICE = "CLIENT";
#endif
// E.G messageType =
// Caps for struct?
int decodingBuffer[3];

struct Message {
    // Pulled directly from the README
    enum messageType {REQBATT, KEEPALIVE, REQREAD, REQRUONDTRIP};

    double timeCreated;
    double timeReceived;
    double payload; // I.E 'data'

    messageType type;



    // QUESTION: Should there be constructors that are defiend without a known usecase??
    Message(double time) {timeCreated = time;};
    Message(double time, messageType inputType) {timeCreated = time; type = inputType;};


    String encodeToWire(double myTime) {
        // TODO: Struct --> String 

        // FORMAT   : "[TX:<DEVICE>][type:<messageType>][payload:<payload>]"
        // EXAMPLE  : "[TX:client][type:REQBATT][payload:0]"
    
        // Each part individually
        String identificationStr = String("[TX:") + String(DEVICE) + String("]");
        String typeStr = String("[type:") + String(type) + String("]");
        String payloadStr = String("[payload:") + String(payload) + String("]");

        // Final Message
        String finalMessage = identificationStr + typeStr + payloadStr;
        
        return finalMessage;

    }

    Message decodeFromWire(String inputStringFromWire) {
        // TODO: Have checking
        // Oh boy this one's gonna be interesting
    
        // Create the object we're going to return
        Message returnDecoded(millis());
        String deviecStr;
        String typeStr;
        String payloadStr;

        // WRITE BETTER CODE
        while (inputStringFromWire.length() >= 0) {
            int startLoc = inputStringFromWire.indexOf(":");
            int endLoc = inputStringFromWire.indexOf("]");
        
            String paramTypeStr = inputStringFromWire.substring(1, startLoc);
            String paramBodyStr = inputStringFromWire.substring(startLoc, endLoc);

            // TODO: There's almost 100% a better way to do with with an enum switch satement
            if (paramTypeStr == String("TX")) {
                deviecStr = paramBodyStr;
            } else if (paramTypeStr == String("type")) {
                typeStr = paramBodyStr;
            } else if (paramTypeStr == String("payload")) {
                payloadStr = paramBodyStr;
            } // This is where another paramater would go when created

            // "pops" the firest paramater in the message off the message
            inputStringFromWire.remove(0, paramBodyStr.length() + 3);

        }

        

    }
};
