#include "id.h"
#include<unistd.h>
#include<stdlib.h>
//We prase the second line of the table, and caculate
//the number of _begin_name,_begin_status,_end_name,_end_status 
void Prase_id::initial_begin_status(void)
{
    for(unsigned short i =0; (*_table)[1][i] != 'm'; i++)
    {
        if(((*_table)[1][i]) == 'N')
        {
            _begin_name = i;
            while((*_table)[1][i] != '|')
            {
                i++;
            }                
            _end_name = i-1;
        }
        if (((*_table)[1][i]) == 'S' )
        {
            _begin_status = i;
            while((*_table)[1][++i] != '|')
            {
            }
            _end_status = i-1;
            break;
        }

    }
    return ;
}


// prase the table in the id.txt file and generate vm name 
// id  status to data.
void delete_space(string &str)
{
     unsigned short i = str.length() - 1;
     while(str[i] == ' ')
     {
         i--;
     }
     str = str.substr(0,i+1);
}
void Prase_id::prase_table()
{
    int number = (*_table).size();
    for (unsigned i = 3; i < number-1; ++i) { 
        struct Status tmp;
        string name;
        tmp.id = (*_table)[i].substr(2,37);
        name = (*_table)[i].substr(_begin_name ,_end_name - _begin_name );
        delete_space(name); 
        tmp.sta = (*_table)[i].substr(_begin_status ,_end_status - _begin_status );
        delete_space(tmp.sta );
        _data.insert(make_pair (name, tmp));
    }
    
}
void Prase_id::check_status ()
{
    map<string,struct Status>::iterator it;
    for(it = _data.begin(); it != _data.end(); it++)
    {
        if(it->second.sta != "ACTIVE")
        {
            _fault_status = it->second.sta ;
            _fault_id = it->second.id;
            _fault_name = it->first;
            _backup_name = _fault_name + "-backup";
            break;
        }
    }
}
void Prase_id::restore_vm()
{
    if ( _fault_name.length() == 0)
    {
        cout<<"everything is ok"<<endl;
    }
    else
    {
        map<string,struct Status>::iterator it = _data.find(_backup_name);
        if(it == _data.end())
        {
            cout<<"We Can't find the backup vm, it should be migrated"<<endl;
            // there should be migrate the vm to other compute nodes;
            //
            //
            //
            //
        }
        else
        {

            cout<<"the vm id is: ";
            cout<<_fault_id<<endl;
            cout<<"the fault name is: ";
            cout<<_fault_name<<endl;
            cout<<"the backup_name is ";
            cout<<_backup_name<<endl;
            cout<<"the state is: ";
            cout<<_fault_status<<endl; 
            if(it->second.sta == "ACTIVE" )
            {
                cout<<"the backup vm has been activated"<<endl;
            }
            else 
            {
                // there should be activate the backup vm
                string str;
                if(it->second.sta == "PAUSED")
                {
                   str = "nova unpause "+ _backup_name;
                   system(str.data());
                }
                else if(it->second.sta == "SUSPENDED")
                {
                    str = "nova resume "+_backup_name;
                    system(str.data());
                }
                
                
            
            }
        }
    }
} 

        









