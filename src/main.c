/*
 * Copyright (c) 2014-2018 Cesanta Software Limited
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mgos.h"
#include "mgos_rpc.h"
#include "mgos_wifi.h"
#include "mgos_http_server.h"

#define LED_PIN 2


bool col1_en = 0, col2_en = 0, col3_en = 0, col4_en = 0, col5_en = 0, col6_en = 0, col7_en = 0, col8_en = 0, col9_en = 0, col10_en = 0;
bool  col11_en = 0, col12_en = 0, col13_en = 0, rc_1970day = 0, rc_thisday = 0;
 

static void timer_cb(void *arg) {

#ifdef LED_PIN
  mgos_gpio_toggle(LED_PIN);
#endif
  (void) arg;
}

// don't forget to state the ssid and pass
const struct mgos_config_wifi_sta cfg = {.enable = true, .ssid = "", .pass = ""};

static void setting_modifier(struct mg_rpc_request_info *ri, void *cb_arg,
                   struct mg_rpc_frame_info *fi, struct mg_str args) {
 
  if (json_scanf(args.p, args.len, ri->args_fmt, &col1_en, &col2_en, &col3_en, &col4_en, &col5_en, &col6_en, &col7_en, &col8_en, &col9_en, &col10_en, &col11_en, &col12_en, &col13_en, &rc_1970day, &rc_thisday) == 15) {
    mg_rpc_send_responsef(ri, "OK");
	LOG(LL_INFO, ("setting json file received"));
	json_fprintf("/data/setting.json", "{col1_en: %B, col2_en: %B, col3_en: %B, col4_en: %B, col5_en: %B, col6_en: %B, col7_en: %B, col8_en: %B, col9_en: %B, col10_en: %B, col11_en: %B, col12_en: %B, col13_en: %B, rc_1970day: %B, rc_thisday: %B}", col1_en, col2_en, col3_en, col4_en, col5_en, col6_en, col7_en, col8_en, col9_en, col10_en, col11_en, col12_en, col13_en, rc_1970day, rc_thisday);
  } else {
    mg_rpc_send_errorf(ri, -1, "Bad request");
  }
  
  (void) cb_arg;
  (void) fi;
}


enum mgos_app_init_result mgos_app_init(void) {
#ifdef LED_PIN
  mgos_gpio_setup_output(LED_PIN, 0);
#endif
	
	
	
  mgos_set_timer(1000 /* ms */, MGOS_TIMER_REPEAT, timer_cb, NULL);
  //wifi configuration
  mgos_wifi_setup_sta(&cfg);
  
   mg_rpc_add_handler(mgos_rpc_get_global(), "setting"
  ,"{col1_en: %B, col2_en: %B, col3_en: %B, col4_en: %B, col5_en: %B, col6_en: %B, col7_en: %B,  col8_en: %B, col9_en: %B, col10_en: %B, col11_en: %B, col12_en: %B, col13_en: %B, rc_1970day: %B, rc_thisday: %B}"
  , setting_modifier, NULL);
  return MGOS_APP_INIT_SUCCESS;
}
