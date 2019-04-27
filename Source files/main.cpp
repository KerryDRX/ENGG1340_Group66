#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "printed_messages.h"
#include "functionalities.h"
using namespace std;

// the main function
int main() {
    // print welcome message
    welcome();
    Node * head = NULL;
    double budget=-1;
    // ask the user to decide whether to set up a monthly budget or not at the beginning of the program
    // the budget will remain -1 if it's not set by the user
    set_up_budget_or_not(budget);
    // users must add record(s) for future ooperations at first
    char command = '2';
    // always ask the user for a command until the user wants to quit the program
    while (command!='0') {
        read_command(command, head, budget);
        // show all the functionalities of this program
        show_choices();
        cin>>command;
    }
    // print thank-you message
    thanks();
    delete head;
    return 0;
}
