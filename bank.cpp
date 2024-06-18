#include <iostream>
using namespace std;

class bankAccount
{
    protected:
    std::string name;
    static int nextaccntnum;
    int accntnum;
    double balance;
    public:
    bankAccount(std::string a, double b, std::string c){
        name = a + ' ' + c; balance = b; accntnum =  1000 + nextaccntnum++;
    }
    std::string get_name(){
        return name;
    }
    void set_name(std::string newnameF, std::string newnameL){
        name = newnameF + " " + newnameL;
    }
    int get_accntN(){
        return accntnum;
    }
    void set_accntN(){
        accntnum += nextaccntnum;
    }
    double get_balance(){
        return balance;
    }
    void withdraw_balance(int amount){
        balance -= amount;
    }
    void deposit_balance(int amount){
        balance += amount;
    }
    virtual void writeCheck(double amount, std::string recipient) = 0;
    virtual ~bankAccount() {};
};
int bankAccount::nextaccntnum = 0;
class checkingAccount : public bankAccount
{
    public:
    checkingAccount(std::string a, double b, std::string c) : bankAccount(a, b, c) {}
    void writeCheck(double amount, std::string recipient) {}
    
};
class serviceChargeChecking : public checkingAccount
{
    int checks;
    public:
    serviceChargeChecking(std::string a, double b, std::string c) : checkingAccount(a, b, c), checks(5) {}
    void writeCheck(double amount, std::string recipient) {
        if (amount >= balance && checks == 0) {
            cout << "Insufficient funds to write a check for $" << amount << "\nor not enough checks available." << endl;        }
        else {
            balance -= amount;
            cout << "Writing a check for $" << amount << " to " << recipient << endl;
        }   

    }
    void get_checks(){
        cout << checks;
    }

};
class noServiceChecking : public checkingAccount
{
    double interest;
    public:
    double minBalance;
    noServiceChecking(std::string a, double b, std::string c, double d) : checkingAccount(a, b, c), minBalance(1000) {
        interest = d;
        if(b < minBalance){
            cout << "Your account does not meet the minimum balance!!" << endl;
            cout << "Please deposit so your balance " << b << " is at or above $" << minBalance << endl;
            cout << "Deposit: ";
            cin >> b;
            deposit_balance(b);
        }
    }
    void writeCheck(double amount, std::string recipient) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Writing a check for $" << amount << " to " << recipient << endl;
        }
        else {
            cout << "Insufficient funds to write a check for $" << amount << endl;
        } 
    }
    void monthlyCharge(){
        balance -= balance * interest;
        cout << balance;
    }
    void get_minBalance(){
        cout << minBalance;
    }
};
class highInterestChecking : public noServiceChecking
{
    double interest;
    public:
    double minBalance;
    highInterestChecking(std::string a, double b, std::string c, double d) : noServiceChecking(a, b, c, d), minBalance(2000) {
        interest = d;
        if(b < minBalance){
            cout << "Your account does not meet the minimum balance!!" << endl;
            cout << "Please deposit so your balance " << b << " is at or above $" << minBalance << endl;
            cout << "Deposit: ";
            cin >> b;
            deposit_balance(b);
        }
        if(interest < 3){
                interest = 3;
        }
    }
    void interestcharge(){
        double charge = balance * interest;
        balance -= balance * interest;
        cout << charge;
    }
    void monthlyCharge(){
        balance -= 20;
        cout << balance;
    }
    void get_minBalance(){
        cout << minBalance;
    }
};
class savingsAccount : public bankAccount
{
    protected:
    double interest;
    public:
    savingsAccount(std::string a, double b, std::string c, double d) : bankAccount(a, b, c) {
            interest = d;
            if(interest > 1){
                interest = 1;
            }
    }
    double get_interestRate(){
        return interest;
    }
    void set_interestRate(double value) {
        interest = value;
    }
    double post_interest(){
       cout << "After interest your balance is: "<< balance + (balance * (interest/100));
       return balance + (balance * (interest/100));
    }
    void withdraw_balance(double value){
        if(value > balance){
            cout << "Please enter a valid number";
        } else {
            balance -= value;
        }
    }
    void writeCheck(double amount, std::string recipient) {
        savingsAccount::writeCheck(amount, recipient);
    }
    void monthlyCharge(){
        balance -= 20;
        cout << balance;
    }
};
class highInterestSavings : public savingsAccount
{
    public:
    double minBalance;
    highInterestSavings(std::string a, double b, std::string c, double d) : savingsAccount(a, b, c, d), minBalance(1000) {
        double interestn = d;
        if(b < minBalance){
            cout << "Your account does not meet the minimum balance!!" << endl;
            cout << "Please deposit so your balance " << b << " is at or above $" << minBalance << endl;
            cout << "Deposit: ";
            cin >> b;
            deposit_balance(b);
        }
        if(interestn < 3){
            interest = 3;
        }
    }
    void writeCheck(double amount, std::string recipient) {
        savingsAccount::writeCheck(amount, recipient);
    }
    void get_minBalance(){
        cout << minBalance;
    }

};

class certificateOfDeposit : public bankAccount
{
public:
    certificateOfDeposit(std::string a, double b, std::string c, double d, int e) : bankAccount(a, b, c), interestRate(d), maturityMonths(e), cdMonth(0) {}
    double getInterestRate()
    {
        return interestRate;
    }
    void setInterestRate(double rate)
    {
        interestRate = rate;
    }
    int getMaturityMonths()
    {
        return maturityMonths;
    }
    void setMaturityMonths(int months)
    {
        maturityMonths = months;
    }
    double getCurrentCDMonth()
    {
        return cdMonth;
    }
    void setCurrentCDMonth(int month)
    {
        cdMonth = month;
    }
    void postInterest()
    {
        balance += balance * (interestRate / 12.0);
        cdMonth++;
        if (cdMonth >= maturityMonths)
        {
            cout << "Certificate of Deposit has matured. Balance: $" << balance << " is being paid out." << endl;
            balance = 0;
        }
    }
    void withdraw(double amount)
    {
        if (cdMonth < maturityMonths)
        {
            cout << "Cannot withdraw from Certificate of Deposit before maturity." << endl;
            return;
        }
        if (amount > balance)
        {
            cout << "Insufficient funds." << endl;
            return;
        }
        balance -= amount;
        cout << "Withdrawal of $" << amount << " from Certificate of Deposit successful." << endl;
    }
    void withdraw()
    {
        withdraw(balance);
    }
    void createMonthlyStatement()
    {
        cout << "Monthly Statement for Certificate of Deposit:" << endl;
        cout << "Account Name: " << name << endl;
        cout << "Account Number: " << accntnum << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Months to Maturity: " << maturityMonths - cdMonth << endl;
    }
    void writeCheck(double amount, std::string recipient) {
        certificateOfDeposit::writeCheck(amount, recipient);
    }
    private:
    static const double INTEREST_RATE;         
    static const int NUMBER_OF_MATURITY_MONTHS; 
    double interestRate;
    int maturityMonths;
    int cdMonth;
};
const double certificateOfDeposit::INTEREST_RATE = 0.05; 
const int certificateOfDeposit::NUMBER_OF_MATURITY_MONTHS = 6; 

int main(){
    cout << "\n                Savings Account";
    std::cout << "\n----------------------------------------------";
    savingsAccount object1("Ivan", 5000, "Sandoval", 0.6);
    cout << "\nAccount Holder Name: " << object1.get_name() << endl;
    cout << "Account Number: " << object1.get_accntN() << endl;
    cout << "Balance: $" << object1.get_balance() << endl;
    object1.deposit_balance(1000);
    cout << "Balance after deposit: $" << object1.get_balance() << endl;
    object1.withdraw_balance(200);
    cout << "Balance after withdrawal: $" << object1.get_balance() << endl;
    cout << "Interest Rate: %" << object1.get_interestRate() << endl;
    cout << "Post interest: ";
    object1.post_interest();
    cout << "\n----------------------------------------------";

    cout << "\n\n          High Interest Savings";
    cout << "\n----------------------------------------------";
    highInterestSavings object2("Elon", 10000, "Musk", 4);
    cout << "\nAccount Holder Name: " << object2.get_name() << endl;
    cout << "Account Number: " << object2.get_accntN() << endl;
    cout << "Balance: $" << object2.get_balance() << endl;
    object2.deposit_balance(1000);
    cout << "Balance after deposit: $" << object2.get_balance() << endl;
    object2.withdraw_balance(200);
    cout << "Balance after withdrawal: $" << object2.get_balance() << endl;
    cout << "Interest Rate: %" << object2.get_interestRate() << endl;
    cout << "Post interest: ";
    object2.post_interest();
    cout << "\nMinimum Balance: ";
    object2.get_minBalance();
    cout << endl;
    cout << "----------------------------------------------";
   
   cout << "\n\n          Service charge Checkings";
    cout << "\n----------------------------------------------";
    serviceChargeChecking object3("Jeff", 10000, "Bezos");
    cout << "\nAccount Holder Name: " << object3.get_name() << endl;
    cout << "Account Number: " << object3.get_accntN() << endl;
    cout << "Balance: $" << object3.get_balance() << endl;
    object3.deposit_balance(1000);
    cout << "Balance after deposit: $" << object3.get_balance() << endl;
    object1.withdraw_balance(200);
    cout << "Balance after withdrawal: $" << object3.get_balance() << endl;
    object3.writeCheck(2700, "Joe Biden");
    cout << "Number of checks left this month: ";
    object3.get_checks();
    cout << "\n----------------------------------------------";

    cout << "\n\n          No Service Checkings";
    cout << "\n----------------------------------------------";
    noServiceChecking object4("Mark", 10000, "Zuckerburg", 0.3);
    cout << "\nAccount Holder Name: " << object4.get_name() << endl;
    cout << "Account Number: " << object4.get_accntN() << endl;
    cout << "Balance: $" << object4.get_balance() << endl;
    object4.deposit_balance(1000);
    cout << "Balance after deposit: $" << object4.get_balance() << endl;
    object4.withdraw_balance(200);
    cout << "Balance after withdrawal: $" << object4.get_balance() << endl;
    cout << "Minimum Balance: ";
    object4.get_minBalance();
    cout << endl;
    cout << "----------------------------------------------";

    cout << "\n\n          Hihg Interest Checkings";
    cout << "\n----------------------------------------------";
    highInterestChecking object5("Isaac", 10000, "Newton", 6);
    cout << "\nAccount Holder Name: " << object5.get_name() << endl;
    cout << "Account Number: " << object5.get_accntN() << endl;
    cout << "Balance: $" << object5.get_balance() << endl;
    object5.deposit_balance(1000);
    cout << "Balance after deposit: $" << object5.get_balance() << endl;
    object5.withdraw_balance(200);
    cout << "Balance after withdrawal: $" << object5.get_balance() << endl;
    cout << "Minimum Balance: ";
    object4.get_minBalance();
    cout << "\nInterest charge: ";
    object5.interestcharge();
    cout << "\n----------------------------------------------";

    cout << "\n\n          Certificate of Deposit";
    cout << "\n----------------------------------------------";
    certificateOfDeposit object1cd("Randy", 10000, "Marsh", 0, 6);
    cout << "\nAccount Holder Name: " << object1cd.get_name() << endl;
    cout << "Account Number: " << object1.get_accntN() << endl;
    cout << "Months to Maturity: " << object1cd.getMaturityMonths() << endl;
    object1cd.postInterest();
    cout << "Balance after interest posting: $" << object1cd.get_balance() << endl;
    object1cd.withdraw(2000);
    cout << "Balance after withdrawal: $" << object1cd.get_balance() << endl;
    cout << "----------------------------------------------";

    return 0;
}
    
