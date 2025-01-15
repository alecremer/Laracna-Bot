// 
// Create by Ale on 12/8/24
// 

#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <string>
#include <vector>

using namespace std;

class data_manager
{
    public:
        string read_config(void);
        string read_file(const string& file_name);
        void write_config(const string& key, const string& data);
        string read_config_field(const string& key);
        static void write_file(const string& data, const string& file_name);
        bool delete_file(const string& file_name);
        vector<string> list_files(void);
        data_manager(void);

    private:
        void mount_partition(void);

};



#endif // DATA_MANAGER_HPP
