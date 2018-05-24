#include<iostream>
#include<fstream>
#include<vector>
#include"id.h"
using namespace std;
// read from id.txt and storage them 
void readTxt(vector<string> &data)
{
    ifstream file_read;
    file_read.open("id.txt",ios::in);
    string str;
    while(getline(file_read,str)){
    data.push_back(str+"\r\n");
    }
    return ;
}

int main()
{
    vector<string> data;
    readTxt(data);
    vector<string>::iterator it;

    Prase_id table(&data);
    struct Vm_infomation vm_info;
    vm_info = table.get_information();
//    table.show();
    table.restore_vm();
    return 0;
}
