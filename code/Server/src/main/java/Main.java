import socket.SocketServer;

public class Main {

    public static void main(String[] args){
        try {
            SocketServer server = new SocketServer(6666);
            server.startServer();
        }
        catch (Exception e) {
            e.printStackTrace();
            e.getMessage();
        }

    }


}
