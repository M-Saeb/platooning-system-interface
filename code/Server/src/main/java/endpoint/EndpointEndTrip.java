package endpoint;

import com.sun.net.httpserver.HttpExchange;
import org.json.JSONObject;

import endpoint.abstractEndpoint.AbstractEndpoint;
import services.Services;


public class EndpointEndTrip extends AbstractEndpoint{

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
        Services.setTripToDone(tripId);;
        JSONObject response = new JSONObject();
        response.put("result", true);
        this.sendResponse(exchange, 200, response.toString());
    }

}
