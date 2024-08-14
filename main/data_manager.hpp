// 
// Create by Ale on 12/8/24
// 

#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <string>
using namespace std;

class data_manager
{
    public:
        string read_config(void);
        void write_config(const string& data);
        data_manager(void);

    private:
        void mount_partition(void);

};



#endif // DATA_MANAGER_HPP
