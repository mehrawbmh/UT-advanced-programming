#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const string &RESPONSE_OK = "OK";
const string

class User {
private:
    int id;
    double walletBalance;

    bool validate() { return id >= 1 && walletBalance >= 0; }

public:
    User(int, double);

    int getId();

    double getWalletBalance();;

    void withDrawFromWallet(double price);
};

User::User(int _id, double _wallet) {
    id = _id;
    walletBalance = _wallet;
    if (!validate()) {
        cerr << "wrong input format for user with id " << id;
    }
}

int User::getId() {
    return id;
}

double User::getWalletBalance() {
    return walletBalance;
}

void User::withDrawFromWallet(double price) {
    walletBalance -= price;
}

class ShortTermAccount {
private:
    int id;
    int userId;
    double initDeposit;
    double gainedProfit = 0.0;

public:
    ShortTermAccount(int, int, double);

    int getId();

    int getUserId();

    double getInitialInvestment();

    double getGainedProfit();

    void setGainedProfit(double);
};

ShortTermAccount::ShortTermAccount(int _id, int _userId, double _initDeposit) {
    id = _id;
    userId = _userId;
    initDeposit = _initDeposit;
}

int ShortTermAccount::getId() {
    return id;
}

int ShortTermAccount::getUserId() {
    return userId;
}

double ShortTermAccount::getInitialInvestment() {
    return initDeposit;
}

double ShortTermAccount::getGainedProfit() {
    return gainedProfit;
}

void ShortTermAccount::setGainedProfit(double _profitMoney) {
    gainedProfit = _profitMoney;
}

class LongTermAccount {
private:
    int id;
    int shortTermId;
    int years;
    double initInvestment;

public:
    LongTermAccount(int, int, double, int);

    int getId();

    int getShortTermId();

    double getInitialInvestment();

    int getYears();
};

LongTermAccount::LongTermAccount(int _id, int _shortTermId, double _investment, int _years) {
    id = _id;
    shortTermId = _shortTermId;
    initInvestment = _investment;
    years = _years;
}

int LongTermAccount::getId() {
    return id;
}

double LongTermAccount::getInitialInvestment() {
    return initInvestment;
}

int LongTermAccount::getYears() {
    return years;
}

int LongTermAccount::getShortTermId() {
    return shortTermId;
}

// gharz-ol-hasneh :)
class NoProfitAccount {
private:
    int id;
    int userId;
    double initDeposit;

public:
    NoProfitAccount(int, int, double);

    int getId();

    int getUserId();

    double getInitialInvestment();
};

NoProfitAccount::NoProfitAccount(int _id, int _userId, double _initInvestment) {
    id = _id;
    initDeposit = _initInvestment;
    userId = _userId;
}

int NoProfitAccount::getId() {
    return id;
}

int NoProfitAccount::getUserId() {
    return userId;
}

double NoProfitAccount::getInitialInvestment() {
    return initDeposit;
}

class Bank {
private:
    int id;
    int shortTermProfitMargin;
    double shortTermMinimumInvestment;

    bool validate();

    void updateShortTermAccounts(int months);

    void updateLongTermAccounts(int months);


public:
    vector<ShortTermAccount> shortTermAccounts;
    vector<LongTermAccount> longTermAccounts;
    vector<NoProfitAccount> noProfitAccounts;

    Bank(int, int, double);

    int getId() { return id; }

    int getShortTermProfitMargin();

    double getShortTermMinInvestement();

    int createShortTermAccount(int userId, double initInvestment);

    ShortTermAccount *findShortTermAccountById(int shortTermId);

    LongTermAccount *findLongTermAccountById(int shortTermId);

    string createLongTermAccount(int userId, double initInvestment, int shortTermId, int years);

    string createNoProfitAccount(int userId, double initInvestment);

    void updateAccountForMonths(int months);
};

Bank::Bank(int _id, int _stpm, double _stmi) {
    id = _id;
    shortTermProfitMargin = _stpm;
    shortTermMinimumInvestment = _stmi;
    if (!validate()) {
        cerr << "wrong input format in bank with id " << id << endl;
    }
}

void Bank::updateShortTermAccounts(int months) {
    cout << "\n updating short terms for " << months << " months...\n";
    for (int i = 0; i < shortTermAccounts.size(); i++) {
        int percent = months * shortTermProfitMargin;
        double profit = (100 + percent) * shortTermAccounts[i].getInitialInvestment() / 100;
        cout << "profit: " << profit << endl;

        ShortTermAccount *current = &shortTermAccounts[i];
        current->setGainedProfit(profit);
    }
}

void Bank::updateLongTermAccounts(int months) {
    cout << "\n updating long terms for " << months << " months...\n";

    for (int i = 0; i < longTermAccounts.size(); i++) {
        int percent = longTermAccounts[i].getYears() * shortTermProfitMargin * months;
        double profit = (100 + percent) * longTermAccounts[i].getInitialInvestment() / 100;

        ShortTermAccount *shortTermAccount = findShortTermAccountById(longTermAccounts[i].getShortTermId());
        shortTermAccount->setGainedProfit(shortTermAccount->getGainedProfit() + profit);
    }
}

bool Bank::validate() {
    return shortTermProfitMargin > 0 && shortTermMinimumInvestment >= 0 && id >= 1;
}

double Bank::getShortTermMinInvestement() {
    return shortTermMinimumInvestment;
}

int Bank::getShortTermProfitMargin() {
    return shortTermProfitMargin;
}

int Bank::createShortTermAccount(int userId, double initInvestment) {
    ShortTermAccount newAccount = ShortTermAccount(
            static_cast<int>(shortTermAccounts.size()) + 1,
            userId,
            initInvestment
    );

    shortTermAccounts.push_back(newAccount);
    return newAccount.getId();
}

ShortTermAccount *Bank::findShortTermAccountById(int shortTermId) {
    for (ShortTermAccount &shortTermAccount: shortTermAccounts) {
        if (shortTermAccount.getId() == shortTermId) {
            return &shortTermAccount;
        }
    }
    return nullptr;
}

LongTermAccount *Bank::findLongTermAccountById(int shortTermId) {
    for (LongTermAccount &longTermAccount: longTermAccounts) {
        if (longTermAccount.getId() == shortTermId) {
            return &longTermAccount;
        }
    }
    return nullptr;
}

string Bank::createLongTermAccount(int userId, double initInvestment, int shortTermId, int years) {
    ShortTermAccount *shortTermAccount = findShortTermAccountById(shortTermId);
    if (shortTermAccount == nullptr || shortTermAccount->getUserId() != userId) {
        return "Invalid short-term deposit";
    }

    cout << "\neverything valid...\n short term account: " << shortTermAccount->getId() << " for user: "
         << shortTermAccount->getUserId() << endl;
    longTermAccounts.push_back(
            LongTermAccount(static_cast<int>(longTermAccounts.size()) + 1, shortTermAccount->getId(),
                            initInvestment, years));
    return "OK";
}

string Bank::createNoProfitAccount(int userId, double initInvestment) {
    noProfitAccounts.push_back(
            NoProfitAccount(static_cast<int>(noProfitAccounts.size()) + 1, userId, initInvestment));
    return "OK";
}

void Bank::updateAccountForMonths(int months) {
    updateShortTermAccounts(months);
    updateLongTermAccounts(months);
}


class CsvReader {
private:
    static vector<vector<string>> readCsv(const string &fileName);

public:
    static vector<Bank> readBanks(const string &fileName);

    static vector<User> readUsers(const string &fileName);
};

vector<vector<string>> CsvReader::readCsv(const string &fileName) {
    vector<vector<string>> rows;

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "\nerror happened while reading the csv file\n";
        return {};
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        vector<string> row;
        istringstream lineStream(line);
        string item;

        while (getline(lineStream, item, ',')) {
            row.push_back(item);
        }
        rows.push_back(row);
    }

    file.close();
    return rows;
}

vector<Bank> CsvReader::readBanks(const string &fileName) {
    vector<Bank> result;
    vector<vector<string>> data = readCsv(fileName);

    for (vector<string> row: data) {
        result.push_back(Bank(stoi(row[0]), stoi(row[1]), stod(row[2])));
    }
    return result;
}

vector<User> CsvReader::readUsers(const string &fileName) {
    vector<User> result;
    vector<vector<string>> data = readCsv(fileName);

    for (vector<string> row: data) {
        result.push_back(User(stoi(row[0]), stod(row[1])));
    }
    return result;
}

class BankManager {
private:
    int monthsPassed = 0;
    vector<Bank> banks;
    vector<User> users;

    User *findUserById(int userId);

    Bank *findBankById(int bankId);

public:
    BankManager(vector<User>, vector<Bank>);

    vector<User> getUsers() { return users; }

    vector<Bank> getBanks() { return banks; }

    int getPassedMonths() { return monthsPassed; }

    void passTime(int months);

    double getUserBalanceInBankForAccount(int userId, int bankId, int shortTermAccountId);

    double getUserBalanceInBank(int userId, int bankId);

    double getUserBalance(int userId);

    int createShortTermAccount(int userId, int bankId, double initInvestment);

    string createLongTermAccount(int userId, int bankId, int shortTermId, int years, double initInvestment);

    string createNoProfitAccount(int userId, int bankId, double initInvestment);
};

BankManager::BankManager(vector<User> _users, vector<Bank> _banks) {
    users = _users;
    banks = _banks;
}

User *BankManager::findUserById(int userId) {
    for (User &user: users) {
        if (user.getId() == userId) {
            return &user;
        }
    }

    cerr << "\nuser not found!\n";
    return nullptr;
}

Bank *BankManager::findBankById(int bankId) {
    for (Bank &bank: banks) {
        if (bank.getId() == bankId) {
            return &bank;
        }
    }
    cerr << "bank not found!";
    return nullptr;
}

void BankManager::passTime(int months) {
    monthsPassed += months;
    for (Bank &bank: banks) {
        bank.updateAccountForMonths(months);
    }
}

double BankManager::getUserBalanceInBankForAccount(int userId, int bankId, int shortTermAccountId) {
    Bank *bank = findBankById(bankId);
    ShortTermAccount *shortTermAccount = bank->findShortTermAccountById(shortTermAccountId);

    if (shortTermAccount == nullptr || shortTermAccount->getUserId() != userId) {
        return -1.0;
    }
    return shortTermAccount->getGainedProfit() + shortTermAccount->getInitialInvestment();
}

double BankManager::getUserBalanceInBank(int userId, int bankId) {
    double final = 0.0;
    Bank *bank = findBankById(bankId);
    for (auto account: bank->shortTermAccounts) {
        if (account.getUserId() == userId) {
            final += account.getInitialInvestment() + account.getGainedProfit();
        }
    }
    return final;
}

double BankManager::getUserBalance(int userId) {
    double final = 0;
    for (Bank bank: banks) {
        final += getUserBalanceInBank(userId, bank.getId());
    }
    return final;
}

int BankManager::createShortTermAccount(int userId, int bankId, double initInvestment) {
    cout << "\ncreating short term account ... \n";
    User *user = findUserById(userId);
    Bank *bank = findBankById(bankId);
    if (user->getWalletBalance() < initInvestment || initInvestment < bank->getShortTermMinInvestement()) {
        return 0;
    }
//        cout << "HEREEE";
    user->withDrawFromWallet(initInvestment);
    return bank->createShortTermAccount(userId, initInvestment);
}

string BankManager::createLongTermAccount(int userId, int bankId, int shortTermId, int years, double initInvestment) {
    cout << "\ncreating long term account...\n";
    User *user = findUserById(userId);
    Bank *bank = findBankById(bankId);
    if (initInvestment < bank->getShortTermMinInvestement() * years || user->getWalletBalance() < initInvestment) {
        return "Not enough money";
    }
    cout << "enough money!...\n";
    user->withDrawFromWallet(initInvestment);
    return bank->createLongTermAccount(userId, initInvestment, shortTermId, years);
}

string BankManager::createNoProfitAccount(int userId, int bankId, double initInvestment) {
    cout << "\n creating gharzol ... \n";
    User *user = findUserById(userId);
    Bank *bank = findBankById(bankId);

    user->withDrawFromWallet(initInvestment);
    return bank->createNoProfitAccount(userId, initInvestment);
}

class PromptManager {
private:
    static BankManager createManager(const string &banksFileName, const string &usersFileName) {
        return BankManager(CsvReader::readUsers(usersFileName), CsvReader::readBanks(banksFileName));
    }

    static vector<string> getCommandArgs(const string &command) {
        vector<string> commandArgs;
        istringstream lineStream(command);
        string item;

        while (getline(lineStream, item, ' ')) {
            commandArgs.push_back(item);
        }
        return commandArgs;
    }

    static void handleCommand(string command, BankManager &manager) {
        vector<string> commandArgs = getCommandArgs(command);
        command = commandArgs[0];

        if (command == "create_short_term_deposit") {
            int accountId = manager.createShortTermAccount(
                    stoi(commandArgs[1]),
                    stoi(commandArgs[2]),
                    stod(commandArgs[3])
            );
            cout << ((accountId == 0) ? "Not enough money" : to_string(accountId));

        } else if (command == "create_long_term_deposit") {
            cout << manager.createLongTermAccount(
                    stoi(commandArgs[1]),
                    stoi(commandArgs[2]),
                    stoi(commandArgs[3]),
                    stoi(commandArgs[4]),
                    stod(commandArgs[5])
            );
        } else if (command == "create_gharzolhasane_deposit") {
            cout << manager.createNoProfitAccount(
                    stoi(commandArgs[1]),
                    stoi(commandArgs[2]),
                    stod(commandArgs[3])
            );
        } else if (command == "pass_time") {
            manager.passTime(stoi(commandArgs[1]));
            cout << "OK";
        } else if (command == "inventory_report") {
            double result = manager.getUserBalanceInBankForAccount(
                    stoi(commandArgs[1]),
                    stoi(commandArgs[2]),
                    stoi(commandArgs[3])
            );
            if (result == -1.0) {
                cout << "Invalid short-term deposit";
            } else {
                cout << result;
            }
        } else if (command == "calc_money_in_bank") {
            cout << manager.getUserBalanceInBank(stoi(commandArgs[1]), stoi(commandArgs[2]));
        } else if (command == "calc_all_money") {
            cout << manager.getUserBalance(stoi(commandArgs[1]));
        } else {
            std::cerr << "Unknown command" << std::endl;
        }
    }

public:
    static BankManager readInput(char *argv[]) {
        string flagOne = argv[1];
        string flagTwo = argv[3];

        if (flagOne == "-b" && flagTwo == "-u") {
            return createManager(argv[2], argv[4]);
        } else if (flagOne == "-u" && flagTwo == "-b") {
            return createManager(argv[4], argv[2]);
        } else {
            cerr << "\ninsufficient input provided\n" << endl;
        }
        return {{},{}};
    }

    static void processCommands(BankManager &manager) {
        string command;
        while (getline(cin, command)) {
            if (command.length() < 1) {
                cout << "empty command" << endl;
                return;
            }
            handleCommand(command, manager);
        }
    }
};

void setOutputFloatPrecision(int precision) {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(precision);
}

int main(int argc, char *argv[]) {
    setOutputFloatPrecision(2);

    if (argc < 5) {
        cerr << "wrong format of input";
        abort();
    }

    BankManager manager = PromptManager::readInput(argv);
    PromptManager::processCommands(manager);

    cout << "user 4 balance: " << manager.getUsers()[3].getWalletBalance() << endl;
    cout << "user 3 balance: " << manager.getUsers()[2].getWalletBalance() << endl;
    cout << "user 2 balance: " << manager.getUsers()[1].getWalletBalance() << endl;
    cout << "user 1 balance: " << manager.getUsers()[0].getWalletBalance() << endl;

    cout << "bank 2 PM: " << manager.getBanks()[1].getShortTermProfitMargin() << endl;

    cout << "bank 1 - account 2 - id: " << manager.getBanks()[0].shortTermAccounts[1].getId() << endl;
    cout << "bank 1 - account 2 - init invest: " << manager.getBanks()[0].shortTermAccounts[1].getInitialInvestment()
         << endl;
    cout << "bank 1 - account 2 - user id: " << manager.getBanks()[0].shortTermAccounts[1].getUserId() << endl;

    cout << "bank 1 - account 1 - id: " << manager.getBanks()[0].shortTermAccounts[0].getId() << endl;
    cout << "bank 1 - account 1 - init invest: " << manager.getBanks()[0].shortTermAccounts[0].getInitialInvestment()
         << endl;
    cout << "bank 1 - account 1 - user id: " << manager.getBanks()[0].shortTermAccounts[0].getUserId() << endl;

    for (ShortTermAccount &c: manager.getBanks()[0].shortTermAccounts) {
        cout << "bank 1: account number " << c.getId() << " : " << c.getUserId() << endl;
    }

    for (int i = 0; i < 3; i++) {
        cout << "\nbank 1: short term id " << i << " init and profit \n";
        cout << manager.getBanks()[0].shortTermAccounts[i].getId() << endl;
        cout << manager.getBanks()[0].shortTermAccounts[i].getInitialInvestment() << endl;
        cout << manager.getBanks()[0].shortTermAccounts[i].getGainedProfit() << endl;
    }

    cout << "\n no profits account: \n";
    cout << manager.getBanks()[3].noProfitAccounts[0].getId() << endl;
    cout << manager.getBanks()[3].noProfitAccounts[0].getUserId() << endl;
    cout << manager.getBanks()[3].noProfitAccounts[0].getInitialInvestment() << endl;

    return 0;
}
