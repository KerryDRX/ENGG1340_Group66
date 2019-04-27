#ifndef FUNCTIONALITIES_H
#define FUNCTIONALITIES_H
struct information {
    int no;
    double amount;
    char income_or_expeneses;
    char type;
    char account;
    int date;
};
struct Node {
    information info;
    Node * next;
};
void update_no(Node * head);
void insert(Node * & head, Node * & p, int date);
void budget_warning(Node * head, double budget);
void change_budget(Node * head, double & budget);
void c_add(Node * & head, double budget);
void f_add(Node * & head, double budget);
void add(Node * & head, double budget);
void print_one_record(Node * current, double & total);
void show(Node * head);
void edit(Node * & head, double budget);
void del(Node * & head);
void f_out(Node * head);
void search(Node * head);
void check(Node * head);
void currency(Node * & head, double & budget);
void read_command(char command, Node * & head, double & budget);
#endif
