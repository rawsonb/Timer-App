#include <iostream>
#include <cmath>

using namespace std;

class Clock 
{
    int time;
    bool active = false;
    string name;

    public:
    
    void set_data(int seconds, string clockName);
    bool get_active();
    string get_name();
    int get_time();

};

bool Clock::get_active()
{
    return active;
}

string Clock::get_name()
{
    return name;
}

int Clock::get_time()
{
    return time;
}

void Clock::set_data(int seconds, string clockName)
{
    time = seconds;
    active = true;
    name = clockName;
}


void list_clocks(Clock clocks[], int maxClocks)
{
    cout << "\n\t Clocks\n------------------------\n";
    for(int i = 0; i < maxClocks; i++){
        if (clocks[i].get_active()){
            cout << "\t\"" << clocks[i].get_name() << "\"\nSeconds: " << clocks[i].get_time() << "\n\n";
        }
    }
    cout << "------------------------";
}


int get_active_clocks(Clock clocks[], int maxClocks)
{
    int activeClocks = 0;
    for(int i = 0; i < maxClocks; i++){
        if (clocks[i].get_active()){
            activeClocks++;
        }
    }
    return activeClocks;
}

void show_main_menu(Clock clocks[], int maxClocks)
{
    cout << "Number of clocks: " << get_active_clocks(clocks, maxClocks) << "" <<"\nUse \"l\" to list clocks.\nUse \"s <clock>\" to start a clock.\nUse \"e <clock>\" to edit a clock.";
}

void process_input(Clock clocks[], int maxClocks)
{
    cout << "\n>";
    string input;
    getline(cin, input);
    if(input == "l"){
        list_clocks(clocks, maxClocks);
    }
}

int main()
{
    Clock clocks [5];

    clocks[1].set_data(5, "clocky");
    clocks[2].set_data(3, "clocker");
    clocks[4].set_data(10, "clocks");
    clocks[3].set_data(15, "clook");

    show_main_menu(clocks, sizeof(clocks)/sizeof(clocks[0]));
    process_input(clocks, sizeof(clocks)/sizeof(clocks[0]));
    cout << "\n";
    return 0;
}