#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "functionalities.h"
#include "printed_messages.h"
using namespace std;


// Function: update the serial number of the linked list,
//           1 for the first node, 2 for the second and so on
// Input: Node * head: the pointer pointing to the fist node of the linked list
void update_no(Node * head) {
    Node * current = head;
    int i=1;
    while (current!=NULL) {
      current->info.no=i++;
      current=current->next;
    }
    current=NULL;
    delete current;
}

// Function: insert a node to the linked list according to the order of date
// Input: Node * head: the pointer pointing to the fist node of the linked list
//        Node * p: the pointer pointing to the node to be inserted
//        int date: the date of the node to be inserted
void insert(Node * & head, Node * & p, int date) {
    p->next=NULL;
    Node * current = head;
    if (head==NULL)
        head=p;
    else {
        if (head->info.date>date) {
            p->next=current;
            head=p;
        }
        else {
            while (current->next!=NULL && current->next->info.date<=date)
                current=current->next;
            p->next=current->next;
            current->next=p;
        }
    }
    current=NULL;
    p=NULL;
    delete current;
    // update the sequence number of the linked list after the node is inserted
    update_no(head);
}

// Function: print a warning message if the expenditure in one month has exceeded the budget
// Input: Node * head: the pointer pointing to the fist node of the linked list
//        double budget: the budget set by the user
void budget_warning(Node * head, double budget) {
    Node * current = head;
    double monthly_expenditure=0;
    int i=0, date, new_date;
    while (current!=NULL) {
        if (current->info.income_or_expeneses=='2') {
            if (i==0)
                // it is the earliest day that has the expenditure
                date=current->info.date;
            new_date=current->info.date;
            if (new_date/100>date/100) {
                if (monthly_expenditure>budget) {
                    cout<<"Your monthly expenditure in "<<date/10000<<"-";
                    cout<<setfill('0')<<setw(2)<<date/100-100*(date/10000)<<" exceeds the budget by ";
                    cout.setf(ios::fixed,ios::floatfield);
                  	cout.precision(2);
                    cout<<monthly_expenditure-budget<<endl;
                    cout<<setfill(' ');
                }
                monthly_expenditure=0;
            }
            monthly_expenditure+=current->info.amount;
            date=new_date;
            i++;
        }
        current=current->next;
    }
    if (monthly_expenditure>budget) {
        cout<<"Your monthly expenditure in "<<date/10000<<"-";
        cout<<setfill('0')<<setw(2)<<date/100-100*(date/10000)<<" exceeds the budget by ";
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(2);
        cout<<monthly_expenditure-budget<<"."<<endl;
        cout<<setfill(' ');
    }
    current=NULL;
    delete current;
}

// Function: change the value of budget
// Input: double budget: -1 or another value if the user has set it
void change_budget(Node * head, double & budget) {
    cout<<"Please input your budget for every month."<<endl;
    cin>>budget;
    budget_warning(head, budget);
}
// Function: ask user for information of a new record and add it to the linked list
// Input: Node * head: the pointer pointing to the fist node of the linked list
//        double budget: the budget set by the user (-1 if it's not set)
void c_add(Node * & head, double budget) {
    // create a new node (pointed by p) that records all the information input by the user
    Node * p = new Node;

    double amount;
    cout<<"Please enter the amount of money you want to record."<<endl;
    cin>>amount;
    p->info.amount=amount;

    char income_or_expeneses;
    cout<<"Please indicate whether it is income or expenditure."<<endl;
    // print the choices of income and expenditure
    income_or_expenditure();
    cin>>income_or_expeneses;
    p->info.income_or_expeneses=income_or_expeneses;

    char type;
    if (income_or_expeneses=='1') {
        cout<<"Please choose the type of your income."<<endl;
        // print types of income
        types_of_income();
    }
    if (income_or_expeneses=='2') {
        cout<<"Please choose the type of your expenditure."<<endl;
        // print types of expenditure
        types_of_expenditure();
    }
    cin>>type;
    p->info.type=type;

    char account;
    cout<<"Please choose the type of your account."<<endl;
    // print types of account
    types_of_account();
    cin>>account;
    p->info.account=account;

    int date;
    cout<<"Please enter the date in the format of \"yyyymmdd\"."<<endl;
    cin>>date;
    p->info.date=date;
    // insert this node to the linked list at the right position
    insert(head, p, date);
    delete p;
    // budget is already set if it's value is not -1
    // check if the monthly budget has been exceeded in this case
    if (budget!=-1)
        budget_warning(head,budget);
}

// Function: ask user for information of new records from an existing file and add them to the linked list
// Input: Node * head: the pointer pointing to the fist node of the linked list
//        double budget: the budget set by the user (-1 if it's not set)
void f_add(Node * & head, double budget) {
    // ask user for the file name first
    string filename;
    cout<<"Please enter your file name."<<endl;
    cout<<"Please note that each line of the file should follow the following format."<<endl;
    cout<<"(e.g. A line \"5000 2 6 7 20190101\" which represents each financial record instead of \"5000 Expenditure Education Cash 20190101\" is valid)"<<endl;
    cin>>filename;
    // open the file
    ifstream fin(filename.c_str());
    if (fin.fail()) {
        cout<<"Error in file opening!"<<endl;
    }
 	  double amount;
    char income_or_expeneses, type, account;
    int date;
    while (fin>>amount>>income_or_expeneses>>type>>account>>date) {
        // create a new node (pointed by p) that records all the information input by the user
        Node * p = new Node;
        p->info.amount=amount;
        p->info.income_or_expeneses=income_or_expeneses;
        p->info.type=type;
        p->info.account=account;
        p->info.date=date;
        // insert this node to the linked list at the right position
        insert(head, p, date);
        delete p;
    }
    // close the file
    fin.close();
    // budget is already set if it's value is not -1
    // check if the monthly budget has been exceeded in this case
    if (budget!=-1)
        budget_warning(head, budget);
}

// Function: ask user whether to add record(s) by direct input or by an existing file
//           and then add record(s) according to the user's choice
// Input: Node * head: the pointer pointing to the fist node of the linked list
//        double budget: the budget set by the user (-1 if it's not set)
void add(Node * & head, double budget) {
    char choice;
    cout<<"Do you want to enter your financial record manually or input it from an existing file?"<<endl;
    cout<<"1. I want to enter my financial record manually."<<endl;
    cout<<"2. I want to input my financial record from my file."<<endl;
    cin>>choice;
    switch (choice) {
        case '1':
            // direct input
            c_add(head, budget);
            break;
        case '2':
            // input from file
            f_add(head, budget);
            break;
        default:
            cout<<"Invalid choice."<<endl;
    }
}

// Function: print one certain record including all it's information
// Input: Node * current: the pointer pointing to the node to be printed
//        double total: the net income of all the records to be printed
void print_one_record(Node * current, double & total) {
    cout<<setw(13)<<current->info.no;
    cout.setf(ios::fixed,ios::floatfield);
	  cout.precision(2);
	  cout<<setw(15)<<current->info.amount;
	  switch (current->info.income_or_expeneses) {
        case '1':
            total+=current->info.amount;
            cout<<setw(16)<<"Income";
            switch (current->info.type) {
                case '1':
                    cout<<setw(15)<<"Interest";
                    break;
                case '2':
                    cout<<setw(15)<<"Investment";
                    break;
                case '3':
                    cout<<setw(15)<<"Wage";
                    break;
                case '4':
                    cout<<setw(15)<<"Lottery";
                    break;
                case '5':
                    cout<<setw(15)<<"Gift";
                    break;
                case '6':
                    cout<<setw(15)<<"Others";
            }
            break;
        case '2':
            total-=current->info.amount;
            cout<<setw(16)<<"Expeneses";
            switch (current->info.type) {
                case '1':
                    cout<<setw(15)<<"Clothing";
                    break;
                case '2':
                    cout<<setw(15)<<"Food";
                    break;
                case '3':
                    cout<<setw(15)<<"Houseware";
                    break;
                case '4':
                    cout<<setw(15)<<"Transportation";
                    break;
                case '5':
                    cout<<setw(15)<<"Entertainment";
                    break;
                case '6':
                    cout<<setw(15)<<"Education";
                    break;
                case '7':
                    cout<<setw(15)<<"Medicine";
                    break;
                case '8':
                    cout<<setw(15)<<"Insurance";
                    break;
                case '9':
                    cout<<setw(15)<<"Others";
            }
  	}
	  switch (current->info.account) {
	      case '1':
            cout<<setw(17)<<"Octopus";
            break;
        case '2':
            cout<<setw(17)<<"Credit Card";
            break;
        case '3':
            cout<<setw(17)<<"Bank Card";
            break;
        case '4':
            cout<<setw(17)<<"WeChat Pay";
            break;
        case '5':
            cout<<setw(17)<<"Alipay";
            break;
        case '6':
            cout<<setw(17)<<"University Card";
            break;
        case '7':
            cout<<setw(17)<<"Others";
	  }
	  cout<<setw(10)<<current->info.date<<endl;
}

// Function: print information of all the financial records
// Input: Node * head: the pointer pointing to the fist node of the linked list
void show(Node * head) {
    Node * current = head;
    double total=0;
    title();
	  while (current!=NULL) {
        // for each node in the linked list, print it's information
        // total+=income, total-=expenditure for each record
		    print_one_record(current,total);
		    current=current->next;
	  }
    // total equals to the net income
	  cout<<"Your total net income is "<<total<<"."<<endl;
    current=NULL;
	  delete current;
}

// Function: edit the information of one record
// Input: Node * head: the pointer pointing to the fist node of the linked list
//        double budget: the budget set by the user (-1 if it's not set)
void edit(Node * & head, double budget) {
    show(head);
    // ask user for the sequence number of the node to be edited first
    int number;
    cout<<"Please enter the serial number of the record you want to edit."<<endl;
    cin>>number;
    Node * current = head;
    while (current->info.no!=number)
        current=current->next;
    // ask user what to edit
    char edit_choice;
    cout<<"Please choose what you want to edit."<<endl;
    cout<<"1. Amount"<<endl;
    cout<<"2. Type of Income or Expeneses"<<endl;
    cout<<"3. Account"<<endl;
    cout<<"4. Date"<<endl;
    cin>>edit_choice;
    switch (edit_choice) {
        case '1':
            double amount;
            cout<<"Please enter the amount of money."<<endl;
            cin>>amount;
            current->info.amount=amount;
            current=NULL;
            break;
        case '2':
            char income_or_expeneses;
            cout<<"Please indicate whether it is income or expenditure."<<endl;
            income_or_expenditure();
            cin>>income_or_expeneses;
            current->info.income_or_expeneses=income_or_expeneses;
            switch (income_or_expeneses) {
                case '1':
                    char type_of_income;
                    cout<<"Please choose the type of your income."<<endl;
                    types_of_income();
                    cin>>type_of_income;
                    current->info.type=type_of_income;
                    break;
                case '2':
                    char type_of_expenditure;
                    cout<<"Please choose the type of your expenditure."<<endl;
                    types_of_expenditure();
                    cin>>type_of_expenditure;
                    current->info.type=type_of_expenditure;
            }
            current=NULL;
            break;
        case '3':
            char account;
            cout<<"Please choose the type of your account."<<endl;
            types_of_account();
            cin>>account;
            current->info.account=account;
            current=NULL;
            break;
        case '4':
            int date;
            cout<<"Please enter the date in the format of \"yyyymmdd\"."<<endl;
            cin>>date;
            current->info.date=date;
            // if date is edited, the order of the linked list may be changed
            // delete the edited node first
            if (head==current)
                head=current->next;
            else {
                Node * after = head;
                while (after->next!=current)
                    after=after->next;
                // "after" points to the node before the node to be deleted
                after->next=current->next;
                after=NULL;
                delete after;
            }
            // then, insert this node to the linked list at the right position
            insert(head, current, date);
    }
    delete current;
    cout<<"The edition is done."<<endl;
    // budget is already set if it's value is not -1
    // check if the monthly budget has been exceeded in this case
    if (budget!=-1)
        budget_warning(head, budget);
}

// Function: delete one record
// Input: Node * head: the pointer pointing to the fist node of the linked list
void del(Node * & head) {
    show(head);
    // ask user for the sequence number of the node to delete
    int number;
    cout<<"Please enter the serial number of the record you want to delete."<<endl;
    cin>>number;
    Node * current = head;
    while (current->info.no!=number)
        current=current->next;
    if (head==current)
        head=head->next;
    else {
        Node * after = head;
        while (after->next!=current)
            after=after->next;
        // "after" points to the node before the node to be deleted
        after->next=current->next;
        after=NULL;
        delete after;
    }
    delete current;
    update_no(head);
    cout<<"The deletion is done."<<endl;
}

// Function: write all the financial records to an external file
// Input: Node * head: the pointer pointing to the fist node of the linked list
void f_out(Node * head) {
    string filename;
    cout<<"Please enter the file name."<<endl;
    cin >> filename;
    ofstream fout;
    fout.open(filename.c_str());
    if (fout.fail())
      cout<<"Error in file opening!"<<endl;
    else{
      Node * current = head;
      double total=0;
      fout<<setw(13)<<"Serial Number";
      fout<<setw(13)<<"Amount";
      fout<<setw(18)<<"Income/Expenses";
      fout<<setw(12)<<"Type";
      fout<<setw(17)<<"Account";
      fout<<setw(11)<<"Date"<<endl;
      while (current!=NULL) {
          fout<<setw(13)<<current->info.no;
          fout.setf(ios::fixed,ios::floatfield);
          fout.precision(2);
          fout<<setw(15)<<current->info.amount;
          switch (current->info.income_or_expeneses) {
              case '1':
                  total+=current->info.amount;
                  fout<<setw(16)<<"Income";
                  switch (current->info.type) {
                      case '1':
                          fout<<setw(15)<<"Interest";
                          break;
                      case '2':
                          fout<<setw(15)<<"Investment";
                          break;
                      case '3':
                          fout<<setw(15)<<"Wage";
                          break;
                      case '4':
                          fout<<setw(15)<<"Lottery";
                          break;
                      case '5':
                          fout<<setw(15)<<"Gift";
                          break;
                      case '6':
                          fout<<setw(15)<<"Others";
                  }
                  break;
              case '2':
                  total-=current->info.amount;
                  fout<<setw(16)<<"Expeneses";
                  switch (current->info.type) {
                      case '1':
                          fout<<setw(15)<<"Clothing";
                          break;
                      case '2':
                          fout<<setw(15)<<"Food";
                          break;
                      case '3':
                          fout<<setw(15)<<"Houseware";
                          break;
                      case '4':
                          fout<<setw(15)<<"Transportation";
                          break;
                      case '5':
                          fout<<setw(15)<<"Entertainment";
                          break;
                      case '6':
                          fout<<setw(15)<<"Education";
                          break;
                      case '7':
                          fout<<setw(15)<<"Medicine";
                          break;
                      case '8':
                          fout<<setw(15)<<"Insurance";
                          break;
                      case '9':
                          fout<<setw(15)<<"Others";
                  }
          }
          switch (current->info.account) {
              case '1':
                  fout<<setw(17)<<"Octopus";
                  break;
              case '2':
                  fout<<setw(17)<<"Credit Card";
                  break;
              case '3':
                  fout<<setw(17)<<"Bank Card";
                  break;
              case '4':
                  fout<<setw(17)<<"WeChat Pay";
                  break;
              case '5':
                  fout<<setw(17)<<"Alipay";
                  break;
              case '6':
                  fout<<setw(17)<<"University Card";
                  break;
              case '7':
                  fout<<setw(17)<<"Others";
          }
          fout<<setw(10)<<current->info.date<<endl;
          current=current->next;
      }
      fout.close();
      current=NULL;
      delete current;
      cout<<"All your financial records have been written to "<<filename<<"."<<endl;
    }
}

// Function: search for records that fit in the conditions given by the user and print them
// Input: Node * head: the pointer pointing to the fist node of the linked list
void search(Node * head) {
    // ask user for the criteria for searching
    double min_amount=0, max_amount=0;
    char income_or_expeneses, type, account;
    int earliest_date=0, latest_date=0;

    bool search_by_amount;
    cout<<"Search by amount?"<<endl;
    cout<<"0. No."<<endl;
    cout<<"1. Yes."<<endl;
    cin>>search_by_amount;
    if (search_by_amount) {
        cout<<"Please enter the minimun and maximun amount."<<endl;
        cin>>min_amount>>max_amount;
    }

    cout<<"Please indicate whether it is income or expenditure."<<endl;
    cout<<"0. Any of the Following"<<endl;
    // print the choices of income and expenditure
    income_or_expenditure();
    cin>>income_or_expeneses;
    if (income_or_expeneses=='1') {
        cout<<"Please choose the type of your income."<<endl;
        cout<<"0. Any of the Following"<<endl;
        // print the types of income
        types_of_income();
        cin>>type;
    }
    if (income_or_expeneses=='2') {
        cout<<"Please choose the type of your expenditure."<<endl;
        cout<<"0. Any of the Following"<<endl;
        // print the types of expenditure
        types_of_expenditure();
        cin>>type;
    }

    cout<<"Please choose the type of your account."<<endl;
    cout<<"0. Any of the Following"<<endl;
    // print the types of account
    types_of_account();
    cin>>account;

    bool search_by_time;
    cout<<"Search by time?"<<endl;
    cout<<"0. No."<<endl;
    cout<<"1. Yes."<<endl;
    cin>>search_by_time;
    if (search_by_time) {
        cout<<"Please enter the earliest date and latest date."<<endl;
        cin>>earliest_date>>latest_date;
    }
    title();

    // go through each node of the list, and print the ones that fit in the criteria
    Node * current = head;
    double total=0;
    while (current!=NULL) {
        if (search_by_amount&&(current->info.amount<min_amount||current->info.amount>max_amount)) {
            current=current->next;
            continue;
        }
        if (income_or_expeneses=='1') {
            if (current->info.income_or_expeneses=='2') {
                current=current->next;
                continue;
            }
            else if (type!='0'&&current->info.type!=type) {
                current=current->next;
                continue;
            }
        }
        if (income_or_expeneses=='2') {
            if (current->info.income_or_expeneses=='1') {
                current=current->next;
                continue;
            }
            else if (type!='0'&&current->info.type!=type) {
                current=current->next;
                continue;
            }
        }
        if (account!='0'&&current->info.account!=account) {
            current=current->next;
            continue;
        }
        if (search_by_time&&(current->info.date<earliest_date||current->info.date>latest_date)) {
            current=current->next;
            continue;
        }
        // print the node and calculate the net income at the same time using "total"
        print_one_record(current,total);
        current=current->next;
    }
    cout<<"The total net income of the chosen records is "<<total<<"."<<endl;
    current=NULL;
	  delete current;
}

// Function: check the monthly/yearly income/expenses and the proportion of expenditure
// Input: Node * head: the pointer pointing to the fist node of the linked list
void check(Node * head) {
    // ask user for a choice first
    char choice;
    cout<<"What do you want to check?"<<endl;
    cout<<"1. Monthly Income"<<endl;
    cout<<"2. Yearly Income"<<endl;
    cout<<"3. Monthly Expenditure"<<endl;
    cout<<"4. Yearly Expenditure"<<endl;
    cout<<"5. Expenditure Proportion"<<endl;
    cin>>choice;
    int date, new_date, i;
    double monthly_income, yearly_income, monthly_expenditure, yearly_expenditure;
    Node * current;
    switch (choice) {
        case '1':
            current=head;
            monthly_income=0;
            i=0;
            while (current!=NULL) {
                if (current->info.income_or_expeneses=='1') {
                    if (i==0)
                        //initialize date to the first date that has the income
                        date=current->info.date;
                    new_date=current->info.date;
                    if (new_date/100>date/100) {
                        // this is a new month
                        cout<<date/10000<<"-"<<setfill('0')<<setw(2)<<date/100-100*(date/10000)<<" ";
                        cout.setf(ios::fixed,ios::floatfield);
                        cout.precision(2);
                        cout<<monthly_income<<endl;
                        cout<<setfill(' ');
                        monthly_income=0;
                    }
                    monthly_income+=current->info.amount;
                    date=new_date;
                    i++;
                }
                current=current->next;
            }
            cout<<new_date/10000<<"-"<<setfill('0')<<setw(2)<<new_date/100-100*(new_date/10000)<<" ";
            cout.setf(ios::fixed,ios::floatfield);
            cout.precision(2);
            cout<<monthly_income<<endl;
            cout<<setfill(' ');
            current=NULL;
            delete current;
            break;
        case '2':
            current=head;
            yearly_income=0;
            i=0;
            while (current!=NULL) {
                if (current->info.income_or_expeneses=='1') {
                    if (i==0)
                        //initialize date to the first date that has the expenditure
                        date=current->info.date;
                    new_date=current->info.date;
                    if (new_date/10000>date/10000) {
                        // this is a new year
                        cout<<date/10000<<" ";
                        cout.setf(ios::fixed,ios::floatfield);
                        cout.precision(2);
                        cout<<yearly_income<<endl;
                        cout<<setfill(' ');
                        yearly_income=0;
                    }
                    yearly_income+=current->info.amount;
                    date=new_date;
                    i++;
                }
                current=current->next;
            }
            cout<<new_date/10000<<" ";
            cout.setf(ios::fixed,ios::floatfield);
            cout.precision(2);
            cout<<yearly_income<<endl;
            cout<<setfill(' ');
            current=NULL;
            delete current;
            break;
        case '3':
            current=head;
            monthly_expenditure=0;
            i=0;
            while (current!=NULL) {
                if (current->info.income_or_expeneses=='2') {
                    if (i==0)
                        //initialize date to the first date that has the income
                        date=current->info.date;
                    new_date=current->info.date;
                    if (new_date/100>date/100) {
                        // this is a new month
                        cout<<date/10000<<"-"<<setfill('0')<<setw(2)<<date/100-100*(date/10000)<<" ";
                        cout.setf(ios::fixed,ios::floatfield);
                        cout.precision(2);
                        cout<<monthly_expenditure<<endl;
                        cout<<setfill(' ');
                        monthly_expenditure=0;
                    }
                    monthly_expenditure+=current->info.amount;
                    date=new_date;
                    i++;
                }
                current=current->next;
            }
            cout<<new_date/10000<<"-"<<setfill('0')<<setw(2)<<new_date/100-100*(new_date/10000)<<" ";
            cout.setf(ios::fixed,ios::floatfield);
            cout.precision(2);
            cout<<monthly_expenditure<<endl;
            cout<<setfill(' ');
            current=NULL;
            delete current;
            break;
        case '4':
            current=head;
            yearly_expenditure=0;
            i=0;
            while (current!=NULL) {
                if (current->info.income_or_expeneses=='2') {
                    if (i==0)
                        //initialize date to the first date that has the expenditure
                        date=current->info.date;
                    new_date=current->info.date;
                    if (new_date/10000>date/10000) {
                        // this is a new year
                        cout<<date/10000<<" ";
                        cout.setf(ios::fixed,ios::floatfield);
                        cout.precision(2);
                        cout<<yearly_expenditure<<endl;
                        cout<<setfill(' ');
                        yearly_expenditure=0;
                    }
                    yearly_expenditure+=current->info.amount;
                    date=new_date;
                    i++;
                }
                current=current->next;
            }
            cout<<new_date/10000<<" ";
            cout.setf(ios::fixed,ios::floatfield);
            cout.precision(2);
            cout<<yearly_expenditure<<endl;
            cout<<setfill(' ');
            current=NULL;
            delete current;
            break;
        case '5':
            current=head;
            double clo=0,foo=0,hou=0,tra=0,ent=0,edu=0,med=0,ins=0,oth=0;
            while (current!=NULL) {
                if (current->info.income_or_expeneses=='2') {
                    switch (current->info.type) {
                        case '1':
                            clo+=current->info.amount;
                            break;
                        case '2':
                            foo+=current->info.amount;
                            break;
                        case '3':
                            hou+=current->info.amount;
                            break;
                        case '4':
                            tra+=current->info.amount;
                            break;
                        case '5':
                            ent+=current->info.amount;
                            break;
                        case '6':
                            edu+=current->info.amount;
                            break;
                        case '7':
                            med+=current->info.amount;
                            break;
                        case '8':
                            ins+=current->info.amount;
                            break;
                        case '9':
                            oth+=current->info.amount;
                    }
                }
                current=current->next;
            }
            double total=clo+foo+hou+tra+ent+edu+med+ins+oth;
            cout<<fixed<<setprecision(2);
            cout<<"Clothing       "<<100*clo/total<<"%"<<endl;
            cout<<"Food           "<<100*foo/total<<"%"<<endl;
            cout<<"Houseware      "<<100*hou/total<<"%"<<endl;
            cout<<"Transportation "<<100*tra/total<<"%"<<endl;
            cout<<"Entertainment  "<<100*ent/total<<"%"<<endl;
            cout<<"Education      "<<100*edu/total<<"%"<<endl;
            cout<<"Medicine       "<<100*med/total<<"%"<<endl;
            cout<<"Insurance      "<<100*ins/total<<"%"<<endl;
            cout<<"Others         "<<100*oth/total<<"%"<<endl;
            current=NULL;
    }
    current=NULL;
    delete current;
}

// Function: multiply the budget (if it's already set)
//           and all the amount of money in the records
//           by an exchange rate given by the user
// Input: Node * head: the pointer pointing to the fist node of the linked list
//        double budget: the budget set by the user (-1 if it's not set)
void currency(Node * & head, double & budget) {
    cout<<"Please enter the exchange rate."<<endl;
    cout<<"Here are some approximate exchange rates from HKD to other currencies. Only for reference."<<endl;
    cout<<"USD *0.137"<<endl;
    cout<<"EUR *0.114"<<endl;
    cout<<"JPY *14.2"<<endl;
    cout<<"GBP *0.0988"<<endl;
    cout<<"AUD *0.182"<<endl;
    cout<<"SGD *0.174"<<endl;
    cout<<"CNY *0.860"<<endl;
    cout<<"Please note that your budget will also change if you have set it."<<endl;
    double rate;
    cin>>rate;

    Node * current = head;
    while (current!=NULL) {
        current->info.amount*=rate;
        current=current->next;
    }

    if (budget!=-1)
        budget*=rate;
    current=NULL;
    delete current;
    cout<<"Operation successful."<<endl;
}

// Function: read the user's command, and then execute the corresponding function
// Input: char command: the command input by the user
//        Node * head: the pointer pointing to the fist node of the linked list
//        double budget: the budget set by the user (-1 if it's not set)
void read_command(char command, Node * & head, double & budget) {
    switch (command) {
        case '1':
            change_budget(head, budget);
            break;
        case '2':
            add(head, budget);
            break;
        case '3':
            del(head);
            break;
        case '4':
            edit(head, budget);
            break;
        case '5':
            show(head);
            break;
        case '6':
            f_out(head);
            break;
        case '7':
            search(head);
            break;
        case '8':
            check(head);
            break;
        case '9':
            currency(head, budget);
            break;
        default:
            cout<<"Invalid command! Please select another choice."<<endl;
    }
}

