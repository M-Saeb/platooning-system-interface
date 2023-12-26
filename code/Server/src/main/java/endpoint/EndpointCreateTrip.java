package endpoint;

import com.sun.net.httpserver.HttpExchange;

import org.json.JSONObject;

import endpoint.abstractEndpoint.AbstractEndpoint;
import data.type.Trip;
import services.Services;


public class EndpointCreateTrip extends AbstractEndpoint{

    @Override
    public void handleRequest(HttpExchange exchange) throws Exception {
        if(
            !exchange.getRequestMethod().equalsIgnoreCase("POST")
        ){
            this.sendResponse(exchange, 405, "only POST Method is allowed");
            return;
        }
        JSONObject requestBody = this.getRequestBodyAsJson(exchange);
        String masterId = this.getStringOrThrowException(requestBody, "masterId");
        Trip trip = Services.createTrip(masterId);
        JSONObject response = new JSONObject();
        response.put("result", trip.getTripId());
        this.sendResponse(exchange, 200, response.toString());
    }

}
