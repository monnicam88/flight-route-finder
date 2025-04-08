## Groups of Test Cases

### 1. Basic Functionality Tests  
&emsp;**1.1. Find existing and missing routes**  
| ID | Description | Request                         | Expexted result | HTTP status |
|----|-------------|---------------------------------|:---------------:|:-----------:|
| 1.1.1 | <p align="justify">Verify that all possible routes from SOF to MLE<br>are returned, sorted by price</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE" }` | <a href=".../data/responses/response_01.json">Response</a> | 200 |
| 1.1.2 | <p align="justify">Verify that all possible routes from SOF to LON<br>are returned, sorted by price</p> | `{ "origin": "SOF",`<br>`  "destination": "LON" }` | <a href="../data/responses/response_02.json">Response</a> | 200 |
| 1.1.3 | <p align="justify">Verify empty array is returned when no routes<br>exist</p> | `{ "origin": "MLE",`<br>`  "destination": "SOF" }` | <a href="../data/responses/response_03.json">Response</a> | 200 |
| 1.1.4 | <p align="justify">Verify empty array is returned when having non<br>-existent city codes</p> | `{ "origin": "MAL",`<br>`  "destination": "MLE" }` | <a href="../data/responses/response_04.json">Response</a> | 200 |

### 2. Input validation
&emsp;**2.1. Missing mandatory parameters**
| ID | Description | Request                         | Expexted result | HTTP status |
|----|-------------|---------------------------------|:---------------:|:-----------:|
| 2.1.1 | <p align="justify">Missing parameter "origin"</p> | `{ "destination": "MLE" }` | <a href="../data/responses/response_05.json">Response</a> | 400 |
| 2.1.2 | <p align="justify">Missing parameter "destination"</p> | `{ "origin": "SOF" }` | <a href="../data/responses/response_06.json">Response</a> | 400 |
| 2.1.3 | <p align="justify">Empty request body</p> | `{}` | <a href="../data/responses/response_07.json">Response</a> | 400 |

&emsp;**2.2. Invalid types of parameters**
| ID | Description | Request                         | Expexted result | HTTP status |
|----|-------------|---------------------------------|:---------------:|:-----------:|
| 2.2.1 | <p align="justify">Invalid type for parameter "origin"</p> | `{ "origin": 123,`<br>`  "destination": "MLE" }` | <a href="../data/responses/response_08.json">Response</a> | 400 |
| 2.2.2 | <p align="justify">Invalid type for parameter "destination"</p> | `{ "origin": "SOF",`<br>`  "destination": 123 }` | <a href="../data/responses/response_09.json">Response</a> | 400 |
| 2.2.3 | <p align="justify">Invalid type for parameter "maxFlights"</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": "two" }` | <a href="../data/responses/response_10.json">Response</a> | 400 |
| 2.2.4 | <p align="justify">Negative value for parameter "maxFlights"</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": -1 }` | <a href="../data/responses/response_11.json">Response</a> | 400 |
| 2.2.5 | <p align="justify">Too big value for parameter "maxFlights"</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": 4294967296 }` | <a href="../data/responses/response_12.json">Response</a> | 400 |

&emsp;**2.3. Invalid JSON request format**
| ID | Description | Request                         | Expexted result | HTTP status |
|----|-------------|---------------------------------|:---------------:|:-----------:|
| 2.3.1 | <p align="justify">Invalid JSON</p> | `{ "origin": SOF,`<br>`  "destination": MLE }` | <a href="../data/responses/response_13.json">Response</a> | 400 |

### 3. Limitations on the maximum number of flights in a route
&emsp;**3.1. Valid limitations**
| ID | Description | Request                         | Expexted result | HTTP status |
|----|-------------|---------------------------------|:---------------:|:-----------:|
| 3.1.1 | <p align="justify">Maximum 1 flight<br>(the direct flight only)</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": 1 }` | <a href="../data/responses/response_14.json">Response</a> | 200 |
| 3.1.2 | <p align="justify">Maximum 2 flights</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": 2 }` | <a href="../data/responses/response_15.json">Response</a> | 200 |
| 3.1.3 | <p align="justify">Maximum 0 flights</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": 0 }` | <a href="../data/responses/response_16.json">Response</a> | 200 |

&emsp;**3.2. Corner cases**
| ID | Description | Request                         | Expexted result | HTTP status |
|----|-------------|---------------------------------|:---------------:|:-----------:|
| 3.2.1 | <p align="justify">Verify empty array is returned when having<br>same "origin" and "destination"</p> | `{ "origin": "SOF",`<br>`  "destination": "SOF" }` | <a href="../data/responses/response_17.json">Response</a> | 200 |
| 3.2.2 | <p align="justify">Value for parameter "maxFlights" smaller<br>than `<uint32_t>` max capacity</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": 1000000 }` | <a href="../data/responses/response_18.json">Response</a> | 200 |
| 3.2.3 | <p align="justify">Value for parameter "maxFlights" equals<br>to `<uint32_t>` max capacity</p> | `{ "origin": "SOF",`<br>`  "destination": "MLE",`<br>`  "maxFlights": 4294967295 }` | <a href="../data/responses/response_19.json">Response</a> | 200 |

### 4. Performance
&emsp;**4.1. Large number of routes**
| ID | Description | Request                         | Expexted result | HTTP status |
|----|-------------|---------------------------------|:---------------:|:-----------:|
| 4.1.1 | <p align="justify">Create a network with many possible routes between<br>two cities. Response time should be reasonable (e.g. < 5s).</p> | `{"origin": "SOF",`<br>` "destination": "ZRH" }` | <a href="../data/responses/response_20.json">Response</a><br><a href="./images/response_20.png">Performance</a> | 200 |
