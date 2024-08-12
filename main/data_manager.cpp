// 
// Create by Ale on 12/8/24
// 
#include <iostream>
#include <fstream>
#include "data_manager.hpp"

extern "C"{
#include "esp_spiffs.h"
#include "esp_log.h"

}

using namespace std;

static const char* TAG = "FileSystem";

data_manager::data_manager(void){
    mount_partition();
}

void data_manager::mount_partition(void){

    // config
    esp_vfs_spiffs_conf_t config = {
        .base_path = "/storage",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = false
    };

    // open partition
    esp_err_t result = esp_vfs_spiffs_register(&config);
    
    if(result != ESP_OK){
        ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(result));
        return;
    }

    // calculate space 
    size_t total = 0, used = 0;
    result = esp_spiffs_info(config.partition_label, &total, &used);
    if(result != ESP_OK){

        ESP_LOGE(TAG, "Failed to get partition info (%s)", esp_err_to_name(result));

    }
    else{
        ESP_LOGI(TAG, "Partition size: total: (%d) used: (%d)", total, used);
    }

}

void data_manager::read_config(void){

    ifstream file;
    string line;
    
    file.open("/storage/config.txt");
    if(file.is_open()){
        
        while ( getline(file,line) )
        {
        cout << line << '\n';
        }
        file.close();

    }
    else cout << "Unable to open file";

}