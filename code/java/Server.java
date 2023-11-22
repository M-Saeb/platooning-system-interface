import java.util.ArrayList;

public class Server{

  private ArrayList<Double[]>  pointsHistory = new ArrayList<Double[]>();

  void addNewLocation(Double location[]){

    pointsHistory.add(location);
    System.out.println(
      "Updated current location of master to server: "
      + location[0] + ", " + location[1]
    );

  }

  public ArrayList<Double[]> getMasterPath(){
    System.out.println("Master path is requested from the server");
    return this.pointsHistory;
  }

}
