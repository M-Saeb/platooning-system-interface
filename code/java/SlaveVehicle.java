import java.util.ArrayList;

enum SlaveState{
    COUPLED,
    DECOUPLED
}

public class SlaveVehicle {
    public String number;
    private SlaveState state;
    private double timeDelay;
    private Double minDistance;
    private Server server;
    private MasterVehicle master;
    private boolean testPingState = true;

    public boolean getTestPingState(){
        return this.testPingState;
    }

    public void setTestPingState(boolean newValue){
        this.testPingState = newValue;
    }

    public SlaveVehicle(
        String number, double timeDelay,
        Double minDistance, Server server,
        MasterVehicle master
    ){
        this.number = number;
        this.state = SlaveState.DECOUPLED;
        this.timeDelay = timeDelay;
        this.minDistance = minDistance;
        this.server = server;
        this.master = master;
    }

    public SlaveState getState(){
        return this.state;
    }

    public void setState(SlaveState newState){
        System.out.println(
            "The slave numbered " + this.number + " is updated to " + newState +
            " in slave"
        );
        this.state = newState;
    }

    void accelerate(Double speed){
        System.out.println("The slave with number " + this.number + " Accelerated By " + speed);
    }

    void steer(Double degree){
        System.out.println("The slave with number " + this.number +  " Steered at degree of " + degree);
    }

    void pressBreak(Double pressure){
        System.out.println("The slave with number " + this.number + " Pressed brakes on the vehicle with pressure of " + pressure);
    }

    public void sensorBreak(){
        System.out.println("The slave with number " + this.number + " Pressed sensor brakes on the vehicle");
        this.sendDecoupledSignal();
    }

    void sendDecoupledSignal(){
        System.out.println("The slave with number " + this.number + " decoupled");
        this.state = SlaveState.DECOUPLED;
        this.master.decoubleSlave(this);
    }

    public void autoDrive(){
        this.server.getMasterPath();
         System.out.println("Auto drive is ON for slave " + this.number);
    }


}
