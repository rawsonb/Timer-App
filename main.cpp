#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

bool is_num(string string)
{
    for(int i = 0; i < string.length(); i++){
        if (!isdigit(string[i])){
            return false;
        }
    }
    return true;
}

string get_new_time(int current)
{
    string r;
    cout << "Please input the new clock time in seconds(currently: " << current << ")\n>";
    getline(cin, r);
    if (!is_num(r)){
        cout << "Clock time must be a number.\n";
        get_new_time(current);
    }
    return r;
}

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

class ClockData
{
    Clock clocks [5];
    int maxClocks = 5;

    public:

    void list_clocks();
    int get_active_clocks();
    void set_clock(int index, int seconds, string name);
    void run_clock(string clockName);
    int find_clock(string clockName);
    void edit_clock(string clockName);
};

void ClockData::edit_clock(string clockName){
    int clockIndex = find_clock(clockName);
    if (clockIndex == -1){
        cout << "Invalid name. Use \"l\" to list clocks.";
    } else{
    string newName;
        string newTime = get_new_time(clocks[clockIndex].get_time());
    cout << "Please input the new clock name(currently: " << clocks[clockIndex].get_name() << ")\n>";
    getline(cin, newName);
    clocks[clockIndex].set_data(stoi(newTime), newName);
    }
}

void ClockData::set_clock(int index, int seconds, string name)
{
    clocks[index].set_data(seconds,name);
}

void ClockData::list_clocks()
{
    cout << "\n\t Clocks\n------------------------\n";
    for(int i = 0; i < maxClocks; i++){
        if (clocks[i].get_active()){
            cout << "\t\"" << clocks[i].get_name() << "\"\nSeconds: " << clocks[i].get_time() << "\n\n";
        }
    }
    cout << "------------------------";
}


int ClockData::get_active_clocks()
{
    int activeClocks = 0;
    for(int i = 0; i < maxClocks; i++){
        if (clocks[i].get_active()){
            activeClocks++;
        }
    }
    return activeClocks;
}

void show_main_menu(ClockData clocks)
{
    cout << "\nNumber of clocks: " << clocks.get_active_clocks() << "" <<"\nUse \"l\" to list clocks.\nUse \"s <clock>\" to start a clock.\nUse \"e <clock>\" to edit a clock.";
}

int ClockData::find_clock(string clockName)
{
    for(int i = 0; i < maxClocks; i++){
        if (clocks[i].get_active()){
            if (clocks[i].get_name() == clockName){
                return i;
            }
        }
    }
    return -1;
}

void ClockData::run_clock(string clockName)
{
    int clockIndex = find_clock(clockName);
    if (clockIndex == -1){
        cout << "Invalid name. Use \"l\" to list clocks.";
    } else{
        cout << "|                      |\n";
        Clock clock = clocks[clockIndex];
        double sleepTime = clock.get_time() * 4;
        int lastBar = 0;
        string progressBar;
        float sleepPercent = 0.0;
        for(int i = 0; i < sleepTime; i++){
            sleepPercent = i/sleepTime;

            if(23 * sleepPercent-1 > lastBar) {progressBar = "|";
            for(int j = 23*sleepPercent; j > 0; j--){
                progressBar.insert(1,"#");
            }
            for(int j = 23 - progressBar.length(); j > 0; j--){
                progressBar.append(" ");
            }
            progressBar.append("|");

            cout << progressBar << "\n";
            lastBar = 23*sleepPercent;
            }

            this_thread::sleep_until(chrono::system_clock::now() + 0.25s);
        }
        cout << "\nTime is up!\n";
    }
}

void process_input(ClockData clocks)
{
    cout << "\n>";
    string input;
    getline(cin, input);
    if(input == "l"){
        clocks.list_clocks();
    } else if (input[0] == 's'){
        if (input[1] == ' '){
            clocks.run_clock(input.substr(2));
        } else{
            cout << "\nThis command requires a clock name.\n";
        }
    } else if (input == "c"){
        show_main_menu(clocks);
    } else if (input[0] == 'e'){
        if (input[1] == ' '){
            clocks.edit_clock(input.substr(2));
        } else{
            cout << "\nThis command requires a clock name.\n";
        }
    }
    cout << "\nUse \"c\" to see commands.";
    process_input(clocks);
}

string toComma(string inStr, int commas)
{
    string rdTxt = "";
    int index = 0;
    int pastCommas = 0;
    while(pastCommas < commas){
        while(inStr[index] != ',' && index < inStr.length()){
            index++;
        }
        pastCommas++;
        index++;
    }
    while(inStr[index] != ',' && index < inStr.length()){
        rdTxt.push_back(inStr[index]);
        index++;
    }
    return rdTxt;
}

int main()
{
    ClockData clocks;
    fstream clockFile("clocks.txt");

    string lnTxt;

    int i = 0;

    int clockTime;

    while(getline(clockFile, lnTxt) && i < 5)
    {
        
        clockTime = stoi(toComma(lnTxt,0));
        clocks.set_clock(i,clockTime,toComma(lnTxt,1));
        i++;
    }

    show_main_menu(clocks);
    process_input(clocks);
    cout << "\n";
    return 0;
}