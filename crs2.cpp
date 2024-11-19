#include <iostream>
#include <stack>
using namespace std;
struct Info
{
    string make;
    string model;
    string licensePlate;
    int year;
    double rentalRate;
    bool reserved;
    bool rented;
};

struct node
{
    Info data;
    node *next;
    node *prev;
};
node *head = NULL;
stack<Info> RentedVehicles;

class carRentalSystem
{
private:
public:
    void addAVehicle();
    void viewVehicles();
    void deleteVehicle();
    void searchVehicle();
    void rentAVehicle();
    void viewRentedVehicles();
    void reserveAVehicle();
    bool checkAvailability(string);
};

void carRentalSystem::addAVehicle()
{
    Info carData;
    cout << "Enter License Plate:";
    cin >> carData.licensePlate;
    cout << "Enter car make:";
    cin >> carData.make;
    cout << "Enter car model:";
    cin >> carData.model;
    cout << "Enter car year:";
    cin >> carData.year;
    cout << "Enter it's rental rate:";
    cin >> carData.rentalRate;
    carData.rented = false;
    carData.reserved = false;

    node *newCar = new node;
    newCar->data = carData;
    newCar->next = NULL;
    newCar->prev = NULL;

    if (head == NULL)
    {
        head = newCar;
        cout << "Car information added." << endl;
    }
    else
    {
        node *curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }

        curr->next = newCar;
        newCar->prev = curr;
        newCar->next = NULL;
        cout << "Car information added." << endl;
    }
}
void carRentalSystem::viewVehicles()
{
    int choice;
    cout << "1. View all vehicles" << endl;
    cout << "2. View vehicles in increasing order of rental price" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        node *curr = head;
        while (curr != NULL)
        {
            cout << "-------------------------" << endl;
            cout << "License Plate: " << curr->data.licensePlate << endl;
            cout << "Make: " << curr->data.make << endl;
            cout << "Model: " << curr->data.model << endl;
            cout << "Year: " << curr->data.year << endl;
            cout << "Rent Rate: " << curr->data.rentalRate << endl;
            if (curr->data.rented == false)
            {
                cout << "Vehicle is available." << endl;
            }
            else
            {
                cout << "Vehicle is not available." << endl;
            }
            curr = curr->next;
        }
        break;
    }
    case 2:
    {
        // Bubble sort algorithm to sort vehicles in increasing order of rental price
        node *curr = head;
        int count = 0;
        while (curr != NULL)
        {
            curr = curr->next;
            count++;
        }

        for (int i = 0; i < count - 1; i++)
        {
            curr = head;
            for (int j = 0; j < count - i - 1; j++)
            {
                if (curr->data.rentalRate > curr->next->data.rentalRate)
                {
                    Info temp = curr->data;
                    curr->data = curr->next->data;
                    curr->next->data = temp;
                }
                curr = curr->next;
            }
        }

        // Display the sorted vehicles
        cout << "Viewing vehicles in increasing order of rental price..." << endl;
        curr = head;
        while (curr != NULL)
        {
            cout << "-------------------------" << endl;
            cout << "License Plate: " << curr->data.licensePlate << endl;
            cout << "Make: " << curr->data.make << endl;
            cout << "Model: " << curr->data.model << endl;
            cout << "Year: " << curr->data.year << endl;
            cout << "Rent Rate: " << curr->data.rentalRate << endl;
            if (curr->data.rented == false)
            {
                cout << "Vehicle is available." << endl;
            }
            else
            {
                cout << "Vehicle is not available." << endl;
            }
            curr = curr->next;
        }
        break;
    }
    default:
        cout << "Invalid choice." << endl;
    }
}
void carRentalSystem::deleteVehicle()
{
    string licensePlate;
    cout << "Enter the license plate of the vehicle you want to delete: ";
    cin >> licensePlate;

    node *curr = head;
    node *prev = NULL;

    while (curr != NULL)
    {
        if (curr->data.licensePlate == licensePlate)
        {
            if (prev == NULL)
            {
                head = curr->next;
            }
            else
            {
                prev->next = curr->next;
                if (curr->next != NULL)
                {
                    curr->next->prev = prev;
                }
            }
            delete curr;
            cout << "Vehicle with license plate " << licensePlate << " has been deleted." << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Vehicle with license plate " << licensePlate << " not found." << endl;
}

void carRentalSystem::searchVehicle()
{
    string licensePlate;
    cout << "Enter the license plate of the vehicle you want to search: ";
    cin >> licensePlate;

    node *curr = head;
    while (curr != NULL)
    {
        if (curr->data.licensePlate == licensePlate)
        {
            cout << "-------------------------" << endl;
            cout << "License Plate: " << curr->data.licensePlate << endl;
            cout << "Make: " << curr->data.make << endl;
            cout << "Model: " << curr->data.model << endl;
            cout << "Year: " << curr->data.year << endl;
            cout << "Rent Rate: " << curr->data.rentalRate << endl;
            if (curr->data.rented == false)
            {
                cout << "Vehicle is available." << endl;
            }
            else
            {
                cout << "Vehicle is not available." << endl;
            }
            return;
        }
        curr = curr->next;
    }

    cout << "Vehicle with license plate " << licensePlate << " not found." << endl;
}

void carRentalSystem::rentAVehicle()
{
    string licensePlate;
    int days;
    double price;

    cout << "Enter the license plate of the car to rent out: ";
    cin >> licensePlate;

    node *curr = head;

    while (curr != NULL)
    {
        if (curr->data.licensePlate == licensePlate)
        {
            if (curr->data.rented == true)
            {
                cout << "Vehicle is already rented." << endl;
                return;
            }
            else if (curr->data.reserved == true)
            {
                cout << "Vehicle is reserved. It cannot be rented." << endl;
                return;
            }
            else
            {
                curr->data.rented = true;
                cout << "Enter the number of days you want to rent the car for: ";
                cin >> days;

                price = days * curr->data.rentalRate;

                cout << "Vehicle with License Plate " << licensePlate << " has been rented for: " << price << "$" << endl;
                RentedVehicles.push(curr->data);
                return;
            }
        }
        curr = curr->next;
    }

    cout << "Vehicle with License Plate " << licensePlate << " not found." << endl;
}

void carRentalSystem::reserveAVehicle()
{
    string licensePlate;
    string reservationDate;

    cout << "Enter the license plate of the vehicle to reserve: ";
    cin >> licensePlate;

    node *curr = head;

    while (curr != NULL)
    {
        if (curr->data.licensePlate == licensePlate)
        {
            if (curr->data.rented == true)
            {
                cout << "Vehicle is already rented. It cannot be reserved." << endl;
                return;
            }
            else if (curr->data.reserved == true)
            {
                cout << "Vehicle is already reserved." << endl;
                return;
            }
            else
            {
                cout << "Enter the date of reservation (YYYY-MM-DD): ";
                cin >> reservationDate;

                curr->data.reserved = true;
                cout << "Vehicle with License Plate " << licensePlate << " has been reserved for " << reservationDate << "." << endl;
                return;
            }
        }
        curr = curr->next;
    }

    cout << "Vehicle with License Plate " << licensePlate << " not found." << endl;
}
bool carRentalSystem::checkAvailability(string licensePlate)
{
    node *curr = head;

    while (curr != NULL)
    {
        if (curr->data.licensePlate == licensePlate)
        {
            if (curr->data.rented == true || curr->data.reserved == true)
            {
                return false; // Vehicle is not available
            }
            else
            {
                return true; // Vehicle is available
            }
        }
        curr = curr->next;
    }

    return false; // Vehicle not found
}
void carRentalSystem::viewRentedVehicles()
{
    if (RentedVehicles.empty())
    {
        cout << "No vehicles are currently rented." << endl;
        return;
    }

    stack<Info> tempStack = RentedVehicles;

    cout << "Rented Vehicles:" << endl;

    while (!tempStack.empty())
    {
        Info rental = tempStack.top();
        tempStack.pop();

        cout << "-------------------------" << endl;
        cout << "License Plate: " << rental.licensePlate << endl;
        cout << "Make: " << rental.make << endl;
        cout << "Model: " << rental.model << endl;
        cout << "Year: " << rental.year << endl;
        cout << "Rental Rate: " << rental.rentalRate << endl;
    }
}

int main()
{
    carRentalSystem rentalSystem;
    int choice;

    do
    {
        cout << "-------------------------" << endl;
        cout << "Car Rental System" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Add a Vehicle" << endl;
        cout << "2. View Vehicles" << endl;
        cout << "3. Delete a Vehicle" << endl;
        cout << "4. Search for a Vehicle" << endl;
        cout << "5. Rent a Vehicle" << endl;
        cout << "6. View Rented Vehicles" << endl;
        cout << "7. Reserve a Vehicle" << endl;
        cout << "8. Check Vehicle Availability" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            rentalSystem.addAVehicle();
            break;
        case 2:
            rentalSystem.viewVehicles();
            break;
        case 3:
            rentalSystem.deleteVehicle();
            break;
        case 4:
            rentalSystem.searchVehicle();
            break;
        case 5:
            rentalSystem.rentAVehicle();
            break;
        case 6:
            rentalSystem.viewRentedVehicles();
            break;
        case 7:
            rentalSystem.reserveAVehicle();
            break;
        case 8:
        {
            string licensePlate;
            cout << "Enter the license plate of the vehicle: ";
            cin >> licensePlate;
            bool availability = rentalSystem.checkAvailability(licensePlate);
            if (availability)
                cout << "The vehicle is available for rent." << endl;
            else
                cout << "The vehicle is not available for rent." << endl;
            break;
        }
        case 9:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}