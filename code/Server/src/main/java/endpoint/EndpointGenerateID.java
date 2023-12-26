package endpoint;

import java.io.IOException;
import com.sun.net.httpserver.HttpExchange;
import org.json.JSONObject;

import endpoint.abstractEndpoint.AbstractEndpoint;
import services.Services;

public class EndpointGenerateID extends AbstractEndpoint{

    @Override
    public void handleRequest(HttpExchange exchange) throws Exception {
        if(
            !exchange.getRequestMethod().equalsIgnoreCase("POST")
        ){
            this.sendResponse(exchange, 405, "only POST Method is allowed");
            return;
        }
        JSONObject requestBody = this.getRequestBodyAsJson(exchange);
        String vehicleType = this.getStringOrThrowException(requestBody, "vehicleType");
        if (!vehicleType.equals("master") && !vehicleType.equals("slave") ){
            throw new IOException("clientType Value must either be 'master' or 'slave'");
        }
        String newId;
        if (vehicleType.equals("master")){
            newId = Services.generateMasterVehicleID();
        } else { // slave
            newId = Services.generateSlaveVehicleID();
        }
        JSONObject response = new JSONObject();
        response.put("result", newId);
        // response.append("result", newId);
        this.sendResponse(exchange, 200, response.toString());
    }

}
