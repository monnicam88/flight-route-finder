## Groups of Test Cases

### Group 1 - Basic Functionality Tests
&emsp;1.1. Find existing and missing routes: **`ID:1.1.1 - ID:1.1.4`**

### Group 2 - Input validation
&emsp;2.1. Missing mandatory parameters: **`ID:2.1.1 - ID:2.1.3`**  
&emsp;2.2. Invalid types of parameters: **`ID:2.2.1 - ID:2.1.5`**  
&emsp;2.3. Invalid JSON request format: **`ID:2.3.1`**

### Group 3 - Limitations on the maximum number of flights in a route
&emsp;3.1. Valid limitations: **`ID:3.1.1 - ID:3.1.3`**  
&emsp;3.2. Corner cases: **`ID:3.2.1 - ID:3.1.3`**  

### Group 4 - Performance
&emsp;4.1. Large number of routes: **`ID:4.1.1`**  

---
<table border="1" cellpadding="5" cellspacing="0">
  <thead>
    <tr>
      <th style="width: 5%;">ID</th>
      <th style="width: 40%;">Description</th>
      <th style="width: 10%;">Request</th>
      <th style="width: 40%;">Expected result</th>
      <th style="width: 5%;" align="center">HTTP status</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>1.1.1</td>
      <td><p align="justify">Verify that all possible routes from SOF to MLE are returned, sorted by price</p></td>
<td><pre>{
  "origin": "SOF",
  "destination": "MLE"
}</pre></td>
<td><pre>[
  {
    "route": [ "SOF", "LON", "MLE" ],
    "price": 30
  },
  {
    "route": [ "SOF", "MLE" ],
    "price": 70
  },
  {
    "route": [ "SOF", "IST", "CMB", "MLE" ],
    "price": 70
  }
]</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>1.1.2</td>
      <td><p align="justify">Verify that all possible routes from SOF to LON are returned, sorted by price</p></td>
<td><pre>{
  "origin": "SOF",
  "destination": "LON"
}</pre></td>
<td><pre>[
  {
    "route": [ "SOF", "LON" ],
    "price": 10
  }
]</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>1.1.3</td>
      <td><p align="justify">Verify a message is returned when no routes exist</p></td>
<td><pre>{
  "origin": "MLE",
  "destination": "SOF"
}</pre></td>
<td><pre>{
  "message": "There are no routes!"
}</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>1.1.4</td>
      <td><p align="justify">Verify a message is returned when having non-existent city codes</p></td>
<td><pre>{
  "origin": "MAL",
  "destination": "MLE"
}</pre></td>
<td><pre>{
  "message": "There are no routes!"
}</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>2.1.1</td>
      <td><p align="justify">Missing parameter "origin"</p></td>
<td><pre>{
  "destination": "MLE"
}</pre></td>
<td><pre>{
  "message": "Missing origin input!"
}</pre></td>
      <td align="center">400</td>
    </tr>
    <tr>
      <td>2.1.2</td>
      <td><p align="justify">Missing parameter "destination"</p></td>
<td><pre>{
  "origin": "SOF"
}</pre></td>
<td><pre>{
  "message": "Missing destination input!"
}</pre></td>
      <td align="center">400</td>
    </tr>
       <tr>
      <td>2.1.3</td>
      <td><p align="justify">Empty request body</p></td>
<td><pre>{}</pre></td>
<td><pre>{
  "message": "Missing origin input!"
}</pre></td>
      <td align="center">400</td>
    </tr> 
    <tr>
      <td>2.2.1</td>
      <td><p align="justify">Invalid type for parameter "origin"</p></td>
<td><pre>{ 
  "origin": 123,
  "destination": "MLE" 
}</pre></td>
<td><pre>{
  "message": "The input for origin is not"<a href="../data/responses/response_08.json">...</a>
}</pre></td>
      <td align="center">400</td>
    </tr> 
    <tr>
      <td>2.2.2</td>
      <td><p align="justify">Invalid type for parameter "destination"</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": 123 
}</pre></td>
<td><pre>{
  "message": "The input for destination is"<a href="../data/responses/response_09.json">...</a>
}</pre></td>
      <td align="center">400</td>
    </tr>
        <tr>
      <td>2.2.3</td>
      <td><p align="justify">Invalid type for parameter "maxFlights"</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": "two"
}</pre></td>
<td><pre>{
  "message": "The input for maxFlights is"<a href="../data/responses/response_10.json">...</a>
}</pre></td>
      <td align="center">400</td>
    </tr>
     <tr>
      <td>2.2.4</td>
      <td><p align="justify">Negative value for parameter "maxFlights"</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": -1
}</pre></td>
<td><pre>{
  "message": "The input for maxFlights is"<a href="../data/responses/response_11.json">...</a>
}</pre></td>
      <td align="center">400</td>
    </tr>
    <tr>
      <td>2.2.5</td>
      <td><p align="justify">Too big value for parameter "maxFlights"</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": 4294967296
}</pre></td>
<td><pre>{
  "message": "You have gone over the maximum"<a href="../data/responses/response_12.json">...</a>
}</pre></td>
      <td align="center">400</td>
    </tr>
    <tr>
      <td>2.3.1.</td>
      <td><p align="justify">Invalid JSON</p></td>
<td><pre>{ 
  "origin": SOF,
  "destination": MLE
}</pre></td>
<td><pre>{
  "message": "Unable to parse request body!"
}</pre></td>
      <td align="center">400</td>
    </tr>
    <tr>
      <td>3.1.1</td>
      <td><p align="justify">Maximum 1 flight (the direct flight only)</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": 1
}</pre></td>
<td><pre>[
  {
    "route": [ "SOF", "MLE" ],
    "price": 70
  }
]</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>3.1.2</td>
      <td><p align="justify">Maximum 2 flights</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": 2
}</pre></td>
<td><pre>[
  {
    "route": [ "SOF", "LON", "MLE" ],
    "price": 30
  }
]</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>3.1.3</td>
      <td><p align="justify">Maximum 0 flights</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": 0
}</pre></td>
<td><pre>{
  "message": "The input for maxFlights is"<a href="../data/responses/response_16.json">...</a>
}</pre></td>
      <td align="center">400</td>
    </tr>
    <tr>
      <td>3.2.1</td>
      <td><p align="justify">Verify a message is returned when having same "origin" and "destination"</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "SOF"
}</pre></td>
<td><pre>{
  "message": "The origin and destination"<a href="../data/responses/response_17.json">...</a>
}</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>3.2.2</td>
      <td><p align="justify">Value for parameter "maxFlights" smaller than <b>uint32_t</b> max capacity</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": 1000000
}</pre></td>
<td><pre>{
  "message": "There are no routes!"
}</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>3.2.3</td>
      <td><p align="justify">Value for parameter "maxFlights" equals to <b>uint32_t</b> max capacity</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "MLE",
  "maxFlights": 4294967295
}</pre></td>
<td><pre>{
  "message": "There are no routes!"
}</pre></td>
      <td align="center">200</td>
    </tr>
    <tr>
      <td>4.1.1</td>
      <td><p align="justify">Create a network with many possible routes between two cities. Response time should be reasonable (e.g. < 5s).</p></td>
<td><pre>{ 
  "origin": "SOF",
  "destination": "ZRH"
}</pre></td>
<td><pre>[
  {
    "route": [ "SOF", "ZRH" ],
    "price": 16
  },
  {
    "route": [ "SOF", "VIE", "ZRH" ],
    "price": 17
  },
  {
    "route": [ "SOF", "BER", "ZRH" ],
    "price": 21
  },<a href="../data/responses/response_20.json">...</a>
  <a href="./images/response_20.png">Performance</a></pre>
</td>
      <td align="center">200</td>
    </tr>
  </tbody>
</table>
