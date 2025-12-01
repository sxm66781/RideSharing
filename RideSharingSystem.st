"==================== RIDE CLASS (BASE CLASS) ===================="
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance baseFarePerMile |
    
    Ride class >> id: id pickup: pickup dropoff: dropoff distance: dist [
        ^ self new initializeWithID: id pickup: pickup dropoff: dropoff distance: dist
    ]
    
    initializeWithID: id pickup: pickup dropoff: dropoff distance: dist [
        rideID := id.
        pickupLocation := pickup.
        dropoffLocation := dropoff.
        distance := dist.
        baseFarePerMile := 2.5.
        ^ self
    ]
    
    rideID [ ^ rideID ]
    pickupLocation [ ^ pickupLocation ]
    dropoffLocation [ ^ dropoffLocation ]
    distance [ ^ distance ]
    
    fare [
        ^ distance * baseFarePerMile
    ]
    
    rideType [
        ^ 'Standard'
    ]
    
    printOn: stream [
        stream 
            nextPutAll: 'Ride #'; 
            print: rideID; 
            nextPutAll: ' ('; 
            nextPutAll: self rideType; 
            nextPutAll: '): $';
            print: self fare asFloat;
            nextPutAll: ' - ';
            nextPutAll: pickupLocation;
            nextPutAll: ' to ';
            nextPutAll: dropoffLocation
    ]
]

"==================== STANDARD RIDE CLASS ===================="
Ride subclass: StandardRide [
    
    StandardRide class >> id: id pickup: pickup dropoff: dropoff distance: dist [
        ^ self new initializeWithID: id pickup: pickup dropoff: dropoff distance: dist
    ]
    
    initializeWithID: id pickup: pickup dropoff: dropoff distance: dist [
        super initializeWithID: id pickup: pickup dropoff: dropoff distance: dist.
        baseFarePerMile := 2.5.
        ^ self
    ]
    
    fare [
        ^ (distance * baseFarePerMile) + 1.5
    ]
    
    rideType [
        ^ 'Standard'
    ]
]

"==================== PREMIUM RIDE CLASS ===================="
Ride subclass: PremiumRide [
    | luxuryVehicle |
    
    PremiumRide class >> id: id pickup: pickup dropoff: dropoff distance: dist luxury: luxury [
        ^ self new initializeWithID: id pickup: pickup dropoff: dropoff distance: dist luxury: luxury
    ]
    
    initializeWithID: id pickup: pickup dropoff: dropoff distance: dist luxury: luxury [
        super initializeWithID: id pickup: pickup dropoff: dropoff distance: dist.
        baseFarePerMile := 4.0.
        luxuryVehicle := luxury.
        ^ self
    ]
    
    fare [
        | baseFare luxuryBonus |
        baseFare := distance * baseFarePerMile.
        luxuryBonus := luxuryVehicle ifTrue: [10.0] ifFalse: [0.0].
        ^ baseFare + 5.0 + luxuryBonus
    ]
    
    rideType [
        ^ 'Premium'
    ]
]

"==================== SHARED RIDE CLASS ===================="
Ride subclass: SharedRide [
    | numberOfPassengers |
    
    SharedRide class >> id: id pickup: pickup dropoff: dropoff distance: dist passengers: pass [
        ^ self new initializeWithID: id pickup: pickup dropoff: dropoff distance: dist passengers: pass
    ]
    
    initializeWithID: id pickup: pickup dropoff: dropoff distance: dist passengers: pass [
        super initializeWithID: id pickup: pickup dropoff: dropoff distance: dist.
        baseFarePerMile := 1.5.
        numberOfPassengers := pass.
        ^ self
    ]
    
    fare [
        ^ (distance * baseFarePerMile) * 0.70
    ]
    
    rideType [
        ^ 'Shared'
    ]
]

"==================== DRIVER CLASS ===================="
Object subclass: Driver [
    | driverID name rating assignedRides |
    
    Driver class >> id: id name: driverName rating: rate [
        ^ self new initializeWithID: id name: driverName rating: rate
    ]
    
    initializeWithID: id name: driverName rating: rate [
        driverID := id.
        name := driverName.
        rating := rate.
        assignedRides := OrderedCollection new.
        ^ self
    ]
    
    name [ ^ name ]
    
    addRide: aRide [
        assignedRides add: aRide
    ]
    
    totalEarnings [
        | total |
        total := 0.0.
        assignedRides do: [:ride | total := total + ride fare].
        ^ total
    ]
    
    printOn: stream [
        stream 
            nextPutAll: 'Driver: ';
            nextPutAll: name;
            nextPutAll: ' (ID: ';
            print: driverID;
            nextPutAll: ', Rating: ';
            print: rating;
            nextPutAll: ', Rides: ';
            print: assignedRides size;
            nextPutAll: ', Earnings: $';
            print: self totalEarnings asFloat;
            nextPutAll: ')'
    ]
]

"==================== RIDER CLASS ===================="
Object subclass: Rider [
    | riderID name requestedRides |
    
    Rider class >> id: id name: riderName [
        ^ self new initializeWithID: id name: riderName
    ]
    
    initializeWithID: id name: riderName [
        riderID := id.
        name := riderName.
        requestedRides := OrderedCollection new.
        ^ self
    ]
    
    name [ ^ name ]
    
    requestRide: aRide [
        requestedRides add: aRide
    ]
    
    totalSpent [
        | total |
        total := 0.0.
        requestedRides do: [:ride | total := total + ride fare].
        ^ total
    ]
    
    printOn: stream [
        stream 
            nextPutAll: 'Rider: ';
            nextPutAll: name;
            nextPutAll: ' (ID: ';
            print: riderID;
            nextPutAll: ', Rides: ';
            print: requestedRides size;
            nextPutAll: ', Spent: $';
            print: self totalSpent asFloat;
            nextPutAll: ')'
    ]
]

"==================== MAIN EXECUTION ===================="
| rider1 rider2 driver1 driver2 ride1 ride2 ride3 allRides totalRevenue |

"Create objects"
rider1 := Rider id: 1001 name: 'Alice Johnson'.
rider2 := Rider id: 1002 name: 'Bob Smith'.
driver1 := Driver id: 2001 name: 'John Doe' rating: 4.8.
driver2 := Driver id: 2002 name: 'Jane Williams' rating: 4.9.

ride1 := StandardRide id: 3001 pickup: 'Downtown' dropoff: 'Airport' distance: 15.5.
ride2 := PremiumRide id: 3002 pickup: 'Hotel' dropoff: 'Center' distance: 8.3 luxury: true.
ride3 := SharedRide id: 3003 pickup: 'University' dropoff: 'Mall' distance: 6.7 passengers: 3.

allRides := Array with: ride1 with: ride2 with: ride3.

"Assign rides"
rider1 requestRide: ride1.
rider1 requestRide: ride2.
rider2 requestRide: ride3.
driver1 addRide: ride1.
driver1 addRide: ride3.
driver2 addRide: ride2.

"Calculate total revenue"
totalRevenue := 0.0.
allRides do: [:ride | totalRevenue := totalRevenue + ride fare].

"Output results"
Transcript show: '=== RIDE SHARING SYSTEM ==='; cr; cr.
Transcript show: 'RIDES:'; cr.
allRides do: [:ride | 
    Transcript show: '  '; show: ride printString; cr
].
Transcript cr.
Transcript show: 'DRIVERS:'; cr.
Transcript show: '  '; show: driver1 printString; cr.
Transcript show: '  '; show: driver2 printString; cr.
Transcript cr.
Transcript show: 'RIDERS:'; cr.
Transcript show: '  '; show: rider1 printString; cr.
Transcript show: '  '; show: rider2 printString; cr.
Transcript cr.
Transcript show: 'Total Revenue: $'; show: totalRevenue asFloat printString; cr.
Transcript show: '=== COMPLETED ==='; cr.