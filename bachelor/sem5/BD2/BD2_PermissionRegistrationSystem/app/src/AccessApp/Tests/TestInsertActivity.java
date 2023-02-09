package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestInsertActivity extends Test{
    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{

            insertActivity(act1, perm1Id);
            insertActivity(act2, perm2Id);

            statement = conn.prepareStatement("SELECT count(*) FROM czynnosci");
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 2){
                throw(new Exception("Nie udało się dodać aktywności!"));
            }

//            if(insertActivity(act1, perm1Id)){
//                throw(new Exception("Zudplikowano aktywnosć"));
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
