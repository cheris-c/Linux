#include <iostream>
#include <fstream>
#include "message.pb.h"
using namespace std;

void ListMsg(const Im::Content& msg)
{
    cout << msg.id() << endl;
    cout << msg.str() << endl;
}

int main() 
{
    Im::Content msg1;
    msg1.set_id(101);
    msg1.set_str("sharexu");
    
    ListMsg(msg1);

    fstream output("./log", ios::out | ios::trunc | ios::binary);

    if (!msg1.SerializeToOstream(&output)) 
    {
        cerr << "Failed to write msg." << endl;
        return -1;
    }

    return 0;
}
