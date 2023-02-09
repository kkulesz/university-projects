package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestLogGrantingPermissions extends Test {
    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{

            //insertActivityPerformenceHistory(act2Id, perm2Id, acc2Id);

            statement = conn.prepareStatement("SELECT count(*) FROM historie_nadania_uprawnien");
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 3){
                throw(new Exception("Nie zapisano nadania uprawnienia!"));
            }

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
