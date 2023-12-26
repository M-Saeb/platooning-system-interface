package services;

import java.util.ArrayList;
import java.security.SecureRandom;
import data.DataStore;
import data.type.Trip;

public class Services {

    private static final String ALL_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";


    private static String generateRandomString(int length) {
        SecureRandom random = new SecureRandom();
        StringBuilder stringBuilder = new StringBuilder();

        for (int i = 0; i < length; i++) {
            int randomIndex = random.nextInt(ALL_CHARACTERS.length());
            char randomChar = ALL_CHARACTERS.charAt(randomIndex);
            stringBuilder.append(randomChar);
        }

        return stringBuilder.toString();
    }

    public static ArrayList<String> getAllMasterVehicleIds(){
        return DataStore.getAllMasterVehicleIds();
    }

    public static String generateMasterVehicleID(){
        String newId = "MST-" + generateRandomString(10);
        DataStore.addMasterVehcileId(newId);
        return newId;
    }

    public static String generateSlaveVehicleID(){
        String newId = "SLV-" + generateRandomString(10);
        DataStore.addSlaveVehcileId(newId);
        return newId;
    }

    public static Trip createTrip(String masterVehicleId) throws Exception{
        if (!DataStore.mastervehicleIdExist(masterVehicleId)){
            throw new Exception("The masterId " + masterVehicleId + " does not exist");
        }
        String tripId = "TRIP-" + generateRandomString(10);
        Trip trip = new Trip(tripId, masterVehicleId);
        DataStore.addTrip(trip);
        return trip;
    }
}
