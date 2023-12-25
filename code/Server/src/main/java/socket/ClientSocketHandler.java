package socket;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.net.Socket;

/**
 * This class acts turn sockets into a thread in a managable way
 */
public class ClientSocketHandler implements Runnable {

    private final Socket socket;
    private final SocketServer server;
    private final BufferedReader bufferReader;
    private final BufferedWriter bufferWriter;

    public ClientSocketHandler(Socket socket, SocketServer server) throws IOException {
        this.socket = socket;
        this.server = server;
        this.bufferReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.bufferWriter = new BufferedWriter(new OutputStreamWriter( socket.getOutputStream()));
    }

    // Send a message to this client
    public void sendMessage(String message) throws IOException {
        System.out.println("Send message: " + message);
        this.bufferWriter.write(message);
        this.bufferWriter.newLine();
        this.bufferWriter.flush();
    }


    @Override
    public void run() {
        try {
            while (!socket.isClosed()) {
                // Read incoming messages from the client
                String receivedMessage = bufferReader.readLine();
                if (receivedMessage != null) {
                    System.out.println("Received from client " + socket + ": " + receivedMessage);

                    // Echo the received message back to the client
                    // this.socket.sendMessage(receivedMessage);
                }
            }
        } catch (IOException e) {
            System.out.println("Client disconnected: " + socket);
            this.server.removeClient(this.socket);
            try {
                socket.close();
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }

}