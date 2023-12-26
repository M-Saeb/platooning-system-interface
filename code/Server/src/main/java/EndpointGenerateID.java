import com.sun.net.httpserver.HttpExchange;
import org.json.JSONObject;
import org.json.JSONException;

import endpoint.AbstractEndpoint;

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

        Object clientType;
        try{
            clientType = requestBody.get("clientType");
        } catch(JSONException e ){
            this.sendResponse(exchange, 400, "clientType key is not present");
            return;
        }

        if (!(clientType instanceof String)){
            this.sendResponse(exchange, 400, "client Type Must Be String");
        }

        this.sendResponse(exchange, 200, requestBody.toString());
    }

}
