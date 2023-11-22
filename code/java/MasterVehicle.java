import java.util.Random;
import java.util.ArrayList;

public class MasterVehicle 
{ 
  private ArrayList<SlaveVehicle> slaves;
  private Server server;
  private Boolean showStopSign;

  Double getLongitude()
  {
    Random random = new Random();
    Double value = random.nextDouble();
    return value;
  }
  
  Double getLatitude()
  {
    Random random = new Random();
    Double value = random.nextDouble();
    return value;
  }

  public void addSlaveVehicle(SlaveVehicle slave){
    this.slaves.add(slave);
    System.out.println("Added slave numbered " + slave.number + " to master");
  }

  public MasterVehicle(Server server){
    this.showStopSign = false;
    this.server = server;
    this.slaves = new ArrayList<SlaveVehicle>();
  }

  public void upddateLocation(){
    // Send the current location to the server
    Double longitude = this.getLongitude();
    Double latitude = this.getLatitude();
    Double currentLocation[]  = {longitude, latitude};
    this.server.addNewLocation(currentLocation);
  }

  public void setShowStopSignal(boolean newValue){
    if (newValue){
      System.out.println("Show the stop sign for master !!");
    } else {
      System.out.println("Hide the stop sign for master");
    }
    this.showStopSign = newValue;
  }

  public void accelerate(Double speed){
    System.out.println("The master accelerated by " + speed);
    for(SlaveVehicle slave: this.slaves){
      slave.accelerate(speed);
    }
  }
  
  public void steer(Double steeringAngle){
    System.out.println("The master Steered by angle " + steeringAngle);
    for(SlaveVehicle slave: this.slaves){
      slave.steer(steeringAngle);
    }
  }

 public void getbreakPreassure(Double breakPreassure){
    System.out.println("The master break pressure " + breakPreassure);
    for(SlaveVehicle slave: this.slaves){
      slave.pressBreak(breakPreassure);
    }
  }

 public void pingAllSlaves(){
  boolean exceptionRaised = false;
  for (SlaveVehicle slave: this.slaves){
    try{
      this.pingSlave(slave);
      slave.setState(SlaveState.COUPLED);
    } catch (SlaveNotReachable e){
      this.decoubleSlave(slave);
      exceptionRaised = true;
    }
  }
  if (!exceptionRaised){
    this.setShowStopSignal(false);
  }
 }

  public void decoubleSlave(SlaveVehicle slave){
    slave.setState(SlaveState.DECOUPLED);
    this.setShowStopSignal(true);
  }

 private void pingSlave(SlaveVehicle slave) throws MasterVehicle.SlaveNotReachable{
  boolean isReachable = slave.getTestPingState();
  if (!isReachable){
    throw new SlaveNotReachable(
      "The slave " + slave.number + " is not reachable"
    );
  }
 }

 private class SlaveNotReachable extends Exception{
  public SlaveNotReachable(){
    super();
  }
  public SlaveNotReachable(String message){
    super(message);
  }
 }

}