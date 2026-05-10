// ==========================================
// Carpooling Application
// ==========================================

#include <iostream>
#include <string>
using namespace std;

// ==========================================
// User
// ==========================================

// BASE CLASS: Demonstrates Abstract Base Class (ABC) concept
// ABSTRACTION: User is a general template. Passenger and Driver provide specific details.
class User {
private:
    // ENCAPSULATION: Private attributes restricted to class scope
    int userID;
    string userName;
    string emailAddress;
    string userPassword;
    string phoneNumber;
    static int totalUserCount; // STATIC MEMBER: Shared by all User instances

public:
    User(int id, string name, string email, string phoneNo, string password);
    virtual ~User(); // VIRTUAL DESTRUCTOR: Prevents memory leaks in the case of inheritance.
	
	string getUserName();
    bool login(string enteredUsername, string enteredPassword) const;
    void logout();
    static int getTotalUsers();


    // POLYMORPHISM: Virtual function for dynamic binding
    virtual void displayUserInfo() const; 
};
//----------------------------------------------------------------------------------------------

// Initialize the static member to track the total number of users
int User::totalUserCount = 0;

// Constructor for the User class.
User::User(int id, string name, string email, string phoneNo, string password) {
    userID = id;
    userName = name;
    emailAddress = email;
    userPassword = password;
    phoneNumber = phoneNo;
    totalUserCount++; // // Increment total users whenever a new User-based object is created
}

// Destructor for the User class.
User::~User() { totalUserCount--; }

// Getter for the userName attribute.
string User::getUserName(){
	return userName;
}

/**
 * The login process.
 * Basic Error Handling/Validation by checking credentials.
 * enteredEmail The email input from the user.
 * enteredPassword The password input from the user.
 * true if credentials match, false otherwise.
 */
bool User::login(string enteredEmail, string enteredPassword) const{
	// Validating the input against the stored member variables
    if (this->emailAddress == enteredEmail && this->userPassword == enteredPassword){
    	cout<<"Successful: "<<userName<<" have logged in to the system."<<endl;
    	return true;
	}else{
		cout<<"Error: Email or password is incorrect!"<<endl;
		return false;
	}
}

// logout action and provides feedback to the user.
void User::logout(){
	cout<<"The exit was successful."<<endl;
}

// Static method to retrieve the total number of users currently in the system.
int User::getTotalUsers() { return totalUserCount; }

/**
 * Displays shared user profile information.
 * This method is called or overridden by derived classes.
 */
void User::displayUserInfo() const {
    cout << "ID: " << userID << "\nName: " << userName << "\nEmail: " << emailAddress << "\nPhone: " << phoneNumber << endl;
}

// ==========================================
// Passenger
// ==========================================

// INHERITANCE: Passenger inherits from User class
class Passenger : public User {
private:
    float walletBalance;

public:
    Passenger(int id, string name, string email, string phoneNo, string password, float balance);
    ~Passenger();

    void searchRide(string destination);

    // FUNCTION OVERLOADING: Same function name, different parameters
    bool bookRide(int rideID);
    bool bookRide(int rideID, int seatCount);

    bool cancelBooking(int bookingID);
    
    float getBalance() const;
    void setBalance(float b);

    // OVERRIDING: Custom implementation of displayUserInfo
    void displayUserInfo() const override;

    // FRIEND FUNCTION: Accesses private members without being a member
    friend void showPassenger(const Passenger p);
};

//--------------------------------------------------------------------------------------------------------------------

// Constructor for Passenger class.
Passenger::Passenger(int id, string name, string email, string phoneNo, string password, float balance)
    : User(id, name, email, phoneNo, password) {
    walletBalance = balance;
}

// Destructor for Passenger class.
Passenger::~Passenger() { cout << "Passenger object destroyed" << endl; }

// Simulates searching for a ride based on a destination string
void Passenger::searchRide(string destination) { cout << "Searching: " << destination << endl; }

// METHOD OVERLOADING: bookRide version 1 (Single seat)
bool Passenger::bookRide(int rideID) { return true; }

// METHOD OVERLOADING: bookRide version 2 (Multiple seats)
bool Passenger::bookRide(int rideID, int seatCount) { return true; }

// The cancellation of a booking by its ID.
bool Passenger::cancelBooking(int bookingID) { return true; }

// Getter method for walletBalance.
// Marked as 'const' to ensure it does not modify the object state.
float Passenger::getBalance() const{
	return walletBalance;
}

// Setter method for walletBalance.
// Used to update the passenger's funds after a payment
void Passenger::setBalance(float b){
	walletBalance=b;
}

// Overridden method to display passenger details.
void Passenger::displayUserInfo() const {
    cout << "----- Passenger Information -----" << endl;
    User::displayUserInfo();
    cout << "Wallet: " << walletBalance << " TL" << endl;
}

/**
 * Friend function example.
 * Accesses the private 'walletBalance' member of the Passenger class directly.
 */
void showPassenger(const Passenger p) {
    cout << "Friend Access Wallet: " << p.walletBalance << endl;
}

// ==========================================
// Vehicle
// ==========================================

// This is the class that manages the technical specifications and passenger capacity of the vehicle. 
class Vehicle {
private:
    // ENCAPSULATION: Data members are hidden from direct access
    string vehicleType;
	string plateNumber;
	string model;
    int totalCapacity;

public:
    // CONSTRUCTOR OVERLOADING: Default and Parameterized constructors
    Vehicle();
    Vehicle(string vehicleType, string model, string plateNumber, int totalCapacity);

    // SETTER METHODS: Controlled modification of private data
    void setVehicleType(string vehicleType);
    void setPlateNumber(string plateNumber);
    void setModel(string model);
    void setCapacity(int c);

    // CONST METHOD: Ensures the function does not modify the object

    void vehicleDetails() const;
};

//--------------------------------------------------------------------------------------------------------------------

// Default Constructor
Vehicle::Vehicle() : vehicleType("Unknown"), plateNumber("00-AAA-0000"), model("Unknown"), totalCapacity(0) {}

// Parameterized Constructor
/* Demonstrates the use of the "this" pointer to resolve naming conflicts 
 * between parameters and member variables.
 */
Vehicle::Vehicle(string vehicleType, string model, string plateNumber, int totalCapacity) {
    this->vehicleType = vehicleType; // Use of "this" pointer
    this->model = model;
    this->plateNumber = plateNumber;
    this->totalCapacity = totalCapacity;
}

// Setter methods (Encapsulation)
void Vehicle::setVehicleType(string vt) { vehicleType = vt; }
void Vehicle::setPlateNumber(string pn) { plateNumber = pn; }
void Vehicle::setModel(string m) { model = m; }
void Vehicle::setCapacity(int c) { totalCapacity = c; }

/* Displays vehicle specifications.
 * This method is utilized by the Driver class via Composition to show trip-related info.
 */
void Vehicle::vehicleDetails() const {
	cout<< "Vehicle Type: "<<vehicleType<<endl;
    cout<< "Vehicle: " << model <<endl;
	cout<< "Plate Number: [" << plateNumber << "]"<<endl;
	cout<< "Capacity: " << totalCapacity << endl;
}

// ==========================================
// Ride
// ==========================================


// Manages the data structure and status of trips (advertisements) created by the driver.
// Groups departure and arrival information using the 'Route' structure (struct).
struct Route{
	string departure;
	string destination;
};

class Ride {
private:
	// Member variables are private to ensure Encapsulation
    int rideID;
    Route rideRoute; // Struct usage
    string date, time;
    double ridePrice;
    int seat_number; // Tracks the current number of available seats

public:
	// Constructor to initialize a Ride object with trip specifics.
    Ride(int id, string departure, string destination, string date, string time, int seats, double price);
   
    // Constant getter method to retrieve the price of the ride. Guaranteed not to modify the object's state.
    double getRidePrice() const;
    
    // Constant getter method to check current seat availability.
    int getAvailableSeats() const;
    
    /*
     * Setter method to update the available seats when a booking is confirmed or cancelled.
     */
    void setAvailableSeats(int s);
    
    // Constant method to display all information regarding the ride
    void showRideDetails() const;
};

//---------------------------------------------------------------------------------------------------

// Constructor to initialize the Ride object.
Ride::Ride(int id, string dep, string dest, string d, string t, int s, double p) {
    rideID = id;
    rideRoute.departure = dep; // Struct assign
    rideRoute.destination = dest; // Struct assign
    date = d;
    time = t;
    seat_number = s;
    ridePrice = p;
}

// Getter for the ride price.
double Ride::getRidePrice() const{ return (double)ridePrice; }

// Returns the current number of empty seats. Used by other classes to check availability.
int Ride::getAvailableSeats() const{
	return seat_number;
}

// Updates the seat count.
void Ride:: setAvailableSeats(int s){
	seat_number = s;
}

// Displays trip details
void Ride::showRideDetails() const{
    cout << "\n---------- Ride Details ----------" << endl;
    cout << "Ride ID : " << rideID << endl;
    cout << "Route : " << rideRoute.departure << " -> " << rideRoute.destination << endl;
    cout << "Date-Hour : " << date << " | " << time << endl;
    cout << "Fee : " << ridePrice << " TL" << endl;
    cout << "Empty Seat : " << seat_number << endl;
}

// ==========================================
// Driver
// ==========================================

// INHERITANCE: Driver inherits from User class
class Driver : public User {
private:
    // COMPOSITION: Driver class has a Vehicle object. Managed as part of the Driver object.
    Vehicle ownedVehicle;

public:
    static int totalDrivers;
    Driver(int id, string name, string email, string password, string phoneNo, Vehicle vehicleModel);
    ~Driver();

    static int getTotalDrivers();
    Ride offerRide(int id, string departure, string destination, string date, string time, int availableSeats, double price);

    // POLYMORPHISM: Overriding the base class function
    void displayUserInfo() const override;

};

//--------------------------------------------------------------------------------------------------------------------------------

// Initialize the static member to keep track of the total number of Driver instances
int Driver::totalDrivers = 0;

// MEMBER INITIALIZATION LIST: Calling base class constructor
Driver::Driver(int id, string name, string email, string password, string phoneNo, Vehicle vehicleModel)
    : User(id, name, email, phoneNo, password), ownedVehicle(vehicleModel) {
    totalDrivers++;
}

/* Destructor for Driver class.
 * Decrements the static driver counter when a Driver object is destroyed.
*/
Driver::~Driver() { totalDrivers--; }

// Static method to retrieve the total count of drivers in the system.
int Driver::getTotalDrivers() { return totalDrivers; }

/*
 * Method to create and return a new Ride object.
 * This represents the action of a driver offering a trip in the system.
 */
Ride Driver::offerRide(int id, string departure, string destination, string date, string time, int availableSeats, double price) {
    return Ride(id, departure, destination, date, time, availableSeats, price);
}

// Overridden method to display driver details.
void Driver::displayUserInfo() const {
	cout << "---------- Driver Information ----------" << endl;
    User::displayUserInfo(); // Calling base class method
    cout << "\n----- Driver's Vehicle Information -----" << endl;
    ownedVehicle.vehicleDetails(); // Calling method from composed object
}

// ==========================================
// Booking
// ==========================================

// ASSOCIATION: This class connects Ride and Passenger classes
// It provides memory efficiency by using pointers instead of copying objects themselves.
// It includes reservation confirmation, cancellation, and updating seat numbers.
class Booking {
private:
    static int totalBookings;
    int bookingID;
    // POINTERS: Using pointers to associate existing objects
    Ride* ride;
    Passenger* passenger;
    int seatCount;

public:
    Booking(int id, Ride* r, Passenger* p, int seats);
    ~Booking();

    bool confirmBooking();
    bool cancelBooking();
    string getBookingDetails() const;
    static int getTotalBookings();

    // FRIEND FUNCTION: Grants non-member function access to private data
    friend void showBooking(const Booking& b);
};

//--------------------------------------------------------------------------------------------------------------------------

// Initialize the static member to track the total number of bookings across all instances
int Booking::totalBookings = 0;

/**
 * Constructor for Booking class.
 * Links a Passenger with a Ride and sets the number of seats requested.
 * Increments the static totalBookings counter.
 */
Booking::Booking(int id, Ride* r, Passenger* p, int seats) : bookingID(id), ride(r), passenger(p), seatCount(seats) {
    totalBookings++;
}

/**
 * Destructor for Booking class.
 * Outputs a message when the object life cycle ends.
 */
Booking::~Booking() { cout << "Booking object destroyed" << endl; }

/**
 * Validates and confirms the booking.
 * Logic: Checks availability, updates the Ride state, and provides feedback.
 * @return true if seats were available and booking is confirmed, false otherwise.
 */
bool Booking::confirmBooking() { 
	// Check if the associated Ride has enough available seats
	if(ride->getAvailableSeats()>=seatCount){
		int remainingSeats=ride->getAvailableSeats()-seatCount; // Calculate the new seat count after deduction
		ride->setAvailableSeats(remainingSeats); // Update the Ride object's state using its setter method
		cout << "Booking Confirmed. Booking ID: " << bookingID << endl;
		cout<< "The remaining number of seats on the ride "<<remainingSeats<<endl;
		return true;
	}else{
		cout <<"Error: Not enough empty seats on the ride!"<<endl; // Handle error case: insufficient capacity
		return false;
	}
}

/**
 * Reverts a booking and returns the seats to the Ride capacity.
 * Demonstrates the ability to modify object state in reverse.
 */
bool Booking::cancelBooking() {
	// Add the reserved seats back to the Ride's total
	int returnedSeat=ride->getAvailableSeats()+seatCount;
	ride->setAvailableSeats(returnedSeat);
	cout<<"Cancelled: Reservation ID " << bookingID << " deleted, seats returned."<<endl;
	return true;
}

// Returns basic booking identification as a string.
string Booking::getBookingDetails() const { return "Booking ID: " + to_string(bookingID); }

//Static method to access the total number of bookings made in the system.
int Booking::getTotalBookings() { return totalBookings; }

// Friend function: Accesses the private bookingID directly.
void showBooking(const Booking& b) { cout << "Friend Access ID: " << b.bookingID << endl; }

// ==========================================
// Payment
// ==========================================

// Payment class manages payment processing and dynamic memory management.
class Payment {
private:
    int paymentID;
    // DYNAMIC MEMORY: Pointer for heap allocation
    float* paymentAmount; 
    string paymentStatus;

public:
    Payment(int id, float amount);
    ~Payment(); // DESTRUCTOR: Releases dynamic memory

    bool makePayment(Passenger& p);
    void displayPaymentInfo() const;
};

//---------------------------------------------------------------------------------------------------------------------

// Constructor for Payment class.
Payment::Payment(int id, float amount) {
    paymentID = id;

    // DYNAMIC MEMORY ALLOCATION: Using 'new'
    paymentAmount = new float(amount); 
    paymentStatus = "Pending";
}

Payment::~Payment() {
    // DEALLOCATION: Avoiding memory leaks
    delete paymentAmount;
    cout << "Payment dynamic memory freed." << endl;
}

// Validates passenger balance and updates their financial state.
bool Payment::makePayment(Passenger& p) {
	cout<<"Passenger Balance: "<<p.getBalance()<<" TL"<<endl;
	
	// Logical Check: Ensuring the passenger has enough funds.
    // Dereferencing (*paymentAmount) to access the value stored in the heap.
	if(p.getBalance()>= *paymentAmount){
		float newBalance=p.getBalance()- *paymentAmount; // Calculate new balance after the transaction
		p.setBalance(newBalance); // Update the Passenger's state using the setter method
		cout<<"Payment Successful!"<<endl;
		cout<<"Remaining Balance: "<<p.getBalance()<<" TL"<<endl;
		return true;
	}else{
		// Error Handling: Manage cases where the transaction cannot proceed.
		cout<<"Error: Insufficient balance for this ride!" << endl;
		return false;
	}
}

// Constant member function to display transaction details.

void Payment::displayPaymentInfo() const{ cout << "Status: " << paymentStatus << " Amount: " << *paymentAmount << endl; }

// ==========================================
// main
// ==========================================

/*
  Helper function to handle the payment and booking logic.
*/
void processRideTransaction(Booking& b, Payment& p, Passenger& pass) {
	cout<<"\n------------- Payment --------------"<<endl;
    cout << "------ Processing Transaction ------" << endl;
    // Attempt to make payment: Deducts from passenger balance if sufficient
    if (p.makePayment(pass)) {
    	// If payment is successful, confirm the reservation and update ride seats
        b.confirmBooking();
    } else {
    	// Error Handling for insufficient funds
        cout << "Transaction cancelled, insufficient balance." << endl;
    }
    cout << "-----------------------------------" << endl;
}

int main() {
    // COMPOSITION: Creating a Vehicle object
    Vehicle myVehicle("Car", "Toyota Corolla", "34 ABC 123", 3);

    // INHERITANCE: Driver inherits from User.
    Driver myDriver(2109, "John Doe", "john@mail.com", "1234", "555-0101", myVehicle);
    
    // Driver and Driver's vehicle Information
    myDriver.displayUserInfo();
    cout << "-----------------------------------" << endl;
    
	// INHERITANCE: Passengers also inherit from User.
    Passenger myPassenger(3, "Elif Kaya", "elif@mail.com", "562-2356", "2115", 500);
    Passenger myPassenger2(4, "Ali Deniz", "aliDeniz@gmail.com", "867-3602", "7536", 100);
    
    // RIDE CREATION: The driver offers a ride, creating a Ride object.
    cout<<"\nThe ride is being created..."<<endl;
    Ride myRide = myDriver.offerRide(1, "Istanbul", "Ankara", "6 May", "14:00", 3, 450.0);
	myRide.showRideDetails();
	cout << "-----------------------------------\n" << endl;

	// ASSOCIATION: Creating a Booking to link a Passenger with a Ride.
	Booking myBooking(9001, &myRide, &myPassenger, 1);
	
	// Login: Checking credentials for the first passenger.
    cout<<myPassenger.getUserName()<<" is trying to log in."<<endl;
    myPassenger.login("elif@mail.com", "2115");
    cout<<"\n"<<endl;
    myPassenger.displayUserInfo();
    cout<<"----------------------------------"<<endl;
    
	// PAYMENT & BOOKING PROCESS: Successful transaction scenario
	Payment myPayment(2301, myRide.getRidePrice()); // Creating a payment equal to the ride price
	processRideTransaction(myBooking, myPayment, myPassenger);
	
	// STATE UPDATE: Show ride details again to prove that seats have decreased
	cout<<"\nUpdated ride details."<<endl;
	myRide.showRideDetails();
	cout << "-----------------------------------\n" << endl;
	myPassenger.logout();
	cout << "\n-----------------------------------\n" << endl;
	
	// LOGIC FLOW: Second passenger login and failed transaction scenario
	cout<<myPassenger2.getUserName()<<" is trying to log in."<<endl;
	myPassenger2.login("aliDeniz@gmail.com", "1234"); // Invalid login attempt
	myPassenger2.login("aliDeniz@gmail.com", "7536"); // Successful login
	cout<<"\n"<<endl;
	myPassenger2.displayUserInfo();
	cout<<"----------------------------------\n"<<endl;
	
	//Error Check: Checking for insufficient balance error
	cout<<myPassenger2.getUserName()<<" is making a reservation..."<<endl;
	Payment myPayment2(2302, myRide.getRidePrice()); // Creating a payment equal to the ride price
	processRideTransaction(myBooking, myPayment2, myPassenger2);
	cout<<"\n"<<endl;
	myPassenger2.logout();
	cout << "\n-----------------------------------\n" << endl;
	
    return 0;
}

