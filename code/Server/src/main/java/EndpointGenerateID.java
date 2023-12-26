import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.IOException;
import java.util.stream.Collectors;
import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;
import org.json.JSONObject;
import org.json.JSONException;


public class EndpointGenerateID implements HttpHandler{

    @Override
    public void handle(HttpExchange exchange) throws IOException {
        if(
            !exchange.getRequestMethod().equalsIgnoreCase("POST")
        ){
            this.sendResponse(exchange, 405, "only POST Method is allowed");
            return;
        }
        Headers requestHeaders = exchange.getRequestHeaders();
        if (
            !requestHeaders.containsKey("Content-Type") ||
            !requestHeaders.getFirst("Content-Type").equalsIgnoreCase("application/json")
        ){
            this.sendResponse(exchange, 400, "You need to set content type to application/json");
            return;
        }
        JSONObject JSONrequestBody;
        try{
            JSONrequestBody = this.getRequestBodyAsJson(exchange);
        } catch (JSONException e){
            this.sendResponse(exchange, 400, "The request's body is not a valid JSON");
            return;            
        }

        Object clientType;
        try{
            clientType = JSONrequestBody.get("clientType");
        } catch(JSONException e ){
            this.sendResponse(exchange, 400, "clientType key is not present");
            return;
        }

        if (!(clientType instanceof String)){
            this.sendResponse(exchange, 400, "client Type Must Be String");
        }

        this.sendResponse(exchange, 200, JSONrequestBody.toString());
    }

    private JSONObject getRequestBodyAsJson(HttpExchange exchange) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
        String requestBody = reader.lines().collect(Collectors.joining("\n"));
        return new JSONObject(requestBody);
    }

    private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }
}
