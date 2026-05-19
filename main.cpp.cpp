
//G21328044 K.A Tharusha Lakshan Dananjaya

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iomanip>

using namespace std;

// Constants for tax calculations and default values
const double TAX_FREE_ALLOWANCE = 12570.0;
const double TAX_RATE = 0.2;
const int MONTHS_IN_YEAR = 12;

// Constants for Default Values
const float DEFAULT_HOURS_WORKED = 0;
const double DEFAULT_TOTAL_MONTHLY_PAY = 0;
const double DEFAULT_TOTAL_POST_TAX_PAY = 0;

// Constants for File Names
const string Employee_File_Name = "employees.txt";
const string Error_File_Name = "errors.txt";

// Structure to hold employee details
struct Employee {
    string id;					// Employee ID
    string name;				// Employee Name
    double rateOfPay; 				// Hourly rate of pay
    float hoursWorked = DEFAULT_HOURS_WORKED;   // Default hours worked set to Zero
    double monthlyPay;				// Monthly pay before tax
    double postTaxPay;				// Monthly pay after tax deduction
};

// Structure to store payroll information for a specific month
struct Payroll {
    string month;		                // Month of the payroll
    vector<Employee> employees;                 // List of employees and their details in the payroll
};

// Function declarations
string selectMonthFile();	                                          // Prompt user to enter a month file
string toUpperCase(string str);                                           // Convert string to uppercase
void addErrorLogHeaders(ofstream& errorLog);                              //Add headers to the error file
void generatePayroll(vector<Payroll>& payrolls, ofstream& errorLog);      // Main payroll generation function
void readEmployees(vector<Employee>& employees);                          // Read employee details from file
void readHoursWorked(vector<Employee>& employees, string monthFile, ofstream& errorLog);     // Read worked hours from file
void calculateMonthlyPay(vector<Employee>& employees);                    // Calculate monthly pay before tax
void calculateTax(vector<Employee>& employees);                           // Calculate tax and final pay
void displayEmployees(const vector<Employee>& employees);                 // Display employee payroll data
void saveToFile(const vector<Employee>& employees, string monthFile);     // Save payroll data to a file
void mainMenu(vector<Payroll>& payrolls, ofstream& errorLog);             // Main menu function
void viewAllRecords(const vector<Payroll>& payrolls);                     // View all payroll records
void displayEmployeeDetails(Employee& emp, string month);                 // Display employee details for a specific month
void displayTotalPay(vector<Payroll>& payrolls, string empId);            // Display total earnings across all months
void searchEmployeeMenu(vector<Payroll>& payrolls, string empId);         // Search employee menu in payroll records
bool findEmployeeInPayrolls(vector<Payroll>& payrolls, string empId, bool allMonths, string month);   // Find an employee Id


int main() 
{
    vector<Payroll> payrolls;                       //create a vector to store month of payrole and employee details
    ofstream errorLog( Error_File_Name, ios::app);  //Create Errorlog File
    
    addErrorLogHeaders(errorLog);                   // Add headers to the error log file

    mainMenu(payrolls, errorLog);                   //SHow main Menu when starting program
    errorLog.close();                               //Close Error log when exit program
}

// Add headers to the error log file
void addErrorLogHeaders(ofstream& errorLog) 
{
    errorLog << left << setw(50) << "Name of pay file where error occurred" 
             << "Error description" << endl;
    errorLog << "---------------------------------------------"
             << "---------------------------------------------" << endl;
}

// Display Main Menu with Error Handling and Exit Option
void mainMenu(vector<Payroll>& payrolls, ofstream& errorLog) 
{
    string input;

    while (true) 
    {   
        cout << "**********************************\n"
             << "Select one from below to continue:\n"
             << "**********************************\n"
             << "1. Generate payroll\n2. Search Employee\n3. View All Employee Records\n"
             << "\nEnter the number of the option (or type 'quit' to exit): ";

        cin >> input;
        input = toUpperCase(input); // Convert to uppercase for case-insensitive check

        if (input == "QUIT") 
        {
            cout << "Exiting program...\n"; 
            return;
        } 
        else if (input == "1") generatePayroll(payrolls, errorLog);
        else if (input == "2") 
        {
            string empId;
            cout << "\nEnter Employee ID to search or type 'quit' to exit: ";
            cin >> empId;
            empId = toUpperCase(empId);
            if (empId == "QUIT")continue;
            else searchEmployeeMenu(payrolls, empId);
        } 
        else if (input == "3") viewAllRecords(payrolls);
        else 
        {
            cout << "\nInvalid option! Please enter a valid number (1-3) or 'quit' to exit.\n";
        }
    }
}

// Generate payroll for the selected month
void generatePayroll(vector<Payroll>& payrolls, ofstream& errorLog) 
{
    while (true) 
    {
        string monthFile = selectMonthFile();
        if (monthFile == "quit") return;
            
        ifstream inputFile(monthFile); // Check if the file exists

        if (!inputFile) 
        {
            cout << "\nError opening " << monthFile << " file. " 
                 << "Please enter again.\n";
            continue;
        } 
	else 
	{
    	   inputFile.close();
    
    	   // Check if payroll for the month already exists
    	   bool payrollExists = false;
    	   for (int i = 0; i < payrolls.size(); ++i) 
    	   {
        	if (payrolls[i].month == monthFile) 
        	{
            	    payrollExists = true;
            	    cout << "Payroll for " << monthFile << " already exists. "
                         << "Updating existing payroll.\n";
            
                    // Update existing payroll
                    readHoursWorked(payrolls[i].employees, payrolls[i].month, errorLog);
            	    calculateMonthlyPay(payrolls[i].employees);
            	    calculateTax(payrolls[i].employees);
            	    displayEmployees(payrolls[i].employees);
            	    saveToFile(payrolls[i].employees, payrolls[i].month);
            	    break;
                }
          }
    	  
    	  // Create new payroll if it doesn't exist
    	  if (!payrollExists) 
    	  {
             Payroll payroll;
             payroll.month = monthFile;

             readEmployees(payroll.employees);  // Read employee data
             readHoursWorked(payroll.employees, payroll.month, errorLog);
             calculateMonthlyPay(payroll.employees);
             calculateTax(payroll.employees);

             payrolls.push_back(payroll);  // Store the payroll in the vector
             displayEmployees(payroll.employees);
             saveToFile(payroll.employees, payroll.month);
    	  }
       }
    }
}

// prompt user to enter Month file name
string selectMonthFile() 
{
    string monthFile;
    cout << "\nEnter the month file name (e.g., Jan25.txt) or type 'quit' to return to main menu: ";
    cin >> monthFile;
    return monthFile;
}

// Convert Employee ID to uppercase
string toUpperCase(string str) 
{
    for (int i = 0; i < str.length(); i++) 
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

// Read employee details from employees.txt
void readEmployees(vector<Employee>& employees) 
{
    ifstream inputFile(Employee_File_Name); // Open the file

    if (!inputFile) cout << "\nError opening employees.txt file.\n";
    else 
    {
        Employee emp;
        while (inputFile >> emp.id >> emp.name >> emp.rateOfPay) 
        {
            employees.push_back(emp);
        }
    }inputFile.close(); // Close the file
}

// Read hours worked from selected file
void readHoursWorked(vector<Employee>& employees, string monthFile, ofstream& errorLog) 
{
    ifstream inputFile(monthFile); // Open the file

    if (!inputFile) 
    {
        cout << "\nError opening " << monthFile << " file.\n";
        return;
    }

    string line;
    string empId;
    float hours;

    while (getline(inputFile, line)) 
    { 
        // Read the entire line
        stringstream ss(line); // Use a stringstream to split
        ss >> empId;

        empId = toUpperCase(empId); // Normalize ID

        if (!(ss >> hours)) // If hours is missing or invalid
        { 
            errorLog << left << setw(50) << monthFile
                     << "Pay entry for " << empId << " is incomplete.\n";
            errorLog.flush();
            hours = DEFAULT_HOURS_WORKED ; // Default to zero
        }

        // Check if empId exists in the employees list
        bool found = false;
        for (int i = 0; i < employees.size(); i++) 
        {
            if (employees[i].id == empId) 
            {
                employees[i].hoursWorked = hours;
                found = true;
                break;
            }
        }

        if (!found) 
        {
            errorLog << left << setw(50) << monthFile
                     << empId << " is not a valid employee ID number.\n";
            errorLog.flush();
        }
    }
    inputFile.close();
}



// Calculate the monthly pay (Before Tax)
void calculateMonthlyPay(vector<Employee>& employees) 
{
    for (int i = 0; i < employees.size(); i++) 
    {
        //Multiply the rate of pay with valur of hours worked and get monthly Pay
        employees[i].monthlyPay = employees[i].rateOfPay * employees[i].hoursWorked;
    }
}

// Calculate the monthly pay after Tax
void calculateTax(vector<Employee>& employees) 
{
    for (int i = 0; i < employees.size(); i++) 
    {
        Employee& emp = employees[i];      //Pass the current employee as a referrence to a struct

        double annualIncome = emp.monthlyPay * MONTHS_IN_YEAR ;     // Find yearly income
        double taxableIncome = annualIncome - TAX_FREE_ALLOWANCE ;  // Subtract tax-free amount

        if (taxableIncome < 0) taxableIncome = 0;     // No negative tax

        double annualTax = taxableIncome * TAX_RATE ;  // 20% tax on taxable income
        double monthlyTax = annualTax / MONTHS_IN_YEAR ;  // Convert to monthly tax

        emp.postTaxPay = emp.monthlyPay - monthlyTax;  // Deduct tax from salary
    }
}

// Display employee details
void displayEmployees( const vector<Employee>& employees) 
{
    cout << endl;
    cout << left << setw(15) << "Employee_ID"
         << setw(15) << "Name"
         << setw(15) << "Rate of Pay"
         << setw(15) << "Hours Worked"
         << setw(25) << "Monthly Pay (Before)"
         << "Monthly Pay (After)" << endl;
    cout << "-------------------------------------------------"
         << "-------------------------------------------------------" << endl;

    for (int i = 0; i < employees.size(); i++) 
    {
        cout << left << setw(15) << employees[i].id
             << setw(15) << employees[i].name
             << setw(15) << employees[i].rateOfPay
             << setw(15) << employees[i].hoursWorked
             << fixed << setprecision(2)                             // Format to 2 decimal places
             << "€." << setw(23) << employees[i].monthlyPay
             << "€." << employees[i].postTaxPay << endl;
    }
}

// Write output to a file
void saveToFile(const vector<Employee>& employees, string monthFile) 
{   
    string outputFileName = monthFile.substr(0, monthFile.find('.')) + "_output.txt"; // Create output file name
    ofstream outputFile(outputFileName);

    if (!outputFile) cout << "\nError creating " << outputFileName << " file!\n";
    
    else 
    {
        // Write the header
        outputFile << left << setw(15) << "Employee_ID"
                   << setw(25) << "Monthly Pay (Before)"
                   << "Monthly Pay (After)" << endl;
        outputFile << "-----------------------------------------------------------\n";

        // Write each employee details
        for (int i = 0; i < employees.size(); i++) 
        {
            outputFile << left << setw(15) << employees[i].id
                       << fixed << setprecision(2)                    // Format to 2 decimal places
                       << "€." << setw(23) << employees[i].monthlyPay
                       << "€." << employees[i].postTaxPay << endl;
        }
    }
    outputFile.close();  // Close the file
    cout << "\nEmployee pay details saved to " << outputFileName << "\n";
}

// Search employee menu
void searchEmployeeMenu(vector<Payroll>& payrolls, string empId) 
{
    while (true) 
    {
        cout << "\nWhich month do you want to search:\n\n";
        cout << "1. January\n2. February\n3. March\n4. April\n5. All months together\n";
        cout << "\nEnter the number of the option or type 'quit' to return to main menu: ";

        int input;
        cin >> input;

        if (cin.fail()) 
        {
            cout << "\nInvalid Choice! Please try again.\n\n";
            cin.clear();
            cin.ignore(100 , '\n');
            continue;
        }

        string month;
        bool allMonths = false;

        switch (input) 
        {
            case 1:
                month = "Jan25.txt";
                break;
            case 2:
                month = "Feb25.txt";
                break;
            case 3:
                month = "Mar25.txt";
                break;
            case 4:
                month = "Apr25.txt";
                break;
            case 5:
                allMonths = true;
                break;
            default:
                cout << "\nInvalid option! Please try again.\n";
                continue;
        }

        bool found = findEmployeeInPayrolls(payrolls, empId, allMonths, month);
	
        if (found) return; 
        else 
        {
            cout << "\nEnter Employee ID to search or type 'quit' to return to main menu: ";
            cin >> empId;
            empId = toUpperCase(empId);
            if (empId == "QUIT") return;
        }
    }
}

// Find employee in payrolls
bool findEmployeeInPayrolls(vector<Payroll>& payrolls, string empId, bool allMonths, string month) 
{
    bool found = false;

    for (int i = 0; i < payrolls.size(); i++) 
    {
        if (allMonths || payrolls[i].month == month)  //check all months is true and match is equal to month
        {
            for (int j = 0; j < payrolls[i].employees.size(); j++) 
            {
                if (payrolls[i].employees[j].id == empId) //Check id is matching or not
                {
                    displayEmployeeDetails(payrolls[i].employees[j], payrolls[i].month);  // Display employee details
                    found = true;
                }
            }
        }
    }
    
    if (!found) 
    {
        if (allMonths) 
        {
            cout << "\nEmployee ID " << empId << " not found in payroll records.\n";
        } 
        else 
        {
            cout << "\nEmployee ID " << empId << " not found in payroll records for " << month << ".\n";
        }
    } 
    else 
    {
        if (allMonths) displayTotalPay(payrolls, empId);
    }return found; 
}

// Display employee details for a specific month
void displayEmployeeDetails(Employee& emp, string month) 
{
    cout << endl;
    cout << "Month : " << month << endl;
    cout << left << setw(15) << "Employee_ID"
         << setw(15) << "Name"
         << setw(15) << "Rate of Pay"
         << setw(15) << "Hours Worked"
         << setw(25) << "Monthly Pay (Before)"
         << "Monthly Pay (After)" << endl;
    cout << left << setw(15) << emp.id
         << setw(15) << emp.name
         << setw(15) << emp.rateOfPay
         << setw(15) << emp.hoursWorked
         << fixed << setprecision(2)           // Format to 2 decimal places
         << "€." << setw(23) << emp.monthlyPay
         << "€." << emp.postTaxPay << endl;
    cout << endl;
}

// Display total pay for an employee across all months
void displayTotalPay(vector<Payroll>& payrolls, string empId) 
{
    double totalMonthlyPay = DEFAULT_TOTAL_MONTHLY_PAY;
    double totalPostTaxPay = DEFAULT_TOTAL_POST_TAX_PAY;
    
    for (int i = 0; i < payrolls.size(); i++) 
    {
        for (int j = 0; j < payrolls[i].employees.size(); j++) 
        {
            if (payrolls[i].employees[j].id == empId) 
            {
                totalMonthlyPay += payrolls[i].employees[j].monthlyPay;
                totalPostTaxPay += payrolls[i].employees[j].postTaxPay;
            }
        }
    }

    cout << "Total Monthly Pay (Before Tax): €" << fixed << setprecision(2) << totalMonthlyPay;
    cout << "\nTotal Monthly Pay (After Tax): €" << fixed << setprecision(2) << totalPostTaxPay << "\n\n";
}

// View all records
void viewAllRecords(const vector<Payroll>& payrolls) 
{
    if (payrolls.empty()) 
    {
        cout << "\nCouldn't find any employee data. Try after generating payrolls!\n\n";
        return;
    }

    for (int i = 0; i < payrolls.size(); i++) 
    {
        cout << "\nPayroll for " << payrolls[i].month << ":\n";
        displayEmployees(payrolls[i].employees);                //Show all Employee Records
    }return;
}

