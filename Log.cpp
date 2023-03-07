#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Log
{
private:
    string Name;

public:
    Log(string name);
    ~Log() = default;

    void Write(string msg);

    string getName()
    {
        return Name;
    }
};

Log::Log(string name)
{
    Name = name;
    try
    {
        ofstream file(name, ios::app);

        if (file.is_open())
        {
            time_t timer;
            time(&timer);
            file << "Current time: " << asctime(localtime(&timer));
            file.close();
        }
        else
            cout << "Problem with operning file" << endl;
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
};

void Log::Write(string msg)
{
    try
    {
        ofstream file(Name, ios::app);
        if (file.is_open())
        {

            file << msg << "\n";
            file.close();
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
};
