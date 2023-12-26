package endpoint.abstractEndpoint;

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


public abstract class AbstractEndpoint implements HttpHandler{

    @Override
    public void handle(HttpExchange exchange) throws IOException {
        try {
            this.handleRequest(exchange);
        }catch (Exception e){
            this.sendResponse(exchange, 400, e.getMessage());
        }
    }

    /**
     * Override this method to implement your custom logic
     * @param exchange
     * @throws IOException
     * @throws JSONException
     */
    public abstract void handleRequest(HttpExchange exchange) throws Exception;

    /**
     * Return a JSON object from the request's body of the HttpExchange instance
     * @param exchange
     * @return
     * @throws IOException
     */
    public JSONObject getRequestBodyAsJson(HttpExchange exchange) throws IOException {
        Headers requestHeaders = exchange.getRequestHeaders();
        if (
            !requestHeaders.containsKey("Content-Type") ||
            !requestHeaders.getFirst("Content-Type").equalsIgnoreCase("application/json")
        ){
            throw new IOException("You need to set content type to application/json");
        }

        try{
            BufferedReader reader = new BufferedReader(new InputStreamReader(exchange.getRequestBody()));
            String requestBody = reader.lines().collect(Collectors.joining("\n"));
            return new JSONObject(requestBody);
        } catch (JSONException e){
            throw new IOException("The request's body is not valid JSON format");
        }
    }

    /**
     * 
     * @param exchange
     * @param statusCode
     * @param response
     * @throws IOException
     */
    public void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
        exchange.sendResponseHeaders(statusCode, response.length());
        OutputStream os = exchange.getResponseBody();
        os.write(response.getBytes());
        os.close();
    }

    private Object getValueFromJSONObject(JSONObject body, String key) throws IOException{
        Object value;
        try{
            value = body.get(key);
        } catch(JSONException e ){
            throw new IOException(key + " key is not present");
        }        
        return value;
    }

    public String getStringOrThrowException(JSONObject body, String key) throws IOException{
        Object value = this.getValueFromJSONObject(body, key);
        if (!(value instanceof String)){
            throw new IOException(key +" Must Be String");
        }
        return (String)value;
    }

    public double getDoubleOrThrowException(JSONObject body, String key) throws IOException{
        String value = this.getValueFromJSONObject(body, key).toString();
        try{
            return Double.parseDouble(value);
        } catch (Exception e){
            throw new IOException(key + " Must Be Number");
        }
    }
}
