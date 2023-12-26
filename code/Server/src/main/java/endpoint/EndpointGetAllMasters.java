package endpoint;

import com.sun.net.httpserver.HttpExchange;
import java.util.ArrayList;

import endpoint.abstractEndpoint.AbstractEndpoint;
import services.Services;


public class EndpointGetAllMasters extends AbstractEndpoint{

    @Override
    public void handleRequest(HttpExchange exchange) throws Exception {
        if(
            !exchange.getRequestMethod().equalsIgnoreCase("GET")
        ){
            this.sendResponse(exchange, 405, "only GET Method is allowed");
            return;
        }
        ArrayList<String> newId = Services.getAllMasterVehicleIds();
        this.sendResponse(exchange, 200, newId.toString());
    }

}
