#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

string getSymbol(int num) {
    switch (num) {
        case 0: return "A";
        case 1: return "B";
        case 2: return "C";
        case 3: return "D";
        default: return "?";
    }
}

int main() {
    srand(time(0));
    char playAgain;

    do {
        int slot1 = rand() % 4;
        int slot2 = rand() % 4;
        int slot3 = rand() % 4;

        cout << "\n== Slot Machine ==\n";
        cout << "-------------------\n";
        cout << "| " << getSymbol(slot1) << " | " << getSymbol(slot2) << " | " << getSymbol(slot3) << " |\n";
        cout << "-------------------\n";

        if (slot1 == slot2 && slot2 == slot3) {
            cout << "!!! JACKPOT! You win!\n";
        } else {
            cout << "Sorry, try again.\n";
        }

        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}

