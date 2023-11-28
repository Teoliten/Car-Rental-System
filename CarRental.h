#include <iostream>
#include <fstream>
#include <string>
#include <iterator> //size()
#include <cstdlib> // for system function
#include <random>//random token
#include <ctime>
#include <sstream>
#include <iomanip>

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
    string generateToken();

     // Setters
    void setUserName(const string& name);
    void setFileName(const string& name);
    void setBrand(const string& newBrand);
    void setModel(const string& newModel);
    void setLastRented(const string& newLastRented);
    void setRentalLength(const string& newRentalLength);
    void setPrice(const string& newPrice);
    void setAvailable(const string& newAvailable);
    
    // Getters
    string getUserName() const;
    string getFileName() const;
    string getBrand() const;
    string getModel() const;
    string getLastRented() const;
    string getRentalLength() const;
    string getPrice() const;
    string isAvailable() const;

private:
    string userName;
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
    cout << "Enter the MODEL of the car you want to RENT: ";
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
                    cout << "Your Name: ";
                    string name;
                    cin >> name;

                    system("cls");

                    // GET CURRENT DATE
                    // Get the current time
                    time_t currentTime = time(nullptr);
                
                    // Convert time_t to tm structure
                    tm* localTime = localtime(&currentTime);
                
                    // Format the date as "25/11/23"
                    ostringstream oss;
                    oss << setfill('0') << setw(2) << localTime->tm_mday << '/'
                        << setw(2) << localTime->tm_mon + 1 << '/'
                        << setw(2) << localTime->tm_year % 100;
                
                    // Convert the stringstream to a string
                    string today = oss.str();
                    // GET CURRENT DATE

                    cout << "\nTotal cost for renting our " << model << " for " << days << " days: $" << (stoi(price)) * (stoi(days)) << "." << endl;
                    cout << "Today's date: " << today << endl;

                    cout <<"\nRent car? ('yes' / 'no')\n>";

                    string validate = "";
                    cin >> validate;
                    system("cls");
                
                    if (validate == "yes") 
                    {
                        cout << "Car rented Successfully!\n";
                        cout << "Thank you " << name << "! See you in " << days << " days." << endl;
                
                        string randomToken = generateToken();
                        cout << "\nNOTICE!\n" << "Token: '" << randomToken << "'. Enter Token when Returning Car!" << endl;

                        ofstream myFile;
                        myFile.open("token.txt", ios::app);
                
                        if (myFile.is_open()) {
                            myFile << name  << " " << randomToken << " " << model << "\n";
                            myFile.close();
                        } else {
                            cout << "Error: Unable to open the file." << endl;
                        }
                    } 
                    else 
                    {
                        cout << "Car NOT rented." << endl;
                    }

                    // Update availability status to "no" in temp file
                    outFile << brand << " " << model << " " << today << " " << days << " "
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
            // cout << "File updated successfully!\n";
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
    cout << "Enter your Token to return Car:\n>";
    string token;
    cin >> token;
    system("cls");

    ifstream tokenFile("token.txt");
    ofstream tempTokenFile("temp_token.txt");
    bool validToken = false;
    string userName = "";
    string modelName = "";

    if (tokenFile.is_open() && tempTokenFile.is_open())
    {
        string name, storedToken, storedModel;

        while (tokenFile >> name >> storedToken >> storedModel)
        {
            if (storedToken == token)
            {
                validToken = true;
                userName = name;  // Store the user's name when a matching token is found
                modelName = storedModel;
            }
            else
            {
                // Write unchanged data to temp file
                tempTokenFile << name << " " << storedToken << " " << storedModel << "\n";
            }
        }

        tokenFile.close();
        tempTokenFile.close();

        // Remove the original token file
        remove("token.txt");

        // Rename temp file to the original token file
        if (rename("temp_token.txt", "token.txt") == 0)
        {
            // Continue with the logic to update the availability status in the inventory
            if (validToken)
            {
                cout << "Token is valid. " << modelName << " returned successfully!\n" << "Have a good day " << userName << "!\n" << endl;

                // Update availability status to "yes" in the inventory
                ofstream outFile("temp.txt");
                ifstream inFile(getFileName());

                if (inFile.is_open() && outFile.is_open())
                {
                    string brand, model, lastRented, rentalLength, price, available;

                    while (inFile >> brand >> model >> lastRented >> rentalLength >> price >> available)
                    {
                        if (storedToken == token && storedModel == model && available == "no")
                        {
                            // Update availability status to "yes" in temp file
                            outFile << brand << " " << model << " " << lastRented << " " << rentalLength << " "
                                    << price << " " << "yes" << "\n";       
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
                    if (remove(getFileName().c_str()) == 0 && rename("temp.txt", getFileName().c_str()) == 0)
                    {
                        // cout << "File updated successfully!\n";
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
            }
            else
            {
                cout << "Invalid token. Car cannot be returned.\n";
            }
        }
        else
        {
            cout << "Error updating token file.\n";
        }
    }
    else
    {
        cout << "Error: Unable to open the token file.\n";
    }
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
    getModel() << endl << "Price : $" << getPrice() << endl << "\n('yes' / 'no')\n>";
    
    string validate = "";
    cin >> validate;

    system("cls");

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
    showInventory(); // Display the inventory

    string modelToRemove;
    cout << "Enter the MODEL of the car you want to REMOVE: ";
    cin >> modelToRemove;

    ifstream inFile(getFileName());
    ofstream outFile("temp.txt");

    if (inFile.is_open() && outFile.is_open())
    {
        string brand, model, lastRented, rentalLength, price, available;

        while (inFile >> brand >> model >> lastRented >> rentalLength >> price >> available)
        {
            if (model == modelToRemove)
            {
                system("cls");

                // GET CURRENT DATE
                // Get the current time
                time_t currentTime = time(nullptr);

                // Convert time_t to tm structure
                tm* localTime = localtime(&currentTime);

                // Format the date as "25/11/23"
                ostringstream oss;
                oss << setfill('0') << setw(2) << localTime->tm_mday << '/'
                    << setw(2) << localTime->tm_mon + 1 << '/'
                    << setw(2) << localTime->tm_year % 100;

                // Convert the stringstream to a string
                string today = oss.str();
                // GET CURRENT DATE

                cout << "\nRemove " << modelToRemove << "? ('yes' / 'no')\n>";
                string validate = "";
                cin >> validate;

                if (validate == "yes")
                {
                    cout << "Car removed Successfully!\n";
                    continue; // Skip writing the line to temp file
                }
                else
                {
                    cout << "Car NOT removed." << endl;
                    outFile << brand << " " << model << " " << lastRented << " " << rentalLength << " "
                            << price << " " << available << "\n";
                    break; // Exit the loop, as the car is not removed
                }
            }
            else
            {
                // Write unchanged data to temp file
                outFile << brand << " " << model << " " << lastRented << " " << rentalLength << " "
                        << price << " " << available << "\n";
            }
        }

        // Continue processing the remaining lines
        while (inFile >> brand >> model >> lastRented >> rentalLength >> price >> available)
        {
            // Write unchanged data to temp file
            outFile << brand << " " << model << " " << lastRented << " " << rentalLength << " "
                    << price << " " << available << "\n";
        }

        inFile.close();
        outFile.close();

        // Rename temp file to the original file
        if (remove(fileName.c_str()) == 0 && rename("temp.txt", fileName.c_str()) == 0)
        {
            // cout << "File updated successfully!\n";
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
}//removeCar

void CarRental::showInventory()
{
    ifstream myFile;
    myFile.open(getFileName());
    if (myFile.is_open()) 
    {
        cout << "Inventory:\n\n";
        string brand, model, lastRented, rentalLength, price, available;
        
        while (myFile >> brand >> model >> lastRented >> rentalLength >> price >> available)
        {
            if(available == "yes" || getUserName() == "Admin")
            {
                cout << "Brand: " << brand << "\n"
                << "Model: " << model << "\n"
                << "Price: $" << price << "\n";
                if(getUserName() == "Admin")
                {
                    cout << "Last Rented: " << lastRented << "\n"
                    << "Rental Length: " << rentalLength << "\n"
                    << "Available: " << available << "\n";
                }
                cout << "\n";
            }
            
        }
        myFile.close();
    } 
    else 
    {
        cout << "Error: Unable to open the file." << endl;
    }
}//showInventory

string CarRental::generateToken() {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int length = 5;

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, characters.size() - 1);

    string token;
    for (int i = 0; i < length; ++i) {
        token += characters[distribution(generator)];
    }

    return token;
}//generateToken

// Setters
void CarRental::setUserName(const string& name) { userName = name; }
void CarRental::setFileName(const string& name) { fileName = name; }
void CarRental::setBrand(const string& newBrand) { brand = newBrand; }
void CarRental::setModel(const string& newModel) { model = newModel; }
void CarRental::setLastRented(const string& newLastRented) { lastRented = newLastRented; }
void CarRental::setRentalLength(const string& newRentalLength) { rentalLength = newRentalLength; }
void CarRental::setPrice(const string& newPrice) { price = newPrice; }
void CarRental::setAvailable(const string& newAvailable) { available = newAvailable; }

// Getters
string CarRental::getUserName() const { return userName; }
string CarRental::getFileName() const { return fileName; }
string CarRental::getBrand() const { return brand; }
string CarRental::getModel() const { return model; }
string CarRental::getLastRented() const { return lastRented; }
string CarRental::getRentalLength() const { return rentalLength; }
string CarRental::getPrice() const { return price; }
string CarRental::isAvailable() const { return available; }