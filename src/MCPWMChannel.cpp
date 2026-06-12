#include <MCPWMChannel.h>

team967::MCPWMChannel::MCPWMChannel(int mcpwmId, int channel, int pin0, int pin1, int frequency, int resolution) :
                                        mcpwmId(mcpwmId), channel(channel), pin0(pin0), pin1(pin1), frequency(frequency), resolution(resolution) {

}

team967::MCPWMChannel::~MCPWMChannel() {
    
}