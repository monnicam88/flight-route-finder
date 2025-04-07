# Flight Route Finder
[![C++14](https://img.shields.io/badge/C%2B%2B-14-blue)](https://en.cppreference.com/w/cpp/14) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Introduction

<p align="justify">The Flight Route Finder is a comprehensive solution of the internship task for PROS. It is designed to help finding optimal flight routes between cities. The system consists of two main interfaces:</p>

&emsp; - A console application for interactive use - **Subtask 1**  
&emsp; - A RESTful HTTP API for programmatic access - **Subtasks 2 and 3**
   
<div align="justify">Both interfaces use the same core components to manage flight data and find routes. Some test cases for validation of system correct functionality are also added - <b>Subtask 4</b>.</div>

## Repository Structure

```
PROS_Internship/
|
├─ data/                                 # Raw datasets used for testing the functionallity
|  ├─ flights/                           # Flights datasets
|  |  ├─ flights-network_rows-07.txt/    # Original data from the task condition
|  |  └─ flights-network_rows-55.txt/    # Additionally generated data
|  ├─ requests/                          # All requests from Subtask 4.md
|  |  └─ requests.json               
|  └─ responses/                         # All responses from Subtask 4.md
|     ├─ response_01.json                # First request response
|     ├─ ...
|     └─ response_N.json                 # N-th request response
|
├─ docs/                                 # Document files (.md)
|  ├─ Subtask 4.md/                      # Some test case scenarios
|  ├─ CompilationProcess.md/             # How to run the project
|  └─ images/                            # Images used in the project
|
├─ include/                              # Header files (.h/.hpp)
|  ├─ json.hpp/                          # Used for HTTP server implementation
|  ├─ httplib.h/                         # Used for HTTP server implementation
|  ├─ Route.h/                           # Represents a complete route from origin to destination
|  ├─ Flight.h/                          # Represents a single flight between two cities
|  ├─ ConsoleDemo.h/                     # Represents Subtask 1
|  ├─ RouteService.h/                    # Service layer for managing flight data and finding routes
|  └─ StartHttpRequest.h/                # Represents Subtasks 2 and 3
|
├─ src/                                  # Implementation files (.cpp)
|  ├─ main.cpp/                          # The project 'start point'
|  ├─ Route.cpp/                         # Route finding algorithm
|  ├─ Flight.cpp/                    
|  ├─ ConsoleDemo.cpp/                   # Logic for Subtask 1
|  ├─ RouteService.cpp/              
|  └─ StartHttpRequest.cpp/              # Logic for Subtasks 2 and 3
|
├─ .gitignore                            # Specifies intentionally untracked files to ignore
├─ README.md                             # Overview of the project 
└─ LICENSE                               # MIT License                       
```

## Algorithm Description
<p align="justify">The route finding algorithm uses depth-first search with backtracking to find all possible paths from origin to destination. It is implemented in the <i>findRoutesRecursive()</i> method, which is a helper function for <i>findPossibleRoutes()</i>. The recursive function builds routes step by step, tracking:</p>

```
  - Current city  
  - Visited cities                   # to prevent cycles 
  - Current path                     # sequence of cities 
  - Current accumulated price  
  - Number of flights taken          # for the maxFlights constraint
```
When a valid route is found (reaching the destination within the maxFlights constraint), it is added to the results vector.

## Implementation Details
Flight data can be loaded from a text file where each line representing a flight in the format: ` ORIGIN,DESTINATION,PRICE `. The HTTP server is implemented using the _cpp-httplib_ library and _nlohmann/json_.

## Error Handling
<table style="width: 100%; font-family: monospace;">
  <tr>
    <td style="vertical-align: top; width: 50%; text-align: justify">
      <strong>File loading errors</strong><br>
      Checks if the file can be opened<br>
      Validates each line's format<br>
      Uses try-catch blocks for parsing numeric values
    </td>
    <td style="vertical-align: top; width: 50%; text-align: justify">
      <strong>API input validation</strong><br>
      Validates presence of required fields (origin, destination)<br>
      Validates data types (<code>std::string</code> for cities, <code>&lt;uint32_t&gt;</code> for maxFlights)<br>
      Returns appropriate error messages with HTTP 400 status codes
    </td>
  </tr>
</table>

## Sources
[cpp-httplib] (https://github.com/yhirose/cpp-httplib)  
[JSON for Modern C++] (https://github.com/nlohmann/json)  
[POST Request using Postman] (https://www.toolsqa.com/postman/post-request-in-postman/)  
[Mastering C++ Httplib: A Quick Guide to Web Requests] (https://cppscripts.com/cpp-httplib)
