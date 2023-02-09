package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

/**
 * Checks whether we can add an employee
 */
public class TestInsertEmployee extends Test{
    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{
            insertEmployee(emp1Id, name1, sur1);
            insertEmployee(emp2Id, name2, sur2);
            insertEmployee(emp3Id, name3, sur3);
            insertEmployee(emp4Id, name4, sur4);

            statement = conn.prepareStatement("SELECT count(*) FROM pracownicy");

            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 4){
                throw(new Exception("Dodawanie pracownika"));
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
