#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <cctype>
#include <vector>
#include<algorithm>
#include <map>

// print menu to user
void PrintMenu() {
    cout << "\nPlease make a selection 1-4 " << endl;
    cout << "1. Search for item" << endl;
    cout << "2. Show item frequency" << endl;
    cout << "3. Histogram" << endl;
    cout << "4. Exit Program" << endl;
}

// capitalize first letter of word
string capitalizeFirstOnly(string word) {
    word[0] = toupper(word[0]);
    for (unsigned int i = 1; i < word.size(); i++) {
        word[i] = tolower(word[i]);
    }
    cout << word << ": ";
    return word;
}

// main function
int main() {
    ifstream inFS; // input file stream
    ofstream oFS("frequency.dat"); // output file stream
    int input, count;
    string searchItem, currItem, line, item;
    vector<string> inputVector;
    map<string, int> freqMap;

    //add data to output file

    // check if input file is open
    inFS.open("input.txt");
    // check if file opened successfully
    if (!inFS.is_open()) {
        cout << "Could not open file Input.txt" << endl;
        return 1;
    }
    // reset item count to 0 before checking next item
    while (inFS >> item) {
        freqMap[item] = 0;
    }
    inFS.clear(); // clear any error flags from previous reads
    inFS.seekg(0); // reset file pointer to beginning of file

    while (inFS >> item) {
        freqMap[item]++;
    }

    // output frequency information
    for (const auto& pair: freqMap) {
        oFS << pair.first << " " << pair.second << endl;
    }

    oFS.close();
    inFS.close();

    cout << "\nCorner Grocer\nDaily Produce Purchases\n" << endl;

    // loop until user inputs 4 to quit
    while(true) {
        //print menu to user
        PrintMenu();
        // get user selection
        cin >> input;

        // check if the input is valid
        while (input < 1 || input > 4) {
            cout << "Invalid input. Enter option 1-4." << endl;
            cin >> input;
        }
        // option 1
        if (input == 1) {
            inFS.open("input.txt");
            // check if file opened successfully
            if (!inFS.is_open()) {
                cout << "Could not open file Input.txt" << endl;
                return 1;
            }
            count = 0;
            cout << "What would you like to search for?" << endl;
            cin >> searchItem;
            searchItem = capitalizeFirstOnly(searchItem);
            while (!inFS.eof()) {
                inFS >> currItem;
                if (currItem == searchItem) {
                    count++;
                }
            }
            cout << count << endl;
            inFS.close();
        }
            //option 2
        else if (input == 2) {
            inFS.open("input.txt");
            // check if file opened successfully
            if (!inFS.is_open()) {
                cout << "Could not open file Input.txt" << endl;
                return 1;
            }
            // reset item count to 0 before checking next item
            while (inFS >> item) {
                freqMap[item] = 0;
            }
            inFS.clear(); // clear any error flags from previous reads
            inFS.seekg(0); // reset file pointer to beginning of file

            // count number of item occurrences
            while (inFS >> item) {
                freqMap[item]++;
            }

            // output frequency information
            for (const auto& pair: freqMap) {
                cout << pair.first << " " << pair.second << endl;
            }
            inFS.close();
        }
            //option 3
        else if (input == 3) {
            inFS.open("input.txt");
            // check if file opened successfully
            if (!inFS.is_open()) {
                cout << "Could not open file Input.txt" << endl;
                return 1;
            }

            // clear frequency map
            freqMap.clear();

            // count number of item occurrences
            while (inFS >> item) {
                freqMap[item]++;
            }
            // output number of '*' for each item occurrence
            for (const auto& pair: freqMap) {
                cout << pair.first << " ";
                for (int i = 0; i < pair.second; ++i ) {
                    cout << "*";
                }
                cout << std::endl;
            }
            inFS.close();
        }
        // option 4
        else {
            cout << "\nGoodbye" << endl;
            break;
        }
    }

    oFS.close();

    return 0;
}
