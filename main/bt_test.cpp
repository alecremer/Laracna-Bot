// #include <stdint.h>//lib for ints i-e int8_t upto 1int64_t
// #include <string.h> //for string data i-e char array
// #include <stdbool.h> //for boolean data type
// #include <stdio.h> // macros,input output, files etc
// #include "nvs.h" //non volatile storage important for saving data while code runs
// #include "nvs_flash.h" // storing in nvs flash memory
// #include "freertos/FreeRTOS.h" //freertos for realtime opertaitons
// #include "freertos/task.h" // creating a task handler and assigning priority
// #include "esp_log.h" // printing out logs info this is to avoid printf statment
// #include "esp_bt.h" //bluetooth related data structs and important files init cb etc
// #include "esp_bt_main.h" // initialize the Bluetooth stack, enable Bluetooth functionality, and retrieve the device address on ESP32
// #include "esp_gap_bt_api.h" //is used to set the scan mode for the device after the Bluetooth stack is initialized and enabled
// #include "esp_bt_device.h" //device address and device name for bluetooth
// #include "esp_spp_api.h" // are used to manage SPP connections, perform service discovery, and handle data transmission over SPP.
// #include "time.h" //time funtions
// #include "sys/time.h"//time funtions

// uint16_t my_handle; /* declaring this publically to save "handle" value which is address of mobile
// phone and mac address so it can be written in later function of esp_spp_write to write from esp32
// to mobile
// */
// const char *TAG = "Bluetooth"; //tag for LOGs
// #define DEVICE_NAME "ALE_DEVICE"
// #define SPP_SERVER_NAME "ALE_SERVER"
// /*note: here server name and device name are two different things
// Server Name" (SPP_SERVER_NAME) is the name used to identify the Bluetooth SPP server running on the ESP32.
// Device Name" (DEVICE_NAME) is the name used to identify the ESP32 Bluetooth device itself to other Bluetooth devices during the discovery process*/
// static const esp_spp_mode_t esp_spp_mode = ESP_SPP_MODE_CB;/*When using ESP_SPP_MODE_CB, it means that the Serial Port Profile will be set 
// to use a callback-based mechanism for handling data and events during the Bluetooth communication.
// */
// static const esp_spp_sec_t sec_mask = ESP_SPP_SEC_AUTHENTICATE;/* By setting sec_mask to ESP_SPP_SEC_AUTHENTICATE,
// it means that authentication is required before establishing the SPP connection, but no encryption is used after the devices are paired.*/
// static const esp_spp_role_t role_slave = ESP_SPP_ROLE_SLAVE;/*
// By setting role_slave to ESP_SPP_ROLE_SLAVE, it means that the ESP32 device will act as the slave in the SPP connection. 
// The slave role is typically used when the ESP32 is waiting for incoming connections from another device acting as the master.*/

// static void esp_spp_cb(esp_spp_cb_event_t event,esp_spp_cb_param_t *param){ /*
// in funtion there are two parameters event and *param event is for using
// if else statment to keep letting event handler know which event is occuring by 
// updating values in background and param provides us information about device 
// we are connected to which is phone. param is responsible for sending and receiving data*/
// my_handle = param->write.handle; /*we declared my_handle above now we are saving 
// write handle values so it saves the writing address while writing data in separate funtion*/

// int num_connections = 0;
// switch (event){ //using switch case cause we need to use if statements
// case ESP_SPP_INIT_EVT: //if event matches enumerated value
//   if(param->init.status == ESP_SPP_SUCCESS){ //esp_spp_status enum if is equal to 0
//   ESP_LOGI(TAG,"ESP_SPP_INIT_EVNT"); //log value shows this event
//   esp_spp_start_srv(sec_mask, role_slave, 0, SPP_SERVER_NAME); /*for starting we declare
//   security method and role of esp32 and its server name*/}else {
//               ESP_LOGE(TAG, "ESP_SPP_INIT_EVT status:%d", param->init.status);
//           }//incase of failure it prints status value
//       break;
// case ESP_SPP_DISCOVERY_COMP_EVT:
//      ESP_LOGI(TAG, "ESP_SPP_DISCOVERY_COMP_EVT"); //discovery event occuring
//       break;
// case ESP_SPP_OPEN_EVT:
//         ESP_LOGI(TAG, "ESP_SPP_OPEN_EVT"); //event is open for connections
//         if (num_connections < 3) {
//                 num_connections++;
//             } else {
//                 ESP_LOGE(TAG, "Max connections reached. Rejecting new connection.");
//                 esp_spp_disconnect(param->open.handle); /* if connections reaches more than 
// required connections it will disconnect*/
//             }
//         break;
// case ESP_SPP_CLOSE_EVT:
//         ESP_LOGI(TAG, "ESP_SPP_CLOSE_EVT status:%d handle:%d close_by_remote:%d", param->close.status,
//                  param->close.handle, param->close.async);
//         break; /*when esp diconnects this event closes*/
// case ESP_SPP_START_EVT: // esp spp event when starts
//         if (param->start.status == ESP_SPP_SUCCESS) {
//             ESP_LOGI(TAG, "ESP_SPP_START_EVT handle:%d sec_id:%d scn:%d", param->start.handle, param->start.sec_id,
//                      param->start.scn);
//             esp_bt_dev_set_device_name(DEVICE_NAME); //device name goes here
//             esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);/*
//  This means that the Bluetooth device will be connectable, allowing other Bluetooth devices to establish connections with it.
//  This means that the Bluetooth device will be discoverable, allowing other devices to find it during the discovery process.*/
//         } else {
//             ESP_LOGE(TAG, "ESP_SPP_START_EVT status:%d", param->start.status);
//         }
//         break;
// case ESP_SPP_CL_INIT_EVT:
//         ESP_LOGI(TAG, "ESP_SPP_CL_INIT_EVT");//when the SPP client is initialized,
//         break;
// case ESP_SPP_DATA_IND_EVT: //if event data print value received
//         printf("Received data:\t %.*s", param->data_ind.len, param->data_ind.data);
//     break;
//     case ESP_SPP_WRITE_EVT:
//         ESP_LOGI(TAG, "ESP_SPP_WRITE_EVT"); // when we write from esp32 to mobile phone
//         break;
//     default:
//         break;    
// }

// void test(void){
//     nvs_flash_init(); //it will save important details necesasry for run time program
//     esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT(); //bt config default
//     esp_bt_controller_init(&bt_cfg); //init this default configuration
//     esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT); //enabling classic bluetooth mode
//     esp_bluedroid_init(); //initialize bluedroid
//     esp_bluedroid_enable(); //enable bluedroid
//     esp_spp_register_callback(esp_spp_cb); //event handler registerd here
//     esp_spp_init(esp_spp_mode); // initialize the esp_spp_mode call back explained above
//     input_funtion_from_keyboard_you_will_write()// you will write this not me
// }