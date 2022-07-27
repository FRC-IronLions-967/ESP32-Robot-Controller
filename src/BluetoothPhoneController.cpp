#include "BluetoothPhoneController.h"
#include <functional>

team967::BluetoothPhoneController* team967::BluetoothPhoneController::inst = nullptr;
bool team967::BluetoothPhoneController::hasData = false;

team967::BluetoothPhoneController& team967::BluetoothPhoneController::createInstance(char* name) {
  if(inst != nullptr) delete inst;

  inst = new BluetoothPhoneController(name);
  return *inst;
}

team967::BluetoothPhoneController::BluetoothPhoneController(char* name) {
    // TODO copy this?? probably doesn't matter if it's a literal, can't think of a time this would ever be changed
    btName = name;

    state = new BtPacket();
    state->joystickVals = new int8_t[1];
    state->buttonVals = new bool[1];

    hasData = false;
}

team967::BluetoothPhoneController::~BluetoothPhoneController() {
  delete state;
}

bool team967::BluetoothPhoneController::begin() {
    bt.register_callback(this->btCallback);

    return bt.begin(btName);
}

bool team967::BluetoothPhoneController::isConnected() {
    return connected;
}

uint8_t team967::BluetoothPhoneController::getNumAxes() {
    return 2 * state->numJoysticks;
}

int8_t team967::BluetoothPhoneController::getJoystickAxis(uint8_t id) {
    if(!hasData || id >= 2 * state->numJoysticks) return 0;

    return state->joystickVals[id];
}

uint8_t team967::BluetoothPhoneController::getNumJoysticks() {
    if(!hasData) return 0;
    return state->numJoysticks;
}

int8_t team967::BluetoothPhoneController::getJoystickX(uint8_t id) {
    if(!hasData || id >= state->numJoysticks) return 0;

    return state->joystickVals[2 * id];
}

int8_t team967::BluetoothPhoneController::getJoystickY(uint8_t id) {
    if(!hasData || id >= state->numJoysticks) return 0;

    return state->joystickVals[(2 * id) + 1];
}

uint8_t team967::BluetoothPhoneController::getNumButtons() {
    return state->numButtons;
}

bool team967::BluetoothPhoneController::isButtonPressed(uint8_t id) {
    if(!hasData || id >= state->numButtons) return false;

    return state->buttonVals[id];
}

void team967::BluetoothPhoneController::updateState(BtPacket* data) {
//  delete state;
  state = data;
}

void team967::BluetoothPhoneController::setConnected(bool c) {
  connected = c;
}

void team967::BluetoothPhoneController::btCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t* param) {
    switch(event) {

        // a new device has connected
        case ESP_SPP_SRV_OPEN_EVT:
            inst->setConnected(true);
            break;

        // device has disconnected
        case ESP_SPP_CLOSE_EVT:
            inst->setConnected(false);
            team967::BluetoothPhoneController::hasData = false;
            break;

        // new data has become available
        case ESP_SPP_DATA_IND_EVT:
        {
            static BtPacket packet;
            uint16_t index = 0;
            if(param->data_ind.len < 4) break;
            packet.type = param->data_ind.data[index++];
            packet.rev = param->data_ind.data[index++];
            packet.numJoysticks = param->data_ind.data[index++];
            packet.numButtons = param->data_ind.data[index++];
            if(param->data_ind.len < (packet.numButtons / 8) + (2 * packet.numJoysticks) + 4) break;
            if(!team967::BluetoothPhoneController::hasData) {
                packet.joystickVals = new int8_t[2 * packet.numJoysticks];
                packet.buttonVals = new bool[packet.numButtons];
            }
            for(uint8_t i = 0; i < 2 * packet.numJoysticks; i++) {
              packet.joystickVals[i] = param->data_ind.data[index++];
            }
            uint8_t i;
            for(i = 0; i < packet.numButtons / 8; i++) {
              for(uint8_t j = i; j < 8; j++) {
                if(param->data_ind.data[index] & (1 << (7 - j))) {
                  packet.buttonVals[(8 * i) + j] = true;
                } else {
                  packet.buttonVals[(8 * i) + j] = false;
                }
              }
              index++;
            }

            if(packet.numButtons % 8 != 0) {
              for(uint8_t j = 0; j < 8; j++) {
                if(param->data_ind.data[index] & (1 << (7 - j))) {
                  packet.buttonVals[(8 * i) + j] = true;
                } else {
                  packet.buttonVals[(8 * i) + j] = false;
                }
              }
            }
            index++;
            inst->updateState(&packet);

            team967::BluetoothPhoneController::hasData = true;
          }
            break;

        default:
            break;
    }
}
