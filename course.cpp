#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib> // for randomization

class Room {
public:
    std::string guestName;
    std::string guestAddress;
    std::string guestPhone;
    int numberOfDays;
    double roomRate;
    double parkingCharges;
    bool isBooked;
    int roomNumber;

    Room* left;
    Room* right;

    Room(int number) : roomNumber(number), isBooked(false), parkingCharges(0.0), left(nullptr), right(nullptr) {}

    void bookRoom(const std::string& name, const std::string& address, const std::string& phone, int days, double rate) {
        guestName = name;
        guestAddress = address;
        guestPhone = phone;
        numberOfDays = days;
        roomRate = rate;
        isBooked = true;
    }

    void displayRoomDetails() const {
        if (isBooked) {
            std::cout << "Room Number: " << roomNumber << "\n";
            std::cout << "Guest Name: " << guestName << "\n";
            std::cout << "Address: " << guestAddress << "\n";
            std::cout << "Phone Number: " << guestPhone << "\n";
            std::cout << "Number of Days: " << numberOfDays << "\n";
            std::cout << "Room Rate: $" << roomRate << " per day\n";
            std::cout << "Parking Charges: $" << parkingCharges << " per day\n";
            std::cout << "Total Room Charges: $" << roomRate * numberOfDays << "\n";
            std::cout << "Total Charges (Including Parking): $" << getTotalCharges() << "\n";
        } else {
            std::cout << "Room Number: " << roomNumber << " (Vacant)\n";
        }
    }

    double getTotalCharges() const {
        return (roomRate * numberOfDays) + (parkingCharges * numberOfDays);
    }

    void checkOut() {
        isBooked = false;
        guestName = "";
        guestAddress = "";
        guestPhone = "";
        numberOfDays = 0;
        roomRate = 0.0;
        parkingCharges = 0.0;
    }

    void setParkingCharges(double charges) {
        parkingCharges = charges;
    }

    bool isBookedRoom() const {
        return isBooked;
    }
};

class HotelManager {
private:
    Room* root; // Binary tree root for hierarchical room organization
    std::map<int, Room*> roomNumberToRoom; // Mapping from room numbers to room objects

    // Graph structure for room connections
    std::unordered_map<int, std::vector<int>> roomConnections;

    std::set<std::string> housekeepingStaff = {
        "Damodar", "Rohan", "Deepak", "Ranveer", "Parminder",
        "Linda", "Rajendra", "Susan", "Tanisha", "Kara",
        "Soham", "Ramesh", "Richard", "Shiva", "Sushant",
        "Riya", "Rajesh", "Nancy", "Irfan", "Kapil"
    };

public:
    HotelManager(int numRooms) : root(nullptr) {
        for (int i = 1; i <= numRooms; ++i) {
            Room* room = new Room(i);
            roomNumberToRoom[i] = room;
            root = insertIntoBinaryTree(root, room);
        }

        // Set up room connections (you can customize this based on your hotel layout)
        addRoomConnection(1, 2);
        addRoomConnection(2, 3);
        addRoomConnection(4, 5);
        addRoomConnection(6, 7);
    }

    // Insert a room into the binary tree
    Room* insertIntoBinaryTree(Room* current, Room* room) {
        if (current == nullptr) {
            return room;
        }

        if (room->roomNumber < current->roomNumber) {
            current->left = insertIntoBinaryTree(current->left, room);
        } else if (room->roomNumber > current->roomNumber) {
            current->right = insertIntoBinaryTree(current->right, room);
        }

        return current;
    }

    // Add a connection between two rooms
    void addRoomConnection(int room1, int room2) {
        roomConnections[room1].push_back(room2);
        roomConnections[room2].push_back(room1);
    }

    void displayWelcomeLogo() {
        std::cout << "Welcome to XYZ Hotel Management System\n";
    }

    bool authenticate() {
        std::string username;
        std::string password;
        std::cout << "Please log in to continue.\n";
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
        return username == "admin" && password == "password";
    }

    void displayMainMenu() {
        int choice;
        while (true) {
            std::cout << "\n\t\t*************\n";
            std::cout << "\t\t* MAIN MENU *\n";
            std::cout << "\t\t*************\n";
            std::cout << "1. Book A Room\n";
            std::cout << "2. Customer Records\n";
            std::cout << "3. Rooms Allotted\n";
            std::cout << "4. Check Out\n";
            std::cout << "5. Set Parking Charges\n";
            std::cout << "6. Display Room Connections\n";
            std::cout << "7. Exit\n";
            std::cout << "Enter Your Choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    bookRoom();
                    break;
                case 2:
                    displayCustomerRecords();
                    break;
                case 3:
                    displayAllottedRooms();
                    break;
                case 4:
                    checkOutRoom();
                    break;
                case 5:
                    setParkingCharges();
                    break;
                case 6:
                    displayRoomConnections();
                    break;
                case 7:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void bookRoom() {
        int roomNumber;
        std::cout << "Enter Room Number: ";
        std::cin >> roomNumber;

        if (roomNumberToRoom.find(roomNumber) == roomNumberToRoom.end()) {
            std::cout << "Invalid room number. Please enter a valid room number.\n";
            return;
        }

        Room* room = roomNumberToRoom[roomNumber];
        if (room->isBookedRoom()) {
            std::cout << "Sorry, the room is already booked.\n";
        } else {
            std::string name, address, phone;
            int days;
            double rate;

            std::cout << "Enter Guest Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter Guest Address: ";
            std::getline(std::cin, address);

            std::cout << "Enter Guest Phone Number: ";
            std::cin >> phone;

            std::cout << "Enter Number of Days to Stay: ";
            std::cin >> days;

            std::cout << "Enter Room Rate per Day: $";
            std::cin >> rate;

            // Book the room
            room->bookRoom(name, address, phone, days, rate);

            // Assign a housekeeping staff member
            std::string staffName = assignHousekeepingStaff();

            std::cout << "Room booked successfully!\n";
            std::cout << "Staff assigned for your assistance: " << staffName << "\n";

            generateReceipt(*room, name, roomNumber);
        }
    }

    std::string assignHousekeepingStaff() {
        // Randomly select a staff member from the set
        int randIndex = rand() % housekeepingStaff.size();
        auto it = housekeepingStaff.begin();
        std::advance(it, randIndex);
        std::string staffName = *it;

        // Remove the assigned staff member from the set to avoid double assignment
        housekeepingStaff.erase(staffName);

        return staffName;
    }

    void displayCustomerRecords() {
        int roomNumber;
        std::cout << "Enter Room Number: ";
        std::cin >> roomNumber;

        if (roomNumberToRoom.find(roomNumber) == roomNumberToRoom.end()) {
            std::cout << "Invalid room number. Please enter a valid room number.\n";
            return;
        }

        Room* room = roomNumberToRoom[roomNumber];
        if (room->isBookedRoom()) {
            std::cout << "\nCustomer Details\n";
            std::cout << "----------------\n";
            room->displayRoomDetails();
        } else {
            std::cout << "The room is vacant.\n";
        }
    }

    void displayAllottedRooms() {
        std::cout << "\nList Of Rooms Allotted\n";
        std::cout << "-----------------------\n";

        inOrderTraversal(root);

        std::cout << "************************\n";
    }

    void inOrderTraversal(Room* current) {
        if (current) {
            inOrderTraversal(current->left);
            if (current->isBookedRoom()) {
                current->displayRoomDetails();
            }
            inOrderTraversal(current->right);
        }
    }

    void checkOutRoom() {
        int roomNumber;
        std::cout << "Enter Room Number: ";
        std::cin >> roomNumber;

        if (roomNumberToRoom.find(roomNumber) == roomNumberToRoom.end()) {
            std::cout << "Invalid room number. Please enter a valid room number.\n";
            return;
        }

        Room* room = roomNumberToRoom[roomNumber];
        if (room->isBookedRoom()) {
            room->checkOut();
            std::cout << "Check-out completed.\n";
        } else {
            std::cout << "The room is already vacant.\n";
        }
    }

    void setParkingCharges() {
        double charges;
        std::cout << "Enter Parking Charges per Day: $";
        std::cin >> charges;

        for (const auto& entry : roomNumberToRoom) {
            Room* room = entry.second;
            room->setParkingCharges(charges);
        }
        std::cout << "Parking charges set for all rooms.\n";
    }

    void displayRoomConnections() {
        std::cout << "\nRoom Connections\n";
        std::cout << "----------------\n";

        for (const auto& entry : roomConnections) {
            int roomNumber = entry.first;
            const std::vector<int>& connectedRooms = entry.second;

            std::cout << "Room " << roomNumber << " is connected to rooms: ";
            for (int connectedRoom : connectedRooms) {
                std::cout << connectedRoom << " ";
            }
            std::cout << "\n";
        }
    }

    void generateReceipt(const Room& room, const std::string& guestName, int roomNumber) {
        std::ofstream receiptFile;
        std::time_t currentTime = std::time(nullptr);
        std::tm localTime = *std::localtime(&currentTime);
        std::string receiptFileName = "Receipt_" + std::to_string(roomNumber) + "_" +
            std::to_string(localTime.tm_year + 1900) +
            std::to_string(localTime.tm_mon + 1) +
            std::to_string(localTime.tm_mday) +
            std::to_string(localTime.tm_hour) +
            std::to_string(localTime.tm_min) +
            std::to_string(localTime.tm_sec) + ".txt";

        receiptFile.open(receiptFileName);
        receiptFile << "Receipt for Room Number: " << roomNumber << "\n";
        receiptFile << "Guest Name: " << guestName << "\n";
        receiptFile << "Check-in Date: " << localTime.tm_year + 1900 << "-" << localTime.tm_mon + 1 << "-" << localTime.tm_mday << "\n";
        receiptFile << "Number of Days: " << room.numberOfDays << "\n";
        receiptFile << "Room Rate per Day: $" << room.roomRate << "\n";
        receiptFile << "Parking Charges per Day: $" << room.parkingCharges << "\n";
        receiptFile << "Total Room Charges: $" << room.roomRate * room.numberOfDays << "\n";
        receiptFile << "Total Parking Charges: $" << room.parkingCharges * room.numberOfDays << "\n";
        receiptFile << "Total Charges: $" << room.getTotalCharges() << "\n";
        receiptFile.close();

        std::cout << "Receipt generated and saved as " << receiptFileName << "\n";
    }
};

int main() {
    HotelManager manager(100); // Initialize with 100 rooms.

    manager.displayWelcomeLogo();

    if (manager.authenticate()) {
        manager.displayMainMenu();
    } else {
        std::cout << "Authentication failed. Exiting...\n";
    }

    return 0;
}
