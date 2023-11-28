#include "CarRental.h"

int main()
{
    srand(time(0));

    CarRental CR;
    ofstream myFile;
    string fileNameInput = "inventory_1.txt";
    // cout << "Enter file name: ";
    // cin >> fileNameInput;
    myFile.open(fileNameInput, ios::app);// open file in append mode

    if(myFile.is_open())
    {
        // cout << "Success!" << endl;
        myFile.close();
        CR.setFileName(fileNameInput);
    }
    else
    {
        cout << "ERROR: Can't open " << fileNameInput << endl;
    }//LOOP UNTIL RIGHT DATA

    string input = "";
    do
    {
        cout << "Sign in\n" << "(1) Customer\n(2) Admin\n";
        cin >> input;
        if((input != "1") && (input != "2"))
        {
            system("cls");
            cout << "Invalid input. Please enter '1' or '2'.\n";
        }
    } while(input != "1" && input != "2");
        
    system("cls");
    string userType = "";
    (input == "1" ? userType = "Customer" : userType = "Admin");
    CR.setUserName(userType);
    
    cout << "Logged in as: " << userType << endl;
    
    string menu[] = {"Rent a Car", "Return a Car", "Show Inventory", "Add Car to System", "Remove Car from System"};
    int menuLength;
    (userType == "Customer" ?  menuLength = 3 : menuLength = 5);

    do
    {
        input = "";
        do
        {
            for (int i = 0; i < menuLength; i++)
            {
                cout << "(" << i + 1 << ") " << menu[i] << endl;
            }

            cout << "Enter your choice (or 'exit' to exit): ";
            cin >> input;

            if (input == "exit")
            {
                system("cls");
                break;
            }

            if (stoi(input) < 1 || stoi(input) > menuLength)
            {
                system("cls");
                cout << "Invalid input. Please enter a valid option.\n";
            }
        } while (stoi(input) < 1 || stoi(input) > menuLength);

        if (input == "exit")
        {
            break;
        }

        system("cls");
        int choice = stoi(input); // Convert string to integer
        
        switch(choice)
        {
            case 1:
                CR.rentCar();
                break;

            case 2:
                CR.returnCar();
                break;

            case 3:
                CR.showInventory();
                break;

            case 4:
                CR.addCar();
                break;
            case 5:
                CR.removeCar();
                break;    
            default:
                cout << "ERROR" << endl;
        };
        // system("cls");
    } while (true);
    
    return 0;
}//main