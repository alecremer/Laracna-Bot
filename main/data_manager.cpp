// 
// Create by Ale on 12/8/24
// 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "data_manager.hpp"

extern "C"{

#include <dirent.h>  
#include "esp_spiffs.h"
#include "esp_log.h"
#include <sys/stat.h>

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
        .format_if_mount_failed = true
    };

    // open partition
    esp_err_t result = esp_vfs_spiffs_register(&config);
    
    if(result != ESP_OK && result != ESP_ERR_INVALID_STATE){
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
        ESP_LOGI(TAG, "Storage mounted!! Partition size: total: (%d) used: (%d)", total, used);
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
            data += line + '\n';
        }
        file.close();

    }
    else cout << "Unable to open file";
    return data;
}

string data_manager::read_file(const string& file_name){

    ifstream file;
    string line;
    string data = "";
    
    string path = "/storage/" + file_name;
    file.open(path);
    if(file.is_open()){
        
        while ( getline(file,line) )
        {
            data += line + '\n';
        }
        file.close();

    }
    else cout << "Unable to open file";
    return data;
}

void data_manager::write_config(const string& key, const string& data){

     // create new config 
    string config_old = read_config();
    std::istringstream f(config_old);
    string line;
    string config_new;

    while ( getline(f, line) )
    {
        if(line.find(key) != std::string::npos){

            line = key + "=" + data;
        }
        config_new += line  + '\n';
    }

    // replace in file
    ofstream fileout("/storage/config.txt");
    fileout << config_new;
    fileout.close();

}

string data_manager::read_config_field(const string& key){

    string config_old = read_config();
    std::istringstream f(config_old);
    string line;
    string value;

    while ( getline(f, line) )
    {
        if(line.find(key) != std::string::npos){
    
            value = line.replace(0, key.length()+ 1, "");
            string log = "key: " + key +  ", value: " + value;
            write_file(log, "log_1.txt");

        }
    }
    
    return value;


}

void data_manager::write_file(const string& data, const string& file_name){

    ofstream fileout("/storage/" + file_name, std::ios::app);
    fileout << data + "\n";
    fileout.close();

}

vector<string> data_manager::list_files(void) {

    string base_path = "/storage";
    DIR* dir = opendir(base_path.c_str());  
    if (!dir) {
        std::cerr << "Error opening folder: " << base_path << "\n";
    }


    vector<string> files;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {

        files.push_back(entry->d_name);

        // std::string full_path = base_path + "/" + entry->d_name;

        // struct stat st;
        // if (stat(full_path.c_str(), &st) == 0) {
        //     if (S_ISREG(st.st_mode)) {
        //         std::cout << "  [ARQUIVO] " << entry->d_name << "\n";
        //     } else if (S_ISDIR(st.st_mode)) {
        //         std::cout << "  [DIRETÓRIO] " << entry->d_name << "\n";
        //     }
        // }
    }

    closedir(dir);  // Fecha o diretório
    return files;
}

bool data_manager::delete_file(const string& file_name) {
    
    string file_path = "/storage/" + file_name;
    
    if (unlink(file_path.c_str()) == 0) {
        return true;
    } else {
        return false;
    }
}