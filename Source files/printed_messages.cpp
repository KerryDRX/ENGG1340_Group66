#include <iostream>
#include <iomanip>
#include "printed_messages.h"
using namespace std;

// Function: print welcome message
void welcome() {
    cout<<"************************************************"<<endl;
    cout<<"*******Welcome to Our Accounting System!********"<<endl;
    cout<<"************************************************"<<endl;
}

// Function: print thank-you message
void thanks() {
    cout<<"************************************************"<<endl;
    cout<<"***Thank You for Using Our Accounting System!***"<<endl;
    cout<<"************************************************"<<endl;
}

// Function: print all the functionalities of this program
void show_choices() {
    cout<<"Please make a choice:"<<endl;
    cout<<"0. Quit"<<endl;
    cout<<"1. Budget Setting"<<endl;
    cout<<"2. Add Records of Income or Expenses"<<endl;
    cout<<"3. Delete Financial Records"<<endl;
    cout<<"4. Edit Financial Records"<<endl;
    cout<<"5. Show Financial Records"<<endl;
    cout<<"6. Write Financial Records to a File"<<endl;
    cout<<"7. Search for Financial Records"<<endl;
    cout<<"8. Check Financial State"<<endl;
    cout<<"9. Change the Type of Currency"<<endl;
}

// Function: ask user to decide whether to set up a monthly budget or not,
//           ask user for budget value if user choose "Yes",
//           leave it -1 if otherwise
// Input: double budget: initialized to be -1.
void set_up_budget_or_not(double & budget) {
    cout<<"Do you want to set up your budget for every month or not?"<<endl;
    cout<<"Please note that there will be an alert if your expenditure in any month exceeds the budget."<<endl;
    cout<<"1. Yes, I do."<<endl;
    cout<<"2. No, I don't."<<endl;
    char choice;
    cin>>choice;
    switch (choice) {
        case '1':
            cout<<"Please input your budget for every month."<<endl;
            cin>>budget;
            cout<<"Budget setting successful."<<endl;
            break;
        case '2':
            cout<<"You have chosen not to set a budget. You can set your budget afterward."<<endl;
            break;
        default:
            cout<<"Invalid choice. Budget setting failed. You can set your budget afterward."<<endl;
    }
}

// Function: print the choices of income and expenditure
void income_or_expenditure() {
    cout<<"1. Income"<<endl;
    cout<<"2. Expenditure"<<endl;
}

// Function: print types of income
void types_of_income() {
    cout<<"1. Interest"<<endl;
    cout<<"2. Investment"<<endl;
    cout<<"3. Wage"<<endl;
    cout<<"4. Lottery"<<endl;
    cout<<"5. Gift"<<endl;
    cout<<"6. Others"<<endl;
}

// Function: print types of expenditure
void types_of_expenditure() {
    cout<<"1. Clothing"<<endl;
    cout<<"2. Food"<<endl;
    cout<<"3. Houseware"<<endl;
    cout<<"4. Transportation"<<endl;
    cout<<"5. Entertainment"<<endl;
    cout<<"6. Education"<<endl;
    cout<<"7. Medicine"<<endl;
    cout<<"8. Insurance"<<endl;
    cout<<"9. Others"<<endl;
}

// Function: print types of account
void types_of_account() {
    cout<<"1. Octopus"<<endl;
    cout<<"2. Credit Card"<<endl;
    cout<<"3. Bank Card"<<endl;
    cout<<"4. WeChat Pay"<<endl;
    cout<<"5. Alipay"<<endl;
    cout<<"6. University Card"<<endl;
    cout<<"7. Cash"<<endl;
}

// Function: print the first line of the bill
void title() {
    cout<<setw(13)<<"Serial Number";
    cout<<setw(13)<<"Amount";
    cout<<setw(18)<<"Income/Expenses";
    cout<<setw(12)<<"Type";
    cout<<setw(17)<<"Account";
    cout<<setw(11)<<"Date"<<endl;
}
