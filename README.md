# Discrete Event Simulation
A simple C++ program to simulate passenger dynamics in an airport.


## Problem Statement
The airport is modelled as:
```
                     +- LUGGAGE AREA -+                  +- SECURITY AREA -+
                    /                  \                /                   \
ENTRY -- LUGGAGE --+--- LUGGAGE AREA ---+-- SECURITY --+--- SECURITY AREA ---+-- DEPARTURE 
          QUEUE     \                  /     QUEUE      \                   / 
                     +- LUGGAGE AREA -+                  +- SECURITY AREA -+ 
```
A passenger goes through following steps before he gets on the plane:
1. Enter the airport 
2. Go to the luggage area.  
  If all counters are busy, get in the queue, and wait until luggage has been cleared.
3. Move along to the security area.  
  If all counters are busy, wait in the line until cleared.
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
|       |   x   |        |       |
|   x   |   x   |        |       |
|       |       |    x   |       |
|   x   |       |    x   |       |
|       |   x   |    x   |       |
|   x   |   x   |    x   |       |


## Input
Syntax is as follows:
```text
<NUM_PASSENGERS> <NUM_LUGGAGE_COUNTERS> <NUM_SECURITY_COUNTERS>
<T_ENTER> <T_FLIGHT> <T_WAIT_LUGGAGE> <T_WAIT_SECURITY> <IS_VIP> <HAS_LUGGAGE>
<T_ENTER> <T_FLIGHT> <T_WAIT_LUGGAGE> <T_WAIT_SECURITY> <IS_VIP> <HAS_LUGGAGE>
...
...
```
where:
+ `IS_VIP` = `{V, N}` to denote VIP status.
+ `HAS_LUGGAGE` = `{L, N}` to denote presence of luggage.
+ All remaining parameters are integers.

An example is included in `inputSample.txt`

## Output
The simulation results for each test case is written to report file, 
also output to the console if verbose flag is set. 

Each line is `<AVG_WAIT_TIME> <MISSED_FLIGHTS>`
```text
7.625 3
7.375 3
6.250 1
6.125 0
5.750 2
5.500 1
4.500 1
4.500 1
```

## Build
```bash
$ make clean
$ cmake CMakeList.txt
$ make
```

## Usage
```bash
$ ./project2 <input.txt> <report.txt> [verbose]
```
