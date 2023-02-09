package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestLogActivities extends Test{

    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{

            insertActivityPerformenceHistory(act2Id, perm2Id, acc2Id);

            statement = conn.prepareStatement("SELECT count(*) FROM historie_wykonania_czynnosci");
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 1){
                throw(new Exception("Nie udało się zapisywać czynności!"));
            }

//            if(insertActivityPerformenceHistory(act2Id, perm2Id, acc1Id)){
//                throw(new Exception("Nie uwzględniono pozwolenia"));
//            }

            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            success = false;
        }finally {
            disconnect();

        }
        return success;
    }
}
