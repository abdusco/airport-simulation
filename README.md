# Discrete Event Simulation
A simple C++ program to simulate passenger dynamics in an airport.


## Problem Statement
The airport is modelled as:
```
                      +- LUGGAGE AREA -+                  +- SECURITY AREA -+
                    /                   \                /                   \
ENTRY -- LUGGAGE --+---- LUGGAGE AREA ---+-- SECURITY --+--- SECURITY AREA ---+-- DEPARTURE 
          QUEUE     \                   /     QUEUE      \                   / 
                     +-- LUGGAGE AREA -+                  +- SECURITY AREA -+ 
```
A passenger goes through following steps before he gets on the plane:
1. Enter the airport 
2. Go to the luggage area.  
  If all counters are busy, get in the queue, and wait until luggage has been cleared.
3. Moves along to the security area.
  If all counters are busy, wait in the line until checked out.
4. Go to departure area and get on the plane.

Originally all queues are FIFO (first in first out) based, and but as more and more passengers prefer this airport
complaints of long waiting times and missed flights start to increase. 

A number of solutions is available to reduce the delays:

## Solution Proposals
### 1. First-to-fly First Serve
With this policy, a passenger whose flight is the earliest 
will be allowed to cut in the line and get service right away.

### 2. VIP Passenger Program
This program allows passengers with VIP memberships to skip the security lines altogether.

### 3. Online Ticketing System
This system allows passengers that checked-in on the internet 
to skip luggage counters if they have no luggage to check in. 

## Test Cases
There are 8 test cases to check the effectiveness of all combination of 3 different proposals.

| F2FFS |  VIP  | ONLINE | Notes |
|:-----:|:-----:|:------:|:-----:|
|       |       |        | FCFS  |
|   x   |       |        |       |
|   x   |       |        |       |
|   x   |   x   |        |       |
|   x   |       |        |       |
|   x   |       |    x   |       |
|   x   |   x   |    x   |       |


## Build
```bash
$ make clean
$ make CMakeList.txt
$ make
```

## Usage
```bash
$ ./project2 input.txt report.txt
```
