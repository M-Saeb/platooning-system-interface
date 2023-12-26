package endpoint;

import com.sun.net.httpserver.HttpExchange;

import org.json.JSONObject;

import data.type.Location;
import endpoint.abstractEndpoint.AbstractEndpoint;
import services.Services;


public class EndpointUpdateMasterLocation extends AbstractEndpoint{

    @Override
    public void handleRequest(HttpExchange exchange) throws Exception {
        if(
            !exchange.getRequestMethod().equalsIgnoreCase("POST")
        ){
            this.sendResponse(exchange, 405, "only POST Method is allowed");
            return;
        }
        JSONObject requestBody = this.getRequestBodyAsJson(exchange);
        String tripId = this.getStringOrThrowException(requestBody, "tripId");
        double longitude = this.getDoubleOrThrowException(requestBody, "longitude");
        double latitude = this.getDoubleOrThrowException(requestBody, "latitude");
        Location location = new Location(longitude, latitude);
        Services.updateLocationOnTrip(tripId, location);
        JSONObject response = new JSONObject();
        response.put("result", true);
        this.sendResponse(exchange, 200, response.toString());
    }

}
