#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
//this is our all protected variable
class Loan_Management_System {
protected:
    int customer_id, age;
    long long mobile_Number;
    string name, address;
    long long account_Number;
    string account_type, account_status, acc_op_date;
    long int balance, client_income;
    int account_credit;
    long int loan_id;
    string loan_type, status;
    long long loan_amount;
    float interest_rate;
    int loan_duration;
    double emi_amount;
    double remaining_balance;
    string propertyAddress;
    double propertyValue;
    string course_name;
    int study_year;
    string purpose;

public:
    void line() {
        cout << "=====================================================================================\n";
    }

    void help() {
        line();
        cout << left << setw(40) << "Help and Information" << endl;
        line();
        cout << "* Minimum age: 21 years\n";
        cout << "* Good CIBIL increases approval chance\n";
        cout << "* Income must match loan type\n";
        cout << "* Ensure correct details\n";
        line();
        cout << left << setw(40) << "Loan Types & Criteria" << endl;
        line();
        cout << left << setw(20) << "Loan Type" << setw(15) << "Max Amount" << setw(15) << "Min Income" << setw(20) << "Interest Rate(%)" << setw(10) << "CIBIL" << endl;
        line();
        cout << left << setw(20) << "Home Loan" << setw(15) << "50,00,000" << setw(15) << "30,000" << setw(20) << "8.5" << setw(10) << "700" << endl;
        cout << left << setw(20) << "Education Loan" << setw(15) << "15,00,000" << setw(15) << "15,000" << setw(20) << "12.0" << setw(10) << "600" << endl;
        cout << left << setw(20) << "Personal Loan" << setw(15) << "5,00,000" << setw(15) << "20,000" << setw(20) << "15.0" << setw(15) << "650" << endl;
        cout << left << setw(20) << "Gold Loan" << setw(15) << "75,000(MAX)" << setw(15) << "20,000" << setw(20) << "8.25" << setw(15) << "650" << endl;
        cout << left << setw(20) << "Car Loan" << setw(15) << "3,00,000" << setw(15) << "20,000" << setw(20) << "7.25" << setw(15) << "650" << endl;
        line();
        cout << "CIBIL Score:\n";
        cout << "300-499  : Bad\n";
        cout << "500-649  : Average\n";
        cout << "650-740  : Good\n";
        cout << "740-900  : Very Good\n";
        line();
    }

    void customer_Details() {
        ofstream file_customer("customer_details.txt", ios::app);
        cout << "Client Name: ";          cin >> name;
        cout << "Client Address: ";       cin >> address;
        cout << "Client Mobile Number: "; cin >> mobile_Number;
        cout << "Client Age: ";           cin >> age;
        cout << "Client ID: ";            cin >> customer_id;

        file_customer << "Client Name: " << name << endl;
        file_customer << "Client Address: " << address << endl;
        file_customer << "Client Mobile Number: " << mobile_Number << endl;
        file_customer << "Client Age: " << age << endl;
        file_customer << "Client ID: " << customer_id << endl;
        cout << "\nCustomer Details saved successfully!\n";
    }

    void account_Details() {
        ofstream file_account("account_details.txt", ios::app);
        cout << "Account Number: ";                  cin >> account_Number;
        cout << "Account Type(Saving/Current): ";    cin >> account_type;
        cout << "Account Balance: ";                 cin >> balance;
        cout << "Account Status(Active/Closed): ";   cin >> account_status;
        cout << "Account Opening Date(YY-MM-DD): ";  cin >> acc_op_date;
        cout << "Client Income: ";                   cin >> client_income;
        cout << "Client Credit Score: ";             cin >> account_credit;

        file_account << "Account Number: " << account_Number << endl;
        file_account << " Account Type(Saving/Current): " << account_type << endl;
        file_account << " Account Balance: " << balance << endl;
        file_account << " Account Status(Active/Closed): " << account_status << endl;
        file_account << " Account Opening Date(YY-MM-DD): " << acc_op_date << endl;
        file_account << " Client Income: " << client_income << endl;
        file_account << " Client Credit Score: " << account_credit << endl << endl;
        cout << "\nAccount Details saved successfully!\n";
    }

    void client_details() {
        cout << " Loan ID: ";               cin >> loan_id;
        cout << " Loan Amount: ";           cin >> loan_amount;
        cout << " Loan Duration (Years): "; cin >> loan_duration;
    }

    double calculateEMI(float rate) {
        interest_rate = rate;
        double r = interest_rate / (12 * 100);
        int n = loan_duration * 12;
        return (loan_amount * r * pow(1 + r, n)) / (pow(1 + r, n) - 1);
    }

    // NEW FUNCTION: Reads previous state to persist data across closures.
    bool loadData(int target_id) {
        bool found = false;
        ifstream infile("information.txt");
        if(infile.is_open()) {
            string line;
            while(getline(infile, line)) {
                // Strip Windows carriage return if present
                if (!line.empty() && line.back() == '\r') line.pop_back();

                // Exact match avoids ID '1' from accidentally matching ID '10' or '12'
                if(line == "Loan ID: " + to_string(target_id)) {
                    found = true;
                    loan_id = target_id;
                    
                    getline(infile, line); if (!line.empty() && line.back() == '\r') line.pop_back();
                    size_t pos = line.find(": ");
                    if(pos != string::npos) loan_amount = stoll(line.substr(pos+2));
                    
                    getline(infile, line); if (!line.empty() && line.back() == '\r') line.pop_back();
                    pos = line.find(": ");
                    if(pos != string::npos) {
                        try { interest_rate = stof(line.substr(pos+2)); } catch(...) {}
                    }
                    
                    getline(infile, line); if (!line.empty() && line.back() == '\r') line.pop_back();
                    pos = line.find(": ");
                    if(pos != string::npos) {
                        try { emi_amount = stod(line.substr(pos+2)); } catch(...) {}
                    }
                    
                    getline(infile, line); if (!line.empty() && line.back() == '\r') line.pop_back();
                    pos = line.find(": ");
                    if(pos != string::npos) {
                        try { remaining_balance = stod(line.substr(pos+2)); } catch(...) {}
                    }
                    
                    getline(infile, line); if (!line.empty() && line.back() == '\r') line.pop_back();
                    pos = line.find(": ");
                    if(pos != string::npos) status = line.substr(pos+2);
                }
            }
            infile.close();
        }
        return found;
    }

    void payEMI() {
        int user_loanId;
        cout << "\nEnter Loan ID to Pay EMI: ";
        cin >> user_loanId;

        // Tries to load previous data from file before making any transactions
        if (!loadData(user_loanId)) {
            cout << "Invalid Loan ID or Loan not found!" << endl;
            return;
        }

        if (status == "Closed") {
            cout << "Loan is already closed.\n";
            return;
        }

        double monthly_rate = interest_rate / (12 * 100);
        double interest = remaining_balance * monthly_rate;
        double principal = emi_amount - interest;
        remaining_balance -= principal;

        if (remaining_balance <= 0) {
            remaining_balance = 0;
            status = "Closed";
            cout << "\nCongratulations! Loan fully paid!\n";
        } else {
            cout << "\nEMI of " << emi_amount << " Paid. Remaining Balance: " << remaining_balance << endl;
        }

        ofstream file("information.txt", ios::app);
        file << "------------------------------EMI PAYMENT-----------------------------------------------\n";
        file << "Loan ID: " << loan_id << "\n";
        file << "Loan Amount: " << loan_amount << "\n";
        file << "Interest Rate: " << interest_rate << "%\n";
        file << "EMI: " << emi_amount << "\n";
        file << "Remaining Balance: " << remaining_balance << "\n";
        file << "Status: " << status << "\n";
        file.close();
    }

    void homeLoan() {
        client_details();
        cout << "Property Value: "; cin >> propertyValue;
        cout << "Property Address: "; cin >> propertyAddress;

        status = "Active";
        emi_amount = calculateEMI(8.5);
        remaining_balance = loan_amount;

        ofstream file("information.txt", ios::app);
        file << "--------------------------HOME LOAN---------------------------------------------------\n";
        file << "Loan ID: " << loan_id << "\n";
        file << "Loan Amount: " << loan_amount << "\n";
        file << "Interest Rate: " << interest_rate << "%\n";
        file << "EMI: " << emi_amount << "\n";
        file << "Remaining Balance: " << remaining_balance << "\n";
        file << "Status: " << status << "\n";
        file.close();
        cout << "\nHome Loan approved! ID: " << loan_id << " | EMI: " << emi_amount << "\n";
    }

    void educationLoan() {
        client_details();
        cout << "Course Name: "; cin >> course_name;
        cout << "Study Years: "; cin >> study_year;

        interest_rate = 12.0; // Fixed bug where calculation was made before assignment
        loan_amount *= pow(1 + interest_rate / 100, study_year);
        status = "Active";
        emi_amount = calculateEMI(interest_rate);
        remaining_balance = loan_amount;

        ofstream file("information.txt", ios::app);
        file << "------------------------------EDUCATIONAL LOAN-----------------------------------------------\n";
        file << "Loan ID: " << loan_id << "\n";
        file << "Loan Amount: " << loan_amount << "\n";
        file << "Interest Rate: " << interest_rate << "%\n";
        file << "EMI: " << emi_amount << "\n";
        file << "Remaining Balance: " << remaining_balance << "\n";
        file << "Status: " << status << "\n";
        file.close();
        cout << "\nEducation Loan approved! ID: " << loan_id << " | EMI: " << emi_amount << "\n";
    }

    void personalLoan() {
        client_details();
        cout << "Loan Purpose: "; cin >> purpose;

        status = "Active";
        emi_amount = calculateEMI(15.0);
        remaining_balance = loan_amount;

        ofstream file("information.txt", ios::app);
        file << "------------------------------PERSONAL LOAN-----------------------------------------------\n";
        file << "Loan ID: " << loan_id << "\n";
        file << "Loan Amount: " << loan_amount << "\n";
        file << "Interest Rate: " << interest_rate << "%\n";
        file << "EMI: " << emi_amount << "\n";
        file << "Remaining Balance: " << remaining_balance << "\n";
        file << "Status: " << status << "\n";
        file.close();
        cout << "\nPersonal Loan approved! ID: " << loan_id << " | EMI: " << emi_amount << "\n";
    }

    void goldloan() {
        float goldValue;
        client_details();
        cout << "Gold Value: "; cin >> goldValue;
        
        float lta = (loan_amount / goldValue) * 100;
        lta = lta * 100000;
        cout << "Loan To Value: " << lta << "\n";
        
        if (lta >= 75000) {
            status = "Active";
            emi_amount = calculateEMI(8.25);
            remaining_balance = loan_amount;

            ofstream file("information.txt", ios::app);
            file << "------------------------------GOLD LOAN-----------------------------------------------\n";
            file << "Loan ID: " << loan_id << "\n";
            file << "Loan Amount: " << loan_amount << "\n";
            file << "Interest Rate: " << interest_rate << "%\n";
            file << "EMI: " << emi_amount << "\n";
            file << "Remaining Balance: " << remaining_balance << "\n";
            file << "Status: " << status << "\n";
            file.close();
            cout << "\nGold Loan approved! ID: " << loan_id << " | EMI: " << emi_amount << "\n";
        } else {
            cout << "\nLoan rejected based on Loan To Value.\n";
        }
    }

    void carloan() {
        client_details();
        status = "Active";
        emi_amount = calculateEMI(7.25);
        remaining_balance = loan_amount;

        ofstream file("information.txt", ios::app);
        file << "------------------------------CAR LOAN-----------------------------------------------\n";
        file << "Loan ID: " << loan_id << "\n";
        file << "Loan Amount: " << loan_amount << "\n";
        file << "Interest Rate: " << interest_rate << "%\n";
        file << "EMI: " << emi_amount << "\n";
        file << "Remaining Balance: " << remaining_balance << "\n";
        file << "Status: " << status << "\n";
        file.close();
        cout << "\nCar Loan approved! ID: " << loan_id << " | EMI: " << emi_amount << "\n";
    }

    void display() {
        int user_loanId;
        cout << "\nEnter Loan ID to Display: ";
        cin >> user_loanId;
        
        if (!loadData(user_loanId)) {
            cout << "Loan not found!" << endl;
            return;
        }

        cout << "-----------------------------------------------------------------------------\n";
        cout << "Loan ID: " << loan_id << "\n";
        cout << "Loan Amount: " << loan_amount << "\n";
        cout << "Interest Rate: " << interest_rate << "%\n";
        cout << "EMI: " << emi_amount << "\n";
        cout << "Remaining Balance: " << remaining_balance << "\n";
        cout << "Status: " << status << "\n";
        cout << "-----------------------------------------------------------------------------\n";
    }

    void main_function() {
        string ch;
        cout << "-------------------------Instructions--------------------------------------\n";
        help();
        cout << "Do you want to apply for loan or track loan? (yes/no): ";
        cin >> ch;
        if (ch != "yes") return;

        int choice;
        do {
            cout << "\n1. Customer Details";
            cout << "\n2. Account Details";
            cout << "\n3. Home Loan";
            cout << "\n4. Education Loan";
            cout << "\n5. Personal Loan";
            cout << "\n6. Gold Loan";
            cout << "\n7. Car Loan";
            cout << "\n8. Pay EMI";
            cout << "\n9. Display Loan";
            cout << "\n0. Exit";
            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: customer_Details(); break;
                case 2: account_Details(); break;
                case 3: homeLoan(); break;
                case 4: educationLoan(); break;
                case 5: personalLoan(); break;
                case 6: goldloan(); break;
                case 7: carloan(); break;
                case 8: payEMI(); break;
                case 9: display(); break;
                case 0: cout << "Exiting system...\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 0);
    }
};

int main() {
    Loan_Management_System obj;
    obj.main_function();
    return 0;
}