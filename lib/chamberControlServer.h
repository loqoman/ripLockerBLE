/*
 * Contains code for the server which is responsible for controling the BLE device inside the container
 *   - This code is run on the 'client' (06.30 terminology)
 *   - Responsible for knowing when to wake up the 'peripheral'
 *   - Reponsible for communicating with the rPI
 *   - Responsible for handing data measurements and indexing them

*/
#include <bluefruit.h> //  I'll


class controlServer {
    public:
    private:
        double myTime;

        typedef struct {
            // todo
        } outogingMessage;

        typedef struct {

        } incomingMessage;
}