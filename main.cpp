#include <iostream>
#include <fstream>
#include <string>
#include <iterator> //size()
#include <cstdlib> // for system function

using namespace std;

class CarRental
{
public:
    CarRental();
    void rentCar();
    void returnCar();
    void addCar();
    void removeCar();
    void showInventory();

     // Setters
    void setFileName(const string& name);
    void setBrand(const string& newBrand);
    void setModel(const string& newModel);
    void setLastRented(const string& newLastRented);
    void setRentalLength(const string& newRentalLength);
    void setPrice(const string& newPrice);
    void setAvailable(const string& newAvailable);
    
    // Getters
    string getFileName() const;
    string getBrand() const;
    string getModel() const;
    string getLastRented() const;
    string getRentalLength() const;
    string getPrice() const;
    string isAvailable() const;

private:
    string fileName;
    string brand;
    string model;
    string lastRented;
    string rentalLength;
    string price;
    string available;

};//CarRental

CarRental::CarRental()
{
    brand = "null";
    model = "null";
    lastRented = "null";
    rentalLength = "null";
    price = "null";
    available = "null";
}//CarRental

void CarRental::rentCar()
{
    showInventory(); // Display the inventory

    string modelToRent;
    cout << "Enter the MODEL of the car you want to rent: ";
    cin >> modelToRent;

    ifstream inFile(getFileName());
    ofstream outFile("temp.txt");

    if (inFile.is_open() && outFile.is_open())
    {
        string brand, model, lastRented, rentalLength, price, available;

        while (inFile >> brand >> model >> lastRented >> rentalLength >> price >> available)
        {
            if (model == modelToRent)
            {
                if (available == "yes")
                {
                    cout << "Rent our " << model << " for how many days: ";
                    string days;
                    cin >> days;
                    cout << "\nTotal cost for renting our " << model << " for " << days << " days: $" << (stoi(price)) * (stoi(days)) << "." << endl;
                    // Car is available for rent
                    cout << "Car rented successfully!\n";

                    // Update availability to "0" (not available)
                    outFile << brand << " " << model << " " << lastRented << " " << rentalLength << " "
                            << price << " " << "no" << "\n";
                }
                else
                {
                    // Car is not available for rent
                    cout << "Car is not available for rent.\n";
                    outFile << brand << " " << model << " " << lastRented << " " << rentalLength << " "
                            << price << " " << available << "\n";
                }
            }
            else
            {
                // Write unchanged data to temp file
                outFile << brand << " " << model << " " << lastRented << " " << rentalLength << " "
                        << price << " " << available << "\n";
            }
        }

        inFile.close();
        outFile.close();

        // Rename temp file to the original file
        if (remove(fileName.c_str()) == 0 && rename("temp.txt", fileName.c_str()) == 0)
        {
            cout << "File updated successfully!\n";
        }
        else
        {
            cout << "Error updating file.\n";
        }
    }
    else
    {
        cout << "Error: Unable to open the file.\n";
    }
}//rentCar

void CarRental::returnCar()
{

}//returnCar

void CarRental::addCar()
{
    string input = "";
    cout << "Adding Car to Inventory" << endl;
    
    cout << "Car Brand: ";
    cin >> input;
    setBrand(input);

    cout << "Car Model: ";
    cin >> input;
    setModel(input);

    cout << "Rental Price per Day ($): ";
    cin >> input;
    setPrice(input);

    system("cls");
    cout << "Add new Car?\n" << endl << "Brand: " << getBrand() << endl << "Model: " << 
    getModel() << endl << "Price ($): " << getPrice() << endl << "\n('yes' / 'no') ";
    
    string validate = "";
    cin >> validate;

    if (validate == "yes") 
    {
        ofstream myFile;
        myFile.open(getFileName(), ios::app);

        if (myFile.is_open()) {
            myFile << getBrand() << " " << getModel() << " " << getLastRented() << " "
               << getRentalLength() << " " << getPrice() << " " << "yes" << "\n";

            myFile.close();
        } else {
            cout << "Error: Unable to open the file." << endl;
        }
    } 
    else 
    {
        cout << "Car NOT added to inventory." << endl;
    }
}//addCar

void CarRental::removeCar()
{

}//removeCar

void CarRental::showInventory()
{
    ifstream myFile;
    myFile.open(getFileName());
    if (myFile.is_open()) 
    {
        cout << "Inventory:\n";

        // Read and display each line from the file
        string brand, model, lastRented, rentalLength, price, available;
        while (myFile >> brand >> model >> lastRented >> rentalLength >> price >> available)
        {
            cout << "Brand: " << brand << "\n"
                 << "Model: " << model << "\n"
                 << "Last Rented: " << lastRented << "\n"
                 << "Rental Length: " << rentalLength << "\n"
                 << "Price: " << price << "\n"
                 << "Available: " << available << "\n\n";
        }
        myFile.close();
    } 
    else 
    {
        cout << "Error: Unable to open the file." << endl;
    }
}//showInventory

// Setters
void CarRental::setFileName(const string& name) { fileName = name; }
void CarRental::setBrand(const string& newBrand) { brand = newBrand; }
void CarRental::setModel(const string& newModel) { model = newModel; }
void CarRental::setLastRented(const string& newLastRented) { lastRented = newLastRented; }
void CarRental::setRentalLength(const string& newRentalLength) { rentalLength = newRentalLength; }
void CarRental::setPrice(const string& newPrice) { price = newPrice; }
void CarRental::setAvailable(const string& newAvailable) { available = newAvailable; }

// Getters
string CarRental::getFileName() const { return fileName; }
string CarRental::getBrand() const { return brand; }
string CarRental::getModel() const { return model; }
string CarRental::getLastRented() const { return lastRented; }
string CarRental::getRentalLength() const { return rentalLength; }
string CarRental::getPrice() const { return price; }
string CarRental::isAvailable() const { return available; }

int main()
{
    CarRental CR;
    ofstream myFile;
    string fileNameInput;
    cout << "Enter file name: ";
    cin >> fileNameInput;
    myFile.open(fileNameInput, ios::app);// open file in append mode

    if(myFile.is_open())
    {
        cout << "Success!" << endl;
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
        cout << "(1) Customer\n(2) Admin\n";
        cin >> input;
        if((input != "1") && (input != "2"))
        {
            cout << "Invalid input. Please enter '1' or '2'.\n";
        }
    } while(input != "1" && input != "2");
        
    system("cls");
    cout << "Logged in as: " << (input == "1" ? "Customer" : "Admin") << endl;
    
    string menu[] = {"Rent a Car", "Return a Car", "Show Inventory", "Add Car to System", "Remove Car from System"};
    
    input = "";
    do
    {
        for(int i = 0; i < size(menu); i++)
        {
            cout << "(" << i + 1 << ") " << menu[i] << endl;
        }
        cin >> input;
        if((input != "1") && (input != "2") && (input != "3") && (input != "4") && (input != "5"))
        {
            cout << "Invalid input. Please enter '1', '2', '3', '4', '5'.\n";
        }
    } while(input != "1" && input != "2" && input != "3" && input != "4" && input != "5");

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
    return 0;
}//main