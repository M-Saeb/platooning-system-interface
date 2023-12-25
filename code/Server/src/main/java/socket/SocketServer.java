package socket;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class SocketServer extends ServerSocket{

    private ArrayList<ClientSocketHandler> clientHandlers = new ArrayList<ClientSocketHandler>();

    public SocketServer(int port) throws IOException {
        super(port);

    }

    public void startServer() {
        System.out.println("Server started. Waiting for clients...");

        while (true) {
            Socket s;
            try{
                s = this.accept();
                // clientSocket = new ClientSocket(s); // Accept incoming client connection
            }
            catch (IOException e) {
                e.printStackTrace();
                continue;
            }

            try {
                this.addClient(s);
            } catch (Exception e) {
                this.clientHandlers.remove(s);
                e.printStackTrace();
            }
        }
    }

    public void addClient(Socket s){
        try{
            System.out.println("Client connected: " + s);
            ClientSocketHandler clientHandler = new ClientSocketHandler(s, this);
            this.clientHandlers.add(clientHandler);
            new Thread(clientHandler).start();
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    public void removeClient(Socket s){
        this.clientHandlers.remove(s);
    }
}
