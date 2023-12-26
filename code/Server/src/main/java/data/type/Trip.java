package data.type;

import java.util.ArrayList;


public class Trip {
    private String tripId;
    private String masterVehicleId;
    private boolean isDone = false;
    private ArrayList<String> slaveVehicleIds = new ArrayList<String>();
    private ArrayList<Location> tripPath = new ArrayList<Location>();

    public Trip(String tripId, String masterVehicleId){
        this.tripId = tripId;
        this.masterVehicleId = masterVehicleId;
    }

    public ArrayList<String> getSlaveVehicleIds(){
        return this.slaveVehicleIds;
    }

    public String getTripId(){
        return this.tripId;
    }

    public boolean isIsDone(){
        return this.isDone;
    }

    public ArrayList<Location> getFulltripPath(){
        return this.tripPath;
    }

    public void addSlaveVehicle(String slaveVehicleId){
        this.slaveVehicleIds.add(slaveVehicleId);
    }

    public void addLocationToTrip(Location location){
        this.tripPath.add(location);
    }

    public void setToDone(){
        this.isDone = true;
    }
}
