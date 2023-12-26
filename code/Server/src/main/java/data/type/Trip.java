package data.type;

import java.util.ArrayList;


public class Trip {
    private String tripId;
    private String masterVehicleId;
    private ArrayList<String> slaveVehicleIds = new ArrayList<String>();
    private ArrayList<Location> tripPath = new ArrayList<Location>();

    public Trip(String tripId, String masterVehicleId){
        this.tripId = tripId;
        this.masterVehicleId = masterVehicleId;
    }

    public String getTripId(){
        return this.tripId;
    }

    public void addSlaveVehicle(String slaveVehicleId){
        this.slaveVehicleIds.add(slaveVehicleId);
    }

    public void addLocationToTrip(Location location){
        this.tripPath.add(location);
    }
}
