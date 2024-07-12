#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <nlohmann/json.hpp>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::cerr;
using nlohmann::json;
using std::ifstream;
using std::ofstream;

string firstLine = "Initializing Backend...";
string secondLine = "Backend started!";
string thirdLine = "Initializing Server...";
string gameVersion = "Renegade-MPT 1.0.0";

void SetColorConsole(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void LogVersionInfo(string firstLine, string secondLine, string thirdLine, string gameVersion)
{
    SetColorConsole(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Set the color to green
    cout << firstLine << endl;
    Sleep(3000);
    SetColorConsole(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Set the color to blue
    cout << secondLine << endl;
    Sleep(1000);
    SetColorConsole(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Set the color to green
    cout << thirdLine << endl;
    Sleep(3000);
    SetColorConsole(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Set the color to blue
    cout << "Server with " + gameVersion << " on 127.0.0.1" << endl;
    Sleep(1000);
    SetColorConsole(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Set the color to white
}

void LogError(string error)
{
    SetColorConsole(FOREGROUND_RED | FOREGROUND_INTENSITY); // Set the color to red
    cout << error << endl;
    SetColorConsole(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Set the color to white
}

bool checkJson()
{
    // Read the JSON file
    ifstream file("data.json");
    if (!file.is_open()) {
        cerr << "Could not open the file!" << std::endl;
        return false;
    }
    return true;
}

void updateJson(const string& name, int age, const string& city)
{
    // Read and parse the JSON data
    ifstream file("data.json");
    json jsonData;
    file >> jsonData;

    // Update the JSON data
    jsonData["name"] = name;
    jsonData["age"] = age;
    jsonData["city"] = city;

    // Write the updated JSON data back to the file
    ofstream outFile("data.json");
    outFile << jsonData.dump(4) << endl;
}

// Function to move the cursor up one line and clear the line
void ClearPreviousLine() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    // Get the current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

    // Move the cursor up one line
    csbi.dwCursorPosition.Y -= 1;
    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);

    // Clear the line by overwriting it with spaces
    DWORD charsWritten;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, csbi.dwCursorPosition, &charsWritten);
    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

int main()
{
    SetConsoleTitle(L"Renegade-MPT");
    if (!checkJson())
    {
        LogError("Error: Could not open data.json. Does the file exist?.");
        system("pause");
        return 1;
    }
    else
    {
        Sleep(1000);
        LogError("Success: data.json has been loaded successfully.");
        Sleep(1000);

        // Accept user data
        string name;
        int age;
        string city;

        cout << "Enter your name: ";
        getline(cin, name);
        ClearPreviousLine();
        cout << "Enter your age: ";
        cin >> age;
        ClearPreviousLine();
        cin.ignore(); // Ignore the newline character left in the input buffer
        cout << "Enter your city: ";
        getline(cin, city);
        ClearPreviousLine();

        // Update the JSON data with user input
        updateJson(name, age, city);

        // Print the updated JSON data
        /*
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "City: " << city << endl;
        */
        Sleep(3000);

        LogVersionInfo(firstLine, secondLine, thirdLine, gameVersion);
        cout << R"(=================================================================================)" << endl;
        cout << R"(______                                _        _____ _             _ _           )" << endl;
        cout << R"(| ___ \                              | |      /  ___| |           | (_)          )" << endl;
        cout << R"(| |_/ /___ _ __   ___  __ _  __ _  __| | ___  \ `--.| |_ _   _  __| |_  ___  ___ )" << endl;
        cout << R"(|    // _ \ '_ \ / _ \/ _` |/ _` |/ _` |/ _ \  `--. \ __| | | |/ _` | |/ _ \/ __|)" << endl;
        cout << R"(| |\ \  __/ | | |  __/ (_| | (_| | (_| |  __/ /\__/ / |_| |_| | (_| | | (_) \__ \)" << endl;
        cout << R"(\_| \_\___|_| |_|\___|\__, |\__,_|\__,_|\___| \____/ \__|\__,_|\__,_|_|\___/|___/)" << endl;
        cout << R"(                       __/ |                                                     )" << endl;
        cout << R"(                      |___/                                                      )" << endl;
        cout << R"(=================================================================================)" << endl;
        SetColorConsole(FOREGROUND_RED | FOREGROUND_INTENSITY); // Set the color to red
        system("pause");
        return 0;
    }
}