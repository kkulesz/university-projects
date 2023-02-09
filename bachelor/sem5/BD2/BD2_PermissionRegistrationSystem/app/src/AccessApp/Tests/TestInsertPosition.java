package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

/**
 * add position
 * unique position name in a department
 */
public class TestInsertPosition extends Test{
    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{

            insertPosition(pos1, dep1Id);
            insertPosition(pos2, dep1Id);
            insertPosition(pos3, dep1Id);


            statement = conn.prepareStatement("SELECT count(*) FROM stanowiska");

            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 3){
                throw(new Exception("Dodawanie stanowiska!"));
            }

            if(insertPosition(pos1, dep1Id)){
                throw(new Exception("Zduplikowana nazwa stanowiska w dziale!"));
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
