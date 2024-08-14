// 
// Create by Ale on 12/8/24
// 
#include <iostream>
#include <fstream>
#include <sstream>
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

string data_manager::read_config(void){

    ifstream file;
    string line;
    string data = "";
    
    file.open("/storage/config.txt");
    if(file.is_open()){
        
        while ( getline(file,line) )
        {
        // cout << line << '\n';
            data += line + '\n';
        }
        file.close();

    }
    else cout << "Unable to open file";
    return data;
}

void data_manager::write_config(const string& data){

     // create new config 
    string config_old = read_config();
    std::istringstream f(config_old);
    string line;
    string config_new;
    string paramReplace = data.substr(0, data.find("="));

    while ( getline(f, line) )
    {
        // if this line contain parameter to change...
        if(line.find(paramReplace) != std::string::npos)
            line = data;
        config_new += line  + '\n';
    }

    // replace in file
    ofstream fileout("/storage/config.txt");
    fileout << config_new;
    fileout.close();




}