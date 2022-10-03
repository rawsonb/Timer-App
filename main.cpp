#include <iostream>
#include <cmath>

using namespace std;

class Clock 
{
    int time;
    bool active = false;

    public:
    
    void set_data(int seconds);
    bool get_active();

};

bool Clock::get_active()
{
    return active;
}

void Clock::set_data(int seconds)
{
    time = seconds;
    active = true;
}

void show_main_menu(Clock clocks[], int maxClocks)
{
    double input;
    int activeClocks = 0;
    for(int i = 0; i < maxClocks; i++){
        if (clocks[i].get_active()){
            activeClocks++;
        }
    }
    cout << "Number of clocks: " << activeClocks << "" <<"\nUse \"l\" to list clocks.\nUse \"s <clock>\" to start a clock.\nUse \"e <clock>\" to edit a clock.\n>";
    cin >> input;
}

int main()
{
    Clock clocks [5];

    clocks[1].set_data(5);
    clocks[2].set_data(3);
    clocks[4].set_data(10);
    clocks[3].set_data(15);

    show_main_menu(clocks, sizeof(clocks)/sizeof(clocks[0]));
    cout << "exiting";
    return 0;
}