package data;

import java.util.ArrayList;
import java.util.HashMap;
import data.type.Trip;

public class DataStore {
    private static ArrayList<String> masterVehicleIds = new ArrayList<String>();
    private static ArrayList<String> slaveVehicleIds = new ArrayList<String>();
    private static HashMap<String, Trip> trips = new HashMap<String, Trip>();

    private DataStore() {}

    public static void addMasterVehcileId(String id){
        masterVehicleIds.add(id);
    }

    public static void addSlaveVehcileId(String id){
        slaveVehicleIds.add(id);
    }

    public static boolean mastervehicleIdExist(String id){
        return masterVehicleIds.indexOf(id) >= 0;
    }

    public static ArrayList<String> getAllMasterVehicleIds(){
        return masterVehicleIds;
    }

    public static void addTrip(Trip trip){
        trips.put(trip.getTripId(), trip);
    }
}
