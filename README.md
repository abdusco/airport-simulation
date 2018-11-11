# Discrete Event Simulation
A simple C++ program to simulate passanger dynamics in an airport

## Problem Statement
The airport is modelled as:
```
                              +-- LUGGAGE AREA --+                      +-- LUGGAGE AREA --+
                            /                     \                    /                    \
ENTRY --- LUGGAGE ----+----- ---- LUGGAGE AREA ----+ --- SECURITY ----+---- LUGGAGE AREA ----+ -- DEPARTURE 
           QUEUE            \                     /       QUEUE        \                    / 
                             +--- LUGGAGE AREA --+                      +-- LUGGAGE AREA --+ 
```
A passenger goes to luggage area, if all counters are busy, gets in the queue, waiting for his turn. 
After his luggage has been cleared, he moves to security area, and again waits if all counters are busy.

Originally all queues are FIFO (first in first out) based, and there are complaints of long waiting times 
and missed flights. To mitigate this problem, a number of solutions is available:

## Solution Proposals
### 1. First-to-fly First Serve
With this policy, a passenger whose flight is the earliest will be allowed to cut in the line and get service right away.

### 2. VIP Passenger Program
This program allows passengers with VIP memberships to skip the security lines altogether.

### 3. Online Ticketing System
This system allows passengers that checked-in on the internet to skip luggage counters if they have no luggage to check in 

## Test Cases
There are 8 test cases to check the effectiveness of combination of solutions for 3 different proposals.


|F2FFS|VIP|ONLINE|Notes|
|:-:|:-:|:-:|:-:|
| | | |Default first-come first served policy|
|x| | | |
| |x| | |
|x|x| | |
| | |x| |
|x| |x| |
|x|x|x| |

