#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==================== RIDE CLASS (BASE CLASS) ====================
// Demonstrates: Encapsulation and Inheritance
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;
    double baseFarePerMile;

public:
    // Constructor
    Ride(int id, string pickup, string dropoff, double dist) 
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), 
          distance(dist), baseFarePerMile(2.5) {}
    
    // Virtual destructor for proper cleanup
    virtual ~Ride() {}
    
    // Virtual method for polymorphism
    virtual double fare() const {
        return distance * baseFarePerMile;
    }
    
    // Display ride details
    virtual void rideDetails() const {
        cout << "Ride ID: " << rideID << endl;
        cout << "Pickup: " << pickupLocation << endl;
        cout << "Dropoff: " << dropoffLocation << endl;
        cout << "Distance: " << distance << " miles" << endl;
        cout << "Fare: $" << fixed << setprecision(2) << fare() << endl;
    }
    
    // Getters (Encapsulation)
    int getRideID() const { return rideID; }
    string getPickupLocation() const { return pickupLocation; }
    string getDropoffLocation() const { return dropoffLocation; }
    double getDistance() const { return distance; }
    
    // Virtual method to get ride type
    virtual string getRideType() const { return "Standard"; }
};

// ==================== STANDARD RIDE CLASS ====================
// Demonstrates: Inheritance and Polymorphism
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {
        baseFarePerMile = 2.5;
    }
    
    double fare() const override {
        double baseFare = distance * baseFarePerMile;
        double bookingFee = 1.5;
        return baseFare + bookingFee;
    }
    
    void rideDetails() const override {
        cout << "\n--- STANDARD RIDE ---" << endl;
        Ride::rideDetails();
    }
    
    string getRideType() const override { return "Standard"; }
};

// ==================== PREMIUM RIDE CLASS ====================
// Demonstrates: Inheritance and Polymorphism
class PremiumRide : public Ride {
private:
    bool luxuryVehicle;
    
public:
    PremiumRide(int id, string pickup, string dropoff, double dist, bool luxury = true)
        : Ride(id, pickup, dropoff, dist), luxuryVehicle(luxury) {
        baseFarePerMile = 4.0;
    }
    
    double fare() const override {
        double baseFare = distance * baseFarePerMile;
        double premiumSurcharge = 5.0;
        double luxuryBonus = luxuryVehicle ? 10.0 : 0.0;
        return baseFare + premiumSurcharge + luxuryBonus;
    }
    
    void rideDetails() const override {
        cout << "\n--- PREMIUM RIDE ---" << endl;
        Ride::rideDetails();
        cout << "Luxury Vehicle: " << (luxuryVehicle ? "Yes" : "No") << endl;
    }
    
    string getRideType() const override { return "Premium"; }
};

// ==================== SHARED RIDE CLASS ====================
// Demonstrates: Inheritance and Polymorphism (Additional Feature)
class SharedRide : public Ride {
private:
    int numberOfPassengers;
    
public:
    SharedRide(int id, string pickup, string dropoff, double dist, int passengers)
        : Ride(id, pickup, dropoff, dist), numberOfPassengers(passengers) {
        baseFarePerMile = 1.5;
    }
    
    double fare() const override {
        double baseFare = distance * baseFarePerMile;
        double discountRate = 0.70; // 30% discount for sharing
        return baseFare * discountRate;
    }
    
    void rideDetails() const override {
        cout << "\n--- SHARED RIDE ---" << endl;
        Ride::rideDetails();
        cout << "Number of Passengers: " << numberOfPassengers << endl;
        cout << "Discount Applied: 30%" << endl;
    }
    
    string getRideType() const override { return "Shared"; }
};

// ==================== DRIVER CLASS ====================
// Demonstrates: Encapsulation
class Driver {
private:
    int driverID;
    string name;
    double rating;
    vector<Ride*> assignedRides;  // Private member (Encapsulation)
    
public:
    Driver(int id, string driverName, double rate)
        : driverID(id), name(driverName), rating(rate) {}
    
    // Add ride to driver's list (Encapsulation through method)
    void addRide(Ride* ride) {
        assignedRides.push_back(ride);
        cout << "\nRide #" << ride->getRideID() << " assigned to " << name << endl;
    }
    
    // Display driver information
    void getDriverInfo() const {
        cout << "\n========== DRIVER INFORMATION ==========" << endl;
        cout << "Driver ID: " << driverID << endl;
        cout << "Name: " << name << endl;
        cout << "Rating: " << rating << " stars" << endl;
        cout << "Total Rides Completed: " << assignedRides.size() << endl;
        
        if (!assignedRides.empty()) {
            cout << "\nCompleted Rides:" << endl;
            double totalEarnings = 0.0;
            for (const auto& ride : assignedRides) {
                cout << "  - Ride #" << ride->getRideID() 
                     << " (" << ride->getRideType() << "): $" 
                     << fixed << setprecision(2) << ride->fare() << endl;
                totalEarnings += ride->fare();
            }
            cout << "Total Earnings: $" << fixed << setprecision(2) << totalEarnings << endl;
        }
        cout << "========================================" << endl;
    }
    
    // Getters
    int getDriverID() const { return driverID; }
    string getName() const { return name; }
    double getRating() const { return rating; }
    int getRideCount() const { return assignedRides.size(); }
};

// ==================== RIDER CLASS ====================
// Demonstrates: Encapsulation
class Rider {
private:
    int riderID;
    string name;
    vector<Ride*> requestedRides;  // Private member (Encapsulation)
    
public:
    Rider(int id, string riderName)
        : riderID(id), name(riderName) {}
    
    // Request a ride (Encapsulation through method)
    void requestRide(Ride* ride) {
        requestedRides.push_back(ride);
        cout << "\n" << name << " requested a " << ride->getRideType() 
             << " ride from " << ride->getPickupLocation() 
             << " to " << ride->getDropoffLocation() << endl;
    }
    
    // View all rides
    void viewRides() const {
        cout << "\n========== RIDER INFORMATION ==========" << endl;
        cout << "Rider ID: " << riderID << endl;
        cout << "Name: " << name << endl;
        cout << "Total Rides Requested: " << requestedRides.size() << endl;
        
        if (!requestedRides.empty()) {
            cout << "\nRide History:" << endl;
            double totalSpent = 0.0;
            for (const auto& ride : requestedRides) {
                cout << "  - Ride #" << ride->getRideID() 
                     << " (" << ride->getRideType() << "): $" 
                     << fixed << setprecision(2) << ride->fare() << endl;
                totalSpent += ride->fare();
            }
            cout << "Total Amount Spent: $" << fixed << setprecision(2) << totalSpent << endl;
        }
        cout << "=======================================" << endl;
    }
    
    // Getters
    int getRiderID() const { return riderID; }
    string getName() const { return name; }
};

// ==================== MAIN FUNCTION ====================
// Demonstrates: Polymorphism
int main() {
    cout << "========================================" << endl;
    cout << "   RIDE SHARING SYSTEM - C++ VERSION   " << endl;
    cout << "========================================" << endl;
    
    // Create riders
    Rider rider1(1001, "Alice Johnson");
    Rider rider2(1002, "Bob Smith");
    
    // Create drivers
    Driver driver1(2001, "John Doe", 4.8);
    Driver driver2(2002, "Jane Williams", 4.9);
    
    // Create different types of rides (Polymorphism)
    Ride* ride1 = new StandardRide(3001, "Downtown", "Airport", 15.5);
    Ride* ride2 = new PremiumRide(3002, "Hotel", "Conference Center", 8.3, true);
    Ride* ride3 = new SharedRide(3003, "University", "Mall", 6.7, 3);
    Ride* ride4 = new StandardRide(3004, "Home", "Office", 12.0);
    Ride* ride5 = new PremiumRide(3005, "Restaurant", "Theater", 4.5, false);
    
    // Store rides in a vector (Polymorphism demonstration)
    vector<Ride*> allRides = {ride1, ride2, ride3, ride4, ride5};
    
    // Riders request rides
    rider1.requestRide(ride1);
    rider1.requestRide(ride2);
    rider2.requestRide(ride3);
    rider2.requestRide(ride4);
    rider1.requestRide(ride5);
    
    // Assign rides to drivers
    driver1.addRide(ride1);
    driver1.addRide(ride3);
    driver2.addRide(ride2);
    driver2.addRide(ride4);
    driver2.addRide(ride5);
    
    // Display all ride details (Polymorphism)
    cout << "\n\n========================================" << endl;
    cout << "     ALL RIDES DETAILS (POLYMORPHISM)   " << endl;
    cout << "========================================" << endl;
    
    for (const auto& ride : allRides) {
        ride->rideDetails();  // Polymorphic call
        cout << endl;
    }
    
    // Calculate total fares (Polymorphism)
    cout << "\n========================================" << endl;
    cout << "     FARE CALCULATION (POLYMORPHISM)    " << endl;
    cout << "========================================" << endl;
    
    double totalRevenue = 0.0;
    for (const auto& ride : allRides) {
        double rideFare = ride->fare();  // Polymorphic call
        totalRevenue += rideFare;
        cout << "Ride #" << ride->getRideID() << " (" << ride->getRideType() 
             << "): $" << fixed << setprecision(2) << rideFare << endl;
    }
    cout << "\nTotal System Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    
    // Display driver and rider information
    driver1.getDriverInfo();
    driver2.getDriverInfo();
    rider1.viewRides();
    rider2.viewRides();
    
    // Clean up memory
    for (auto ride : allRides) {
        delete ride;
    }
    
    cout << "\n========================================" << endl;
    cout << "   SYSTEM DEMONSTRATION COMPLETED       " << endl;
    cout << "========================================" << endl;
    
    return 0;
}