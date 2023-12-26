package endpoint;

import java.util.ArrayList;
import com.sun.net.httpserver.HttpExchange;

import org.json.JSONArray;
import org.json.JSONObject;

import data.type.Location;
import endpoint.abstractEndpoint.AbstractEndpoint;
import services.Services;


public class EndpointGetMasterPath extends AbstractEndpoint{

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
        JSONObject response = new JSONObject();
        
        JSONArray resultedArray = new JSONArray();
        ArrayList<Location> path = Services.getMasterPath(tripId);
        for (Location location: path){
            JSONObject jsonPoint = new JSONObject()
            .put("longitude", location.longitude)
            .put("latitude", location.latitude);
            resultedArray.put(jsonPoint);
        }
        
        response.put("result", resultedArray);
        this.sendResponse(exchange, 200, response.toString());
    }

}
