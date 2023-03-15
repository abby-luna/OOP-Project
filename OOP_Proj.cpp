#include "CItem.h"
#include "CUser.h"

#include <fstream>
#include <sstream>

using namespace std;

const int MAX_ITEMS = 25;
const int MAX_USERS = 5;

CItem itemList[MAX_ITEMS] = { CItem() };
CUser userList[MAX_USERS] = { CUser() };;

int size = 0;

// 9

// menu options
void DoInitializePriceList(void);
void DoDisplayFullPriceList(void);
void DoAddItemToList(void);
void DoSetItemPrice(void);
void DoSetItemDiscountRate(void);
void DoDisplayItem(void);
void DoOrderCost(void);
void DoTotalInvoice(void);
void DoRemoveItemFromList(void);
void DoQuit(void);


void DoAddUser(void);
void DoEditUser(void);
/*

  std::ofstream outfile;

  outfile.open("test.txt", std::ios_base::app); // append instead of overwrite
  outfile << "Data";
  return 0;
  */


// Util functions

void SaveItemsToFile();
void fillUserList()
{
    ifstream file("userFile.csv");
    int index = 0;
    string line;
    while (getline(file, line) && index < MAX_USERS)
    {
        stringstream ss(line);

        std::string nameStr, passwordStr, typeStr;
        getline(ss, nameStr, ',');
        getline(ss, passwordStr, ',');
        getline(ss, typeStr, ',');

        std::cout << "LOADED USER " << nameStr  << " PASS " << passwordStr << endl;

        char type = typeStr[0];
        userList[index] = CUser(nameStr, type, passwordStr);
        index++;

    }
    file.close();
}

void fillItemList()
{
    ifstream file("itemFile.csv");
    int index = 0;
    string line;
    while (getline(file, line) && index < MAX_ITEMS)
    {
        stringstream ss(line);

        std::string codeStr, descStr, priceStr, rateStr;

        getline(ss, codeStr, ',');
        getline(ss, descStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, rateStr, ',');


        itemList[index] = CItem(stoi(codeStr), descStr, stod(priceStr), stod(rateStr));
        index++;

    }

    file.close();
}
int checkPrivlageLevel(char priv)
{
    if (priv == 'N')
        return 0;
    if (priv == 'A')
        return 1;
    if (priv == 'M')
        return 3;
    return -1;

}
void displayNums(int priv)
{
    if (priv > 0)
    {
        std::cout << std::endl << "1. Initialize price list" << std::endl;
        std::cout << "2. Display full price list" << std::endl;
        std::cout << "3. Add item to list" << std::endl;
        std::cout << "4. Set item price" << std::endl;
        std::cout << "5. Set item discount rate" << std::endl;
        std::cout << "6. Display item" << std::endl;
        std::cout << "7. Order cost" << std::endl;
        std::cout << "8. Total invoice" << std::endl;
        std::cout << "9. Remove Item From List" << std::endl;
    }
    if (priv > 2)
    {
        std::cout << "10. Add User" << std::endl;
        std::cout << "11. Edit User" << std::endl;
    }
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter choice: ";
}

int main()
{

    fillUserList();
    fillItemList();


    string uname;
    string pass;
    // n for no permissions
    char userType = 'N';
    bool found = false;
    cout << "Please enter your username: ";
    cin >> uname;
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (userList[i].getName() == uname)
        {
            cout << "Please enter your password: ";
            cin >> pass;
            if (userList[i].auth(pass))
            {
                userType = userList[i].getType();
                std::cout << "Logged in as " << uname << endl;
            }
            else
            {
                std::cout << "Incorrect password: No access granted" << endl;
            }




        }
    }

    int choice;
    displayNums(checkPrivlageLevel(userType));
    do {

        std::cin >> choice;
        switch (choice) {


        case 1:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoInitializePriceList();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 2:
            if (checkPrivlageLevel(userType) > 0)
                DoDisplayFullPriceList();
            else
                cout << "you dont have access to this function\n";
            break;
        case 3:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoAddItemToList();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 4:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoSetItemPrice();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 5:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoSetItemDiscountRate();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 6:
            if (checkPrivlageLevel(userType) > 0)
                DoDisplayItem();
            else
                cout << "you dont have access to this function\n";
            break;
        case 7:
            if (checkPrivlageLevel(userType) > 0)
                DoOrderCost();
            else
                cout << "you dont have access to this function\n";
            break;
        case 8:
            if (checkPrivlageLevel(userType) > 0)
                DoTotalInvoice();
            else
                cout << "you dont have access to this function\n";
            break;
        case 9:
            if (checkPrivlageLevel(userType) > 0)
            {
                //cout << "Work in progress\n";
                DoRemoveItemFromList();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 10:
            if (checkPrivlageLevel(userType) > 1)
                DoAddUser();
            else
                cout << "you dont have access to this function\n";
            break;
        case 11:
            if (checkPrivlageLevel(userType) > 1)
                DoEditUser();
            else
                cout << "you dont have access to this function\n";
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    } while (choice != 0);
}


void DoInitializePriceList(void)
{
    char res;
    cout << "Do you wish to start over (Y or N)? ";
    cin >> res;

    if (res == 'Y' || res == 'y')
    {
         // reset array
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            itemList[i] = CItem();
        }
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            int code;
            string desc;
            double price;
            double discRate;

            cout << "Enter item code for item " << i + 1 << ": ";
            cin >> code;
            cout << "Enter item description for item " << i + 1 << ": ";
            cin >> desc;
            cout << "Enter item price for item " << i + 1 << ": ";
            cin >> price;
            cout << "Enter item discount rate for item " << i + 1 << ": ";
            cin >> discRate;

            itemList[i] = CItem(code, desc, price, discRate);

            cout << "Item added";

            char another;
            cout << "Add another item (Y oder N)?";
            cin >> another;

            if (another == 'n' || another == 'N')
            {
                return;
            }

        }
    }
    else
    {
        // coninuing from closest 0 point

        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (itemList[i].GetCode() == 0)
            {
                int code;
                string desc;
                double price;
                double discRate;

                cout << "Enter item code for item " << i + 1 << ": ";
                cin >> code;
                cout << "Enter item description for item " << i + 1 << ": ";
                cin >> desc;
                cout << "Enter item price for item " << i + 1 << ": ";
                cin >> price;
                cout << "Enter item discount rate for item " << i + 1 << ": ";
                cin >> discRate;

                itemList[i] = CItem(code, desc, price, discRate);

                cout << "Item added";

                char another;
                cout << "Add another item (Y oder N)?";
                cin >> another;

                if (another == 'n' || another == 'N')
                {
                    return;
                }

            }

        }

    }
}

void DoDisplayFullPriceList(void)
{
    //display a suitable item table header 
    //display all of the items in the item list


    for (int i = 0; i < MAX_ITEMS; i++)
    {


        if (itemList[i].GetCode() == 0)
        {
            return;
        }
        itemList[i].Display();
    }
}

void DoAddItemToList(void) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].GetCode() == 0) {

            int code;
            string desc;
            double price;
            double discRate;

            cout << "Enter code for new item : ";
            cin >> code;
            cout << "Enter description for new item: ";
            cin >> desc;
            cout << "Enter price for new item: ";
            cin >> price;
            cout << "Enter discount rate for new item: ";
            cin >> discRate;

            itemList[i] = CItem(code, desc, price, discRate);
            cout << "New item added." << endl;


            return;
        }
    }
    cout << "Item list is full." << endl;
}

void DoSetItemPrice(void) {
    int code;
    cout << "Enter code for item: ";
    cin >> code;

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            int p;
            cout << "Enter new price for item: ";
            cin >> p;
            itemList[i].SetPrice(p);
            return;
        }
    }

    cout << "Item not found." << endl;

}

void DoSetItemDiscountRate(void) {
    int code;
    cout << "Enter code for item: ";
    cin >> code;

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            double p;
            cout << "Enter new discount rate for item: ";
            cin >> p;
            itemList[i].SetDiscountRate(p);
            return;
        }
    }

    cout << "Item not found." << endl;
}

void DoDisplayItem(void) {
    int code;
    cout << "Enter code for item: ";
    cin >> code;

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            itemList[i].Display();
            return;
        }
            
    }

    cout << "Item not found." << endl;
}

void DoOrderCost(void) {

    int code;
    cout << "Enter code for item: ";
    cin >> code;

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            int quantity;
            char discount;
            cout << "What quantity is required: ";
            cin >> quantity;

            cout << "Are they eligible for a discount: ";
            cin >> discount;

            if (discount == 'Y' || discount == 'y')
            {
                cout << "Price is " << itemList[i].GetDiscount() * quantity << endl;
                return;
            }
            cout << "Price is " << itemList[i].GetPrice() * quantity << endl;
            return;
        }

    }

    cout << "Item not found." << endl;

}

void DoTotalInvoice(void) {
    double totalCost = 0;
    cout << "Price List:" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Code\tDescription\tPrice\tDiscount" << endl;
    cout << "-------------------------------------" << endl;
    for (int i = 0; i < MAX_ITEMS; i++) {


        if (itemList[i].GetCode() == 0) 
        {
            break;
        }
            
       
        CItem item = itemList[i];
        cout << item.GetCode() << "\t" << item.GetDescription() << "\t\t" << item.GetPrice() << "\t" << item.GetDiscountRate() << endl;
        totalCost += item.GetPrice();
    }
    cout << "-------------------------------------" << endl;
    cout << "Total invoice: " << totalCost << endl;
}
void DoRemoveItemFromList(void) {
    int code;
    cout << "Enter code for item to remove: ";
    cin >> code;

    bool found = false;
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
            found = true;
        else
        {
            if (!found)
                itemList[i] = itemList[i];
            else
                itemList[i - 1] = itemList[i];

        }

    }

    if (!found)
        cout << "Item not found." << endl;

}

void SaveUsersToFile()
{

    ofstream outfile;
    outfile.open("userFile.csv");

    for (int i = 0; i < MAX_USERS; i++)
    {
        outfile << userList[i].getName() << "," << userList[i].getPass() << ',' << userList[i].getType() << "\n";

    }
    outfile.close();

}


void SaveItemsToFile()
{

    ofstream outfile;
    outfile.open("itemFile.csv");

    for (int i = 0; i < MAX_ITEMS; i++)
    {
        outfile << itemList[i].GetCode() << "," << itemList[i].GetDescription() << ',' << itemList[i].GetPrice() << ',' << itemList[i].GetDiscountRate() << "\n";

    }
    outfile.close();

}

void DoAddUser(void)
{

    string name;
    string password;
    char t;

    cout << "enter a username: ";
    cin >> name;

    cout << "enter a password: ";
    cin >> password;

    cout << "enter a usertype (A or M): ";
    cin >> t;
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (userList[i].getType() == 'N')
        {
            userList[i] = CUser(name, t, password);
            SaveUsersToFile();
            cout << "Success\n";
            return;

        }

    }

    cout << "Max users reached\n";
}
void DoEditUser(void)
{

    string name;

    cout << "enter a user to edit: ";
    cin >> name;

    for (int i = 0; i < MAX_USERS; i++)
    {
        if (userList[i].getName() == name)
        {
            string newPassword;
            cout << "enter the new password: ";
            cin >> newPassword;
            userList[i].setPass(newPassword);

            cout << "Password Updated Successfully\n";
            SaveUsersToFile();
            return;
        }

    }
    cout << "Password Updated Unsuccessfully\n";
    

}



    

