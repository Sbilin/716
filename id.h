#include<iostream>
using namespace std;
#include<vector>
#include<map>
struct Status{
    string id;
    string sta;
};
struct Vm_infomation{
    string fault_name;
    string backup_name;
    string fault_id;
    string fault_status;
};
class Prase_id{
    private:
        // begin of status;
        unsigned short   _begin_status;      // the begin of status in the table
        //end of status;
        unsigned short   _end_status;
        vector<string>  *_table;
        // begin of name
        unsigned short   _begin_name;
        //end of name
        unsigned short   _end_name; 
        // key-value, key is the vm name so the name 
        // must be unique. Using name we can find vm id 
        // status and the back-up vm's name. It should be 
        // $name-backup.
        map<string,struct Status> _data;
        // the fault vm name       
        string _fault_name;
        //  the backup vm name 
        string _backup_name;
        string _fault_id;
        string _fault_status;

        void check_status(void );
        void initial_begin_status(void);
        void prase_table(void);
    public:
       
        Prase_id(vector<string> *table)
        {
            _table = table;
            initial_begin_status();
            prase_table();
            check_status();
        }
        struct Vm_infomation get_information()
        {
            struct Vm_infomation information;
            information.fault_id = _fault_id;
            information.backup_name = _backup_name;
            information.fault_name = _fault_name;
            information.fault_status = _fault_status;
            return information;
        }
        void restore_vm();
        void show()
        {
            map<string,struct Status>::iterator it;
            for(it=_data.begin(); it != _data.end() ;it++)
            {
                cout<<it->first<<" "<<it->second.id<<" "<<it->second.sta<<endl;
            }
        }
       
}; 
