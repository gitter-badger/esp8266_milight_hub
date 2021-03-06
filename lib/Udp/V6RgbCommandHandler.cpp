#include <V6RgbCommandHandler.h>

bool V6RgbCommandHandler::handleCommand(
    MiLightClient* client, 
    uint16_t deviceId,
    uint8_t group,
    uint32_t command,
    uint32_t commandArg)
{
  const uint8_t cmd = command & 0xFF;
  const uint8_t arg = commandArg >> 24;
  
  client->prepare(MilightRgbConfig, deviceId, 0);
  
  if (cmd == V2_RGB_COMMAND_PREFIX) {
    switch (arg) {
      case V2_RGB_ON:
        client->updateStatus(ON);
        break;
        
      case V2_RGB_OFF:
        client->updateStatus(OFF);
        break;
        
      case V2_RGB_BRIGHTNESS_DOWN:
        client->decreaseBrightness();
        break;
        
      case V2_RGB_BRIGHTNESS_UP:
        client->increaseBrightness();
        break;
        
      case V2_RGB_MODE_DOWN:
        client->previousMode();
        break;
        
      case V2_RGB_MODE_UP:
        client->nextMode();
        break;
        
      case V2_RGB_SPEED_DOWN:
        client->modeSpeedDown();
        break;
        
      case V2_RGB_SPEED_UP:
        client->modeSpeedUp();
        break;
        
      default:
        return false;
    }
    
    return true;
  } else if (cmd == V2_RGB_COLOR_PREFIX) {
    client->updateColorRaw(arg);
    return true;
  }
  
  return false;
}