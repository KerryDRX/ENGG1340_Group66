# Accounting System (ENGG1340_Group66)
## Problem Statement:
It is significant to manage our financial status and make better use of our money. Regarding daily wealth management, people have many demands that are difficult to meet through simple human memory. Therefore, we aim to develop such an accounting system using C++ and C programming codes to help people record revenues and expenditures and manage wealth.

The problems that our system need to solve include recording income and expenditure, recording additional information with the corresponding amount such as type, account, and date. The problems also include reminding customers when they spend more than their budget, telling them all details of the wealth status they have recorded.  We need to help customers calculate their net income in the past. We also need to find specific wealth records that meet the criteria based on some of the information provided by the customer. Showing customers their income and expenditure in recent months and telling them the proportion of expenses would be beneficial to their better management of wealth in the future. Furthermore, we need to solve the problems that people who occasionally travel abroad need to change the type and amount of currency records according to the exchange rate. Sometimes customers will need to pass in large amounts of data at once or export their wealth records for other uses.
## Problem Setting:
On entering the system, users can choose whether to set the expenditure budget or not according to their wishes. The budget can be changed after each round of operation. Users will be reminded of the exceeded amount and the corresponding month if the expenditure exceeds the budget.

Before performing other functionalities, users must add record(s) to the system at first.

When adding records to the system, users should provide full information on each record. Each record contains five items in order of amount, income or expenditure, type, account, date. The amount of money in the transactions entered by the user should not be too large (less than 100 billion).

Customers can search for specific records according to a certain interval of date or amount of money input by themselves. Customers can also choose whether to search for records by type and account. 

When checking financial states, customers should choose one operation provided by our system. They can check monthly or yearly income and expenses based on the records saved by our system. Customers can also check the ratio of one type of expenditure to the overall cost regarding all expenditure records.

When showing a list of records to users, we present a bill. The content of bill can be output as a file. Records in the bill are sorted according to the dates entered by the user. And each record is attached with a serial number according to its position in the bill.  In performing various calculations about the amount of money, our system will round the fractional part to two decimal places as most bank statements do.

Each time customers choose to edit or delete, they can only operate on one information. Unless the customer wants to change or delete something, the records input will always exist in the bill.

As for currency conversion, our system will provide a list of commonly used exchange rates based on Hong Kong users. And all they need to do is to enter the ratio and the amount of money in each record will be changed. The list is just for reference because the exchange rates change over time. If users want to have more accurate records, they need to query the real-time exchange rates themselves.

If users finish using the system, they can choose to quit and all data except the file output will be deleted.
## Functionalities and Features:
#### 1)	Budget setting. 
Our system allows users to set the expenditure budget on opening the system or after each round of operations. They can also change it after each round of operation. Whenever the monthly expenditure of some month(s) exceeds the budget after adding or editing, the system will remind users of the exceeded amount of money and the corresponding month(s) (if users have already set the budget). If there is no budget, the system will not give an alert.
#### 2)	Add records.
Our system allows users to add financial records by standard input or file input. If they choose to enter a record manually, they need to follow the guidance and answer five questions regarding five items of a record correspondingly. If they choose to enter records from a file, they need to provide the filename and an error message will be printed if our system cannot open the file. 
#### 3)	Delete records.
Our system allows users to delete one record in each round of operation. A list will be shown to users and they should provide the serial number of the record they wish to delete.
#### 4)	Edit records.
Our system allows users to edit one item (i.e. one piece of information) in each round of operation. A list will be shown to users and they should provide the serial number of the record they wish to edit and answer some questions to finish the edition.
#### 5)	Show records.
Our system can show all the records save in the system by standard output. Also, the net income based on all records in the presented list will be shown to users.
#### 6)	Write records to file
Our system can create a file according to the file name provided by users and output all records to this file. An error message will be printed if our system cannot open the file. 
#### 7)	Search records.
Our system allows users to search for certain records by amount, type, account, and date. All they need to do is to follow the guidance and answer some questions. They can choose whether to search by certain piece of information or not. And if they search by amount, they need to provide the minimum and maximum amount of money. If they search by date, they need to provide the earliest date and latest date.
#### 8)	Check financial states.
Our system allows users to check their financial states. They can choose to check monthly or yearly income and expenditure. They can also check the expenditure proportion (i.e. the ratio of one type of expenditure to the overall cost based on all expenditure records).
#### 9)	Change currency.
Our system can change the amount of money of all records if users provide the exchange rate. We also give users some commonly used exchange rates based on Hong Kong users for reference. Once the amount changes, it will not be restored.
## Input and Output Specifications:
### Input:
All inputs should strictly follow the rules that our output guidance messages provide. 

All multiple-choice questions with given options must be **only** inputted with the **given number** (e.g. Users **should not** input "*3*" or "*2. Expenditure*" if the above output message is "*Please indicate whether it is income or expenditure. 1. Income 2. Expenditure*").

When users input the amount of money of a record, the number (variable type: double) **should not be too large** (less than 100 billion).

When editing or deleting records, users **should not** input any number that **beyond** the serial numbers shown(output) in the table above.

When users input the date of a record, the input should be a **6-digit integer** in the format of *yyyymmdd* and it must represent a **valid date** in real life (e.g. Users should input "*20190427*" which represents April 27th in 2019).  

When adding records from a file, users should input the **full name** of a file (Input "*test.txt*" instead of "*test*" if the records are in an existing file test.txt). Furthermore, users must ensure that each line of this file should contain **five numbers** which also follow the rules mentioned above (e.g. A line contains "*5000 2 6 7 20190101*" is **valid** while a line contains "*5000 Expenditure Education Cash 20190101*" is **invalid**). 
### Output:
When users first enter our accounting system, it will output a **welcome message**. 

Then for the **beginning budget setting** module, it output a message including two options to ask whether users set budget or not. If users choose 1, it will output "*Please input your budget for every month.*" If you choose 2, it will output "*You have chosen not to set a budget. You can set your budget afterward.*". If you input an invalid choice, it will output "*Invalid choice. Budget setting failed. You can set your budget afterward.*".

The message "*Please make a choice:*" followed by "*0. Quit*" and 9 main functionalities of our system can be considered as the **main interface** of our accounting system. Hence, each round of operation starts with this.

A **separation line** will be output to separate each user input and each program output and output of different modules during the running of our system. This allows users to capture and identify information more clearly when running programs directly.

Our system always outputs some **guidance messages** whenever users need to input something. For multiple-choice questions in some modules, our system output **descriptions** followed by some options and **each option occupies one line**.

Our system also outputs some **confirmation message** when a certain operation is done. After users edit a record, it will output "*The edition is done.*". After users delete a record, it will output "*The deletion is done.*". After writing records to a file, it will output "*All your financial records have been written to filename.*"(filename is the name of the external file). After users set or change the budget, it will output "*Budget setting successful.*". After changing the type of currency, it will output "*Operation successful*".

Our system outputs **alert message** when necessary. If the system cannot open the file when adding records from a file, it will output an alert message "*Error in the file opening!*" and continue to next round of operation. Also, there would be an alert if the expenditure of any month exceeds the budget. The alert message of one month follows the format of "*Your monthly expenditure in yyyy-mm exceeds the budget by amount*" (amount is a double representing the exceeded amount of money). The message may contain multiple lines because there might not be only one monthly expenditure that exceeds the budget.

Whenever the system **shows a list of records** (it happens when users edit, show, search records or write records to file), it will output in such a format. The first line is the description of each item in one line of record. **Six items** are "*Serial Number*", "*Amount*", "*Income/Expenses*", "*Type*", "*Account*" and "*Date*". The following lines are the details of the records. Records in the list are sorted based on their dates and each record is attached with a serial number. The last line output tells users the **total net income** based on records of the list above (except when writing records to file).

When checking **financial states**, the system output guidance message including five options. When users choose 1 or 3, the output format is "*yyyy-mm amount*". When users choose 2 or 4, the output format is "*yyyy amount*". When users choose 5, the output is a table. First column presents all types of expenses, second column shows the corresponding proportion in % (round fractional part to two decimal places).

Whenever outputting the **amount of money**, our system will round the fractional part to **two decimal places**.

When users finally quit our system, it will output a **thank-you message**.
## Compilation and Execution Instructions:
