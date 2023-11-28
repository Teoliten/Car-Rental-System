# Car Rental System
## Introduction
The Car Rental System is a simple console-based application written in C++ that simulates a car rental service. It allows users to rent and return cars, view the inventory, add new cars to the system, and remove cars from the system. The system distinguishes between customers and administrators, each with different functionalities.

## Data Storage
The application simulates a basic database using two text files:

- `token.txt`: Stores customer information, including names, unique tokens generated during rentals, and the model of the rented car.
```
Mason MXPLG 911
Sophia mlHL9 Veyron
Mark 6Zcwp P1
```
In the format `NAME`, `TOKEN`, `MODEL`.

- `inventory_1.txt`: Acts as the inventory database, storing details about each car, such as brand, model, last rented date, rental length, price, and availability status.
```
Ferrari 488_GTB 28/11/23 10 1500 yes
Lamborghini Huracan 28/11/23 2 2000 yes
Bugatti Veyron 28/11/23 2 5000 no
McLaren P1 28/11/23 5 2500 no
Porsche 911 28/11/23 4 1000 no
Aston_Martin DBS_Superleggera 27/11/23 47 1800 yes
Skoda Octavia 28/11/23 2 50 yes
```
In the format `BRAND`, `MODEL`, `LastRented`, `RentDuration`, `PRICE($)`, `AVAILABILITY`.

## Features
### 1. Rent a Car:
- Customers can rent available cars for a specified number of days.
- Generates a unique token for the rental, which must be provided during the return process.

### 2. Return a Car:
- Customers can return cars by providing the token generated during the rental.
- Updates the availability status of the returned car in the inventory.

### 3. Show Inventory:
- Displays the current inventory of cars, including brand, model, and price.
- Administrators can view additional details such as the last rented date, rental length, and availability status.

### 4. Add Car to System (Admin function):
- Administrators can add new cars to the inventory, providing details such as brand, model, and rental price per day.

### 5. Remove Car from System (Admin function):
- Administrators can remove cars from the inventory based on the model.

## Usage
- Sign in as a customer or administrator.
- Follow the on-screen menu to perform actions such as renting, returning, viewing inventory, adding, or removing cars.
- Exit the program by entering 'exit' at any menu prompt.

## Example 
Example signing in as Customer and Renting a car, and Returning a Car.

### Output
```
Sign in
(1) Customer
(2) Admin
```
### Input
```
1
```
----------
### Output
```
Logged in as: Customer
(1) Rent a Car
(2) Return a Car
(3) Show Inventory
```
### Input
```
1
```
----------
### Output
```
Inventory:

Brand: Ferrari
Model: 488_GTB
Price: $1500

Brand: Aston_Martin
Model: DBS_Superleggera
Price: $1800

Brand: Skoda
Model: Octavia
Price: $50

Enter the MODEL of the car you want to RENT:
```
### Input
```
Octavia
```
----------
### Output
```
Rent our Octavia for how many days:
```
### Input
```
4
```
----------
### Output
```
Your Name:
```
### Input
```
Elon
```
----------
### Output
```
Total cost for renting our Octavia for 4 days: $200.
Today's date: 28/11/23

Rent car? ('yes' / 'no')
>
```
### Input
```
yes
```
----------
### Output
```
Car rented Successfully!
Thank you Elon! See you in 4 days.

NOTICE!
Token: 'q8Bpd'. Enter Token when Returning Car!
```
----------
`token.txt`
```
Mason MXPLG 911
Sophia mlHL9 Veyron
Mark 6Zcwp P1
Elon q8Bpd Octavia //This line added to 'token.txt', storing 'Name', unique 'Token' and 'Model' rented.
```
`inventory_1.txt`
```
Ferrari 488_GTB 28/11/23 10 1500 yes
Bugatti Veyron 28/11/23 2 5000 no
McLaren P1 28/11/23 5 2500 no
Aston_Martin DBS_Superleggera 27/11/23 47 1800 yes
Skoda Octavia 28/11/23 4 50 no //Availability changes to 'no', updated LastRented and RentLength.
Porsche 911 28/11/23 4 1000 no
```