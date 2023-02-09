package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

/**
 * Checks:
 * -add department
 * -unique department name constraint
 */
public class TestInsertDepartment extends Test{
    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{

            insertDepartment(dep1);

            statement = conn.prepareStatement("SELECT count(*) FROM dzialy WHERE nazwa=?");
            statement.setString(1, dep1);

            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 1){
                throw(new Exception("Nie udało się dodać działu!"));
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
