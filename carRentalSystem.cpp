#include <iostream>
#include <queue>

using namespace std;

class Info
{
public:
    string make;
    string model;
    int year;
    double rentalRate;
    bool rented;
};

class nodes
{
public:
    Info data;
    nodes *leftChild;
    nodes *rightChild;
};

nodes *rootPtr = nullptr;

class carRentalSystem
{
public:
    void addVehicle(string make, string model, int year, double rentalRate);
    void displayAvailableVehicles(nodes *root);
    bool isVehicleAvailable(nodes *root, string make, string model, int year);
    void reserveVehicle(queue<Info> &reservations, string make, string model, int year);

private:
    void insertNode(nodes *&root, nodes *newNode);
    nodes *searchNode(nodes *root, string make, string model, int year);
};

void carRentalSystem::addVehicle(string make, string model, int year, double rentalRate)
{
    nodes *newNode = new nodes;
    newNode->data.make = make;
    newNode->data.model = model;
    newNode->data.year = year;
    newNode->data.rentalRate = rentalRate;
    newNode->data.rented = false; // Assuming newly added vehicles are not rented
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;

    insertNode(rootPtr, newNode);
}

void carRentalSystem::displayAvailableVehicles(nodes *root)
{
    if (root != nullptr)
    {
        displayAvailableVehicles(root->leftChild);
        if (!root->data.rented)
        {
            cout << root->data.make << " " << root->data.model << " (" << root->data.year << ")\n";
        }
        displayAvailableVehicles(root->rightChild);
    }
}

bool carRentalSystem::isVehicleAvailable(nodes *root, string make, string model, int year)
{
    nodes *foundNode = searchNode(root, make, model, year);
    return (foundNode != nullptr && !foundNode->data.rented);
}

void carRentalSystem::reserveVehicle(queue<Info> &reservations, string make, string model, int year)
{
    nodes *foundNode = searchNode(rootPtr, make, model, year);
    if (foundNode != nullptr && !foundNode->data.rented)
    {
        foundNode->data.rented = true;
        reservations.push(foundNode->data);
        cout << "Vehicle reserved successfully!\n";
    }
    else
    {
        cout << "Vehicle not available for reservation.\n";
    }
}

void carRentalSystem::insertNode(nodes *&root, nodes *newNode)
{
    if (root == nullptr)
    {
        root = newNode;
    }
    else
    {
        if (newNode->data.year < root->data.year)
        {
            insertNode(root->leftChild, newNode);
        }
        else
        {
            insertNode(root->rightChild, newNode);
        }
    }
}

nodes *carRentalSystem::searchNode(nodes *root, string make, string model, int year)
{
    if (root == nullptr || (root->data.make == make && root->data.model == model && root->data.year == year))
    {
        return root;
    }

    if (year < root->data.year)
    {
        return searchNode(root->leftChild, make, model, year);
    }
    else
    {
        return searchNode(root->rightChild, make, model, year);
    }
}

int main()
{
    carRentalSystem rentalSystem;

    // Example: Adding vehicles to the system
    rentalSystem.addVehicle("Toyota", "Camry", 2020, 50.0);
    rentalSystem.addVehicle("Honda", "Accord", 2019, 55.0);
    rentalSystem.addVehicle("Ford", "Explorer", 2022, 60.0);

    // Example: Displaying available vehicles
    cout << "Available Vehicles:\n";
    rentalSystem.displayAvailableVehicles(rootPtr);

    // Example: Reserving a vehicle
    queue<Info> reservations;
    rentalSystem.reserveVehicle(reservations, "Toyota", "Camry", 2020);

    return 0;
}