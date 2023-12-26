import java.io.IOException;

import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;

import org.json.JSONObject;
import org.json.JSONArray;
import org.junit.jupiter.api.Test;
import org.apache.http.HttpEntity;
import org.apache.http.HttpHeaders;
import org.apache.http.HttpResponse;
import org.apache.http.entity.ContentType;
import org.apache.http.entity.StringEntity;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import data.DataStore;
import data.type.Location;
import data.type.Trip;
import services.Services;

public class TestApi {

    HttpClient httpClient = HttpClients.createDefault();

    private HttpPost setupHttpPost(String endpoint, JSONObject requestBody){
        HttpPost request = new HttpPost("http://localhost:8081/" + endpoint);
        request.setHeader(HttpHeaders.CONTENT_TYPE, "application/json");
        request.setHeader(HttpHeaders.ACCEPT, "application/json");
        StringEntity entity = new StringEntity(
            requestBody.toString(), ContentType.APPLICATION_JSON
        );
        request.setEntity(entity);
        return request;
    }

    private JSONObject getBodyFromResponse(HttpResponse response) throws IOException{
        HttpEntity responseEntity = response.getEntity();
        String responseString = EntityUtils.toString(responseEntity, "UTF-8");
        JSONObject responseOject = new JSONObject(responseString);
        return responseOject;
    }

    @Test
    public void testCreateMasterVehicleId() throws IOException{
        // setting up Server & client
        Main.main(null);

        JSONObject body = new JSONObject()
            .put("vehicleType", "master");
        HttpPost request = setupHttpPost("generate-id", body);
        HttpResponse response = httpClient.execute(request);

        assertSuccessfullResponse(response);

        ArrayList<String> allMasterVehicles = DataStore.getAllMasterVehicleIds();
        assertEquals(allMasterVehicles.size(), 1, "Should create only one master");

        JSONObject responseOject = getBodyFromResponse(response);
        String responseValue = (String)responseOject.get("result");
        assertEquals(responseValue, allMasterVehicles.get(0));
    }

    @Test
    public void testCreateSlaveVehicleId() throws IOException{
        // setting up Server & client
        Main.main(null);

        JSONObject body = new JSONObject()
            .put("vehicleType", "slave");
        HttpPost request = setupHttpPost("generate-id", body);
        HttpResponse response = httpClient.execute(request);

        assertSuccessfullResponse(response);

        ArrayList<String> allSlaveVehicles = DataStore.getAllSlaveVehicleIds();
        assertEquals(allSlaveVehicles.size(), 1, "Should create only one slave");

        JSONObject responseOject = getBodyFromResponse(response);
        String responseValue = (String)responseOject.get("result");
        assertEquals(responseValue, allSlaveVehicles.get(0));
    }

    @Test
    public void testCreateTrip() throws IOException{
        Main.main(null);

        String masterId = Services.generateMasterVehicleID();
        JSONObject body = new JSONObject()
            .put("masterId", masterId);
        HttpPost request = setupHttpPost("create-trip", body);
        HttpResponse response = httpClient.execute(request);

        assertSuccessfullResponse(response);

        HashMap<String, Trip> allTrips = DataStore.getTripsHashMap();
        assertEquals(allTrips.size(), 1, "Should create only one mater");

        JSONObject responseOject = getBodyFromResponse(response);
        String responseValue = (String)responseOject.get("result");
        assertEquals(responseValue, allTrips.keySet().toArray()[0]);
    }

    @Test
    public void testLinkSlaveToTrip() throws Exception{
        Main.main(null);

        String masterId = Services.generateMasterVehicleID();
        Trip requestTrip = Services.createTrip(masterId);
        String slaveId = Services.generateSlaveVehicleID();
        JSONObject body = new JSONObject()
            .put("slaveId", slaveId)
            .put("tripId", requestTrip.getTripId());

        HttpPost request = setupHttpPost("link-to-trip", body);
        HttpResponse response = httpClient.execute(request);

        assertSuccessfullResponse(response);

        JSONObject responseOject = getBodyFromResponse(response);
        boolean responseValue = (boolean)responseOject.get("result");
        assertTrue(responseValue);


        HashMap<String, Trip> allTrips = DataStore.getTripsHashMap();
        assertEquals(allTrips.size(), 1, "Should create only one trip");
        Trip responseTrip = (Trip)allTrips.values().toArray()[0];
        
        assertEquals(responseTrip.getSlaveVehicleIds().size(), 1);
        assertEquals(responseTrip.getSlaveVehicleIds().get(0), slaveId);
    }

    @Test
    public void testSettingTripToDone() throws Exception{
        Main.main(null);

        String masterId = Services.generateMasterVehicleID();
        Trip requestTrip = Services.createTrip(masterId);
        JSONObject body = new JSONObject()
            .put("tripId", requestTrip.getTripId());

        HttpPost request = setupHttpPost("end-trip", body);
        HttpResponse response = httpClient.execute(request);

        assertSuccessfullResponse(response);

        JSONObject responseOject = getBodyFromResponse(response);
        boolean responseValue = (boolean)responseOject.get("result");
        assertTrue(responseValue);


        HashMap<String, Trip> allTrips = DataStore.getTripsHashMap();
        assertEquals(allTrips.size(), 1, "Should have only one trip");
        Trip responseTrip = (Trip)allTrips.values().toArray()[0];
        
        assertTrue(responseTrip.isIsDone());
    }


    @Test
    public void testUpdateMasterLocation() throws Exception{
        Main.main(null);

        String masterId = Services.generateMasterVehicleID();
        Trip requestTrip = Services.createTrip(masterId);
        JSONObject body = new JSONObject()
            .put("tripId", requestTrip.getTripId())
            .put("longitude", 11.111)
            .put("latitude", 22.222);

        HttpPost request = setupHttpPost("update-master-location", body);
        HttpResponse response = httpClient.execute(request);

        assertSuccessfullResponse(response);

        JSONObject responseOject = getBodyFromResponse(response);
        boolean responseValue = (boolean)responseOject.get("result");
        assertTrue(responseValue);


        HashMap<String, Trip> allTrips = DataStore.getTripsHashMap();
        assertEquals(allTrips.size(), 1, "Should have only one trip");
        Trip responseTrip = (Trip)allTrips.values().toArray()[0];
        ArrayList<Location> path = responseTrip.getFulltripPath();
        assertEquals(path.size(), 1, "There should be only 1 point in the path now");
        assertEquals(path.get(0).longitude, 11.111);
        assertEquals(path.get(0).latitude, 22.222);
    }

    @Test
    public void testGetMasterPath() throws Exception{
        Main.main(null);

        String masterId = Services.generateMasterVehicleID();
        Trip requestTrip = Services.createTrip(masterId);
        requestTrip.addLocationToTrip(
            new Location(11.111, 22.222)
        );
        JSONObject body = new JSONObject()
            .put("tripId", requestTrip.getTripId());

        HttpPost request = setupHttpPost("get-master-location", body);
        HttpResponse response = httpClient.execute(request);

        assertSuccessfullResponse(response);

        JSONObject responseOject = getBodyFromResponse(response);
        Object responseValue = responseOject.get("result");
        if (!(responseValue instanceof JSONArray)){
            throw new Exception("The response should've been an array");
        }
        List listResponseValue = ((JSONArray)responseValue).toList();
        assertEquals(listResponseValue.size(), 1);
        HashMap responseValueItem = (HashMap)listResponseValue.get(0);
        assertEquals(
            responseValueItem.get("longitude").toString(), "11.111"
        );
        assertEquals(
            responseValueItem.get("latitude").toString(), "22.222"
        );
    }

    private void assertSuccessfullResponse(HttpResponse response){
        int statusCode = response.getStatusLine().getStatusCode();
        assertEquals(statusCode, 200);
    }

}
