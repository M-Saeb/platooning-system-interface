### Messaging Format

One possible way to apply pthreads is by making 2 HTTP servers (one for master and one for slave)

the default template for the request is:
```json
{
    // the registered id of the client (if defined)
    "clientID": "aabbccdd", 
    // any spacial params that you want to pass to the server can be done here
    "params": { 
        "key": "value"
    },
    // the name of the action you want from the server
    "action": "actionUniqueName"
}
```

the response is 
```json
{
    // the name of the action used on the request
    "action": "actionUniqueName",
    // the response can be String, integer or any other knowen value type.
    // it defers based on the requested action
    "result": "The requested value"
}
```

### Defined Actions
- **generateID**
    ```json
    {
        "clientID": null,
        "params": {
            "clientType": "master" // or "slave"
        },
        "action": "generateID"
    }
    ```
    reponse 
    ```json
    {
        "action": "generateID",
        "result": "AABBCCDD" // this ID should be used for each call now
    }
    ```

- **createTrip**
    - This call must be made by a master vehicle
    - It'll create a trip on the server and link the master vehicle to it
    ```json
    {
        "clientID": "AABBCCDD",
        "action": "CreateTrip",
    }
    ```

    reponse 
    ```json
    {
        "action": "CreateTrip",
        "result": "TRIP_0001" // this ID should be used for each call now
    }
    ```

- **linkToTrip**
    - This call must be made by a slave vehicle with a `clientID` and a `tripID` defined
    - It'll be used link the slave vehcile to the created trip on the server
    ```json
    {
        "clientID": "AABBCCDD",
        "params": {
            "tripID": "TRIP_0001",
        },
        "action": "linkToTrip",
    }
    ```

    reponse 
    ```json
    {
        "action": "linkToTrip",
        // returns 'true' of all is good, else it returns a string with the exceptions
        "result": true 
    }
    ```

- **endTrip**
    - This call must be made by a master vehicle with a `clientID` and a `tripID` defined
    - It'll end the thread for the trip with the `tripID`
    ```json
    {
        "clientID": "AABBCCDD",
        "params": {
            "tripID": "TRIP_0001",
        },
        "action": "endTrip",
    }
    ```

    reponse 
    ```json
    {
        "action": "endTrip",
        // returns 'true' of all is good, else it returns a string with the exceptions
        "result": true 
    }
    ```

- **SendLocation**
    - This call must be made by a master vehicle with a `clientID`, a `tripID` and a `latitude` and `longitude` defined
    ```json
    {
        "clientID": "AABBCCDD",
        "params": {
            "latitude": 22.222,
            "longitude": 11.111,
        },
        "action": "SendLocation",
    }
    ```

    reponse 
    ```json
    {
        "action": "SendLocation",
        // returns 'true' of all is good, else it returns a string with the exceptions
        "result": true
    }
    ```

- **GetMasterPath**
    - This call must be made by a slave vehicle with a `clientID`, a `tripID` and i's current `latitude` and `longitude` defined
    ```json
    {
        "clientID": "AABBCCDD",
        "params": {
            "latitude": 22.222,
            "longitude": 11.111,
        },
        "action": "GetMasterPath",
    }
    ```

    reponse 
    ```json
    {
        "action": "GetMasterPath",
        // it'll recieve an array of locations for the same path that the master has taken
        "result": [
            [22.222, 11.111],
            [22.000, 11.111],
            [22.000, 11.333],
            [21.000, 11.333],
        ]
    }
    ```

