


public class Main{
    public static void main(String args[]){
        Server server = new Server();
        MasterVehicle master = new MasterVehicle(server);
        SlaveVehicle slave01 = new SlaveVehicle(
            "A01", 0.5, 5.0, server, master
        );
        SlaveVehicle slave02 = new SlaveVehicle(
            "B02", 1.0, 5.0, server, master
        );
        SlaveVehicle slave03 = new SlaveVehicle(
            "C03", 1.5, 5.0, server, master
        );
        master.addSlaveVehicle(slave01);
        master.addSlaveVehicle(slave02);
        master.addSlaveVehicle(slave03);

        System.out.println("=== Second 1 ===");
        master.upddateLocation();
        master.pingAllSlaves();
        master.accelerate(20.0);

        System.out.println("=== Second 2 ===");
        master.upddateLocation();
        master.pingAllSlaves();
        master.steer(30.0);
        slave03.sensorBreak();
        master.getbreakPreassure(80.0);

        System.out.println("=== Second 3 ===");
        master.upddateLocation();
        slave03.autoDrive();

        System.out.println("=== Second 3 ===");
        master.pingAllSlaves();
    }
}