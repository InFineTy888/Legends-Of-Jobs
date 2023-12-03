#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

/*
         _                               _        _____   __        _       _
        | |                             | |      /  __ \ / _|      | |     | |
        | |     ___  __ _  ___ _ __   __| |___   | |  | | |_       | | ___ | |__  ___
        | |    / _ \/ _` |/ _ \ '_ \ / _` / __|  | |  | |  _|  _   | |/ _ \| '_ \/ __|
        | |___|  __/ (_| |  __/ | | | (_| \__ \  | |__| | |   | |__| | (_) | |_) \__ \
        |______\___|\__, |\___|_| |_|\__,_|___/  \_____/|_|    \____/ \___/|_.__/|___/
                    __/  |
                    |___/
*/

json jsonLoad(const string& fileName) {
    try {
        ifstream jsonStream(fileName);

        if (!jsonStream) {
            json userJson;

            userJson["userInfo"] = {{"name", "guest"}, {"jobID", 0}};
            userJson["balance"] = {{"coins", 0}, {"diamonds", 0}};
            userJson["levelSys"] = {{"exp", 0}, {"level", 1}, {"needexp", 20}, {"totalexp", 0}};
            userJson["other"] = {{"multiplierCoins", 1}, {"multiplierEXP", 1}};

            ofstream jsonOut(fileName);
            jsonOut << setw(4) << userJson;

            return userJson;
        }
        
        json userJson = json::parse(jsonStream);
        return userJson;
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
}

json userData = jsonLoad("./database/user.json");
json jobsData = jsonLoad("./database/jobs.json");

vector<string> arguments = {};

int randomNumber(int min, int max);
void inputCommand(string& command, vector<string>& arguments);
string getCommandName(const string& input);
vector<string> getArguments(const string& input);
string convertToShortNumber(long number);

void Profile(const vector<string>& arguments);
void Work(const vector<string>& arguments);
void Jobs(const vector<string>& arguments);
void Buy(const vector<string>& arguments);
void SetName(const vector<string>& arguments);
void Help(const vector<string>& arguments);

int main() {
    srand(time(NULL));

    cout << "In order to save your progress, you need to enter the 'quit' command before exiting, otherwise your progress will be lost." << endl;
    cout << "Enter 'help', to show you all the commands that are in the game" << endl << endl;

    bool run = true;

    while(run) {
        string command;
        vector<string> arguments;

        inputCommand(command, arguments);

        string commandName = getCommandName(command);
        vector<string> commandArguments = getArguments(command);

        // - Level System -
        if(userData["levelSys"]["exp"].get<int>() >= userData["levelSys"]["needexp"].get<int>()) {
            userData["levelSys"]["exp"] = userData["levelSys"]["exp"].get<int>() - userData["levelSys"]["needexp"].get<int>();
            userData["levelSys"]["level"] = userData["levelSys"]["level"].get<int>() + 1;
            userData["levelSys"]["needexp"] = userData["levelSys"]["needexp"].get<int>() * 3;
            userData["other"]["multiplierCoins"] = userData["other"]["multiplierCoins"].get<int>() + 1;
            userData["other"]["multiplierEXP"] = userData["other"]["multiplierEXP"].get<int>() + 1;
        }
        // - User Input -
        if(commandName == "profile") {
            Profile(arguments);
        }
        else if(commandName == "work") {
            Work(arguments);
        }
        else if(commandName == "jobs") {
            Jobs(arguments);
        }
        else if(commandName == "buy") {
            Buy(arguments);
        }
        else if(commandName == "setname") {
            SetName(arguments);
        }
        else if(commandName == "help") {
            Help(arguments);
        }
        else if(commandName == "quit") {
            ofstream jsonOut("./database/user.json");
            jsonOut << setw(4) << userData;
            run = false;
        }
    }

    return 0;
}

void inputCommand(string& command, vector<string>& arguments) {
    string input;
    getline(cin, input);

    istringstream iss(input);
    iss >> command;
    string argument;
    while (iss >> argument) {
        arguments.push_back(argument);
    }
}

string getCommandName(const string& input) {
    istringstream iss(input);
    string command;
    iss >> command;
    return command;
}

vector<string> getArguments(const string& input) {
    istringstream iss(input);
    string command;
    iss >> command;
    vector<string> arguments;
    string argument;
    while (iss >> argument) {
        arguments.push_back(argument);
    }
    return arguments;
}

string convertToShortNumber(long number) {
    if (number < 1000) {
        return std::to_string(number);
    } else if (number < 1000000) {
        return std::to_string(number / 1000) + "K";
    } else if (number < 1000000000) {
        return std::to_string(number / 1000000) + "M";
    } else if (number < 1000000000000) {
        return std::to_string(number / 1000000000) + "B";
    } else if (number < 1000000000000000) {
        return std::to_string(number / 1000000000000) + "T";
    } else {
        return std::to_string(number / 1000000000000000) + "Q";
    }
}

int randomNumber(int min, int max) {
    int num = min + rand() % (max - min + 1);
    return num;
}

void Help(const vector<string>& arguments) {
    cout << endl << "All commands in the game:" << endl;
    cout << "profile - shows your stats" << endl;
    cout << "work - earn coins and exp" << endl;
    cout << "jobs int<page> - shows all jobs" << endl;
    cout << "buy int<jobID> - purchasing a vacancy" << endl;
    cout << "setname string<name> - give you a new name" << endl;
}

void Profile(const vector<string>& arguments) {
    if(arguments.empty()) {
        string jobName = jobsData[userData["userInfo"]["jobID"].get<string>()]["name"];
        int mJobCoins = jobsData[userData["userInfo"]["jobID"].get<string>()]["multiplierCoins"];
        int mJobExp = jobsData[userData["userInfo"]["jobID"].get<string>()]["multiplierEXP"];

        const int barWidth = 10;

        float progress = static_cast<float>(userData["levelSys"]["exp"].get<float>()) / userData["levelSys"]["needexp"].get<float>();
        int filledWidth = static_cast<int>(progress * barWidth);
        int remainingWidth = barWidth - filledWidth;

        string progressBar;

        for (int i = 0; i < filledWidth; ++i) {
            progressBar += "█";
        }
        for (int i = 0; i < remainingWidth; ++i) {
            progressBar += "▒";
        }

        cout << endl << "User Information:" << endl;
        cout << "├───╼ Name: " << userData["userInfo"]["name"].get<string>() << endl;
        cout << "└───╼ Job: " << jobName << " ( ID: " << userData["userInfo"]["jobID"].get<string>() << " )" << endl;
        cout << "Balance:" << endl;
        cout << "├───╼ Coins: " << convertToShortNumber(userData["balance"]["coins"].get<double>()) << " ( " << userData["balance"]["coins"].get<unsigned int>() << " )" << endl;
        cout << "└───╼ Diamonds: " << convertToShortNumber(userData["balance"]["diamonds"].get<unsigned int>()) << endl;
        cout << "Experience:"<< endl;
        cout << "├───╼ Level: " << userData["levelSys"]["level"].get<unsigned int>() << endl;
        cout << "├───╼ Total Exp: " << userData["levelSys"]["totalexp"].get<unsigned int>() << endl;
        cout << "└───╼ Progress: " << progressBar << " ( exp " << userData["levelSys"]["exp"].get<float>() << " / " << userData["levelSys"]["needexp"].get<float>() << " need exp )" << endl;
        cout << "Other:" << endl;
        cout << "├───╼ Multiplier Coins: " << userData["other"]["multiplierCoins"].get<unsigned int>() << " ( +" << mJobCoins << " for Job )" << endl;
        cout << "└───╼ multiplier Exp: " << userData["other"]["multiplierEXP"].get<unsigned int>() << " ( +" << mJobExp << " for Job )" << endl << endl;
    }
}

void Work(const vector<string>& arguments) {
    if(arguments.empty()) {
        int mJobCoins = jobsData[userData["userInfo"]["jobID"].get<string>()]["multiplierCoins"];
        int mJobExp = jobsData[userData["userInfo"]["jobID"].get<string>()]["multiplierEXP"];

        int coins = randomNumber(3, 9) * (userData["other"]["multiplierCoins"].get<unsigned int>() + mJobCoins);
        int exp = randomNumber(2, 6) * (userData["other"]["multiplierEXP"].get<int>() + mJobExp);

        userData["balance"]["coins"] = userData["balance"]["coins"].get<unsigned int>() + coins;
        userData["levelSys"]["totalexp"] = userData["levelSys"]["totalexp"].get<unsigned int>() + exp;
        userData["levelSys"]["exp"] = userData["levelSys"]["exp"].get<unsigned int>() + exp;

        cout << endl << "You have earned " << convertToShortNumber(coins) << " Coins, and " << convertToShortNumber(exp) << " Exp" << endl << endl;
    }
}

void Jobs(const vector<string>& arguments) {
    if (arguments.size() == 1) {
        int page = atoi(arguments[0].c_str());
        if (page <= 0) {
            cout << endl << "The page number must be a positive number" << endl << endl;
            return;
        }

        const int itemsPerPage = 10;
        int start = (page - 1) * itemsPerPage;
        int end = start + itemsPerPage;
        bool jobsFound = false;

        cout << endl << arguments[0] << " Page" << endl << endl;

        for (int id = start; id < end; id++) {
            if (jobsData.find(to_string(id)) != jobsData.end()) {
                jobsFound = true;
                cout << "Job: " << jobsData[to_string(id)]["name"].get<string>() << endl << "ID: " << id << ", Price: " << convertToShortNumber(jobsData[to_string(id)]["price"]) << " Coins" << endl << "MultiplierCoins: " << jobsData[to_string(id)]["multiplierCoins"] << ", MultiplierEXP: " << jobsData[to_string(id)]["multiplierEXP"] << endl << endl;
            } else 
                break;
        }
        if (!jobsFound)
            cout << endl << "There is nothing on this page" << endl << endl;
    } else 
        cout << endl << "To use the jobs command, you need to enter jobs <page>" << endl << endl;
}

void Buy(const vector<string>& arguments) {
    if (arguments.size() == 1) {;
        if (jobsData.find(arguments[0]) == jobsData.end()) {
            cout << endl << "There is no vacancy with such an ID." << endl << endl;
            return;
        }
        string jobName = jobsData[arguments[0]]["name"];
        cout << endl << "Do you want to purchase a job " << jobName << " ?" << endl;
        cout << "Enter [Y/n]: ";

        char answer;
        cin >> answer;

        if (answer == 'Y' || answer == 'y' ) {
            if (userData["balance"]["coins"] >= jobsData[arguments[0]]["price"]) {
                stringstream sid;
                sid << arguments[0];

                userData["balance"]["coins"] =  userData["balance"]["coins"].get<unsigned int>() - jobsData[arguments[0]]["price"].get<unsigned int>();
                cout << "You have successfully purchased a job " << jobName << "!" << endl << endl;
                userData["userInfo"]["jobID"] = arguments[0];
            } else {
                cout << endl << "You don't have enough coins to buy this job" << endl << endl;
            }
        } else if (answer == 'N' || answer == 'n') {
            cout << endl << "You refused to purchase a job" << endl << endl;
        } else {
            cout << endl << "Incorrect input" << endl << endl;
        }
    }
}

void SetName(const vector<string>& arguments) {
    if (arguments.size() == 1) {
        if(arguments[0].length() > 20) {
            cout << endl << "Your name must not contain more than 20 characters!" << endl << endl;
            return;
        }
        userData["userInfo"]["name"] = arguments[0];
        cout << endl << "Your new name: " << arguments[0] << "!" << endl << endl;
    }
}
