// #include <ESP32S3MCPWMChannel.h>

// team967::ESP32S3MCPWMChannel::ESP32S3MCPWMChannel(int mcpwmId, int pin0, int pin1, int resolution) :
//                                         pin0(pin0), pin1(pin1), resolution(resolution) {

//     // TODO this could probably be changed with some prescalers to actually try and hit a certain freq
//     frequency = MCPWM_REFERENCE_FREQ / (1 << resolution);
                                        
//     timer_config = {
//         .group_id = mcpwmId,
//         .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
//         .resolution_hz = MCPWM_REFERENCE_FREQ, // 80 MHz reference clock
//         .period_ticks = (1 << resolution),
//         .count_mode = MCPWM_TIMER_COUNT_MODE_UP
//     };

//     oper_config = {
//         .group_id = mcpwmId
//     };

//     comp_config = {
//         .flags.update_cmp_on_tez = true
//     };

//     gen0_config = {
//         .gen_gpio_num = pin0
//     };

//     gen1_config = {
//         .gen_gpio_num = pin1
//     };
// }

// team967::ESP32S3MCPWMChannel::~ESP32S3MCPWMChannel() {

// }

// void team967::ESP32S3MCPWMChannel::begin(void) {
//     if(initDone) return;

//     ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

//     ESP_ERROR_CHECK(mcpwm_new_operator(&oper_config, &oper));

//     ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

//     ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comp_config, &comp));

//     ESP_ERROR_CHECK(mcpwm_new_generator(oper, &gen0_config, &gen0));
//     ESP_ERROR_CHECK(mcpwm_new_generator(oper, &gen1_config, &gen1));

//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen0, 0, true));
//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen1, 0, true));

//     ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
//     ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));

//     initDone = true;
// }

// void team967::ESP32S3MCPWMChannel::forward(uint32_t duty) {
//     ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, duty));

//     // pin 0 - PWM
//     ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(
//         gen0, MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));

//     ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
//         gen0, MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comp, MCPWM_GEN_ACTION_LOW)));

//     // pin 1 - LOW
//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen1, 0, true));
// }

// void team967::ESP32S3MCPWMChannel::reverse(uint32_t duty) {
//     ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comp, duty));

//     // pin 1 - PWM
//     ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(
//         gen1, MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));

//     ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(
//         gen1, MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comp, MCPWM_GEN_ACTION_LOW)));

//     // pin 0 - LOW
//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen0, 0, true));
// }

// void team967::ESP32S3MCPWMChannel::brake(void) {
//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen0, 1, true));
//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen1, 1, true));
// }

// void team967::ESP32S3MCPWMChannel::coast(void) {
//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen0, 0, true));
//     ESP_ERROR_CHECK(mcpwm_generator_set_force_level(gen1, 0, true));
// }