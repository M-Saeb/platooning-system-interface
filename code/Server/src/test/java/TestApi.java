import java.io.IOException;

import java.util.ArrayList;
import java.util.HashMap;

import org.json.JSONObject;
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
        assertEquals(allTrips.size(), 1, "Should create only one mater");
        Trip responseTrip = (Trip)allTrips.values().toArray()[0];
        
        assertEquals(responseTrip.getSlaveVehicleIds().size(), 1);
        assertEquals(responseTrip.getSlaveVehicleIds().get(0), slaveId);

    }



    private void assertSuccessfullResponse(HttpResponse response){
        int statusCode = response.getStatusLine().getStatusCode();
        assertEquals(statusCode, 200);
    }

}
