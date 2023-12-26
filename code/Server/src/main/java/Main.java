import com.sun.net.httpserver.HttpServer;

import endpoint.*;

import java.net.InetSocketAddress;
import java.io.IOException;
// import java.util.concurrent.ThreadPoolExecutor;
// import java.util.concurrent.Executors;

public class Main {

    public static void main(String[] args){
        HttpServer server;
        try{
           server = HttpServer.create(new InetSocketAddress("localhost", 8081), 0);
        } catch (IOException e){
            System.out.println("<=== IOException Occured ===>");
            e.printStackTrace();
            return;
        }

        // ThreadPoolExecutor threadPoolExecutor = (ThreadPoolExecutor)Executors.newFixedThreadPool(10);
        // server.setExecutor(threadPoolExecutor);
        
        server.createContext("/generate-id", new EndpointGenerateID());
        server.createContext("/get-id", new EndpointGetAllMasters());
        server.createContext("/create-trip", new EndpointCreateTrip());
        server.createContext("/link-to-trip", new EndpointLinkToTrip());
        server.createContext("/end-trip", new EndpointEndTrip());
        server.createContext("/update-master-location", new EndpointUpdateMasterLocation());
        server.createContext("/get-master-location", new EndpointGetMasterPath());

        server.start();
        System.out.println(" Server started on port 8001");
    }


}
