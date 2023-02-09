package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestInsertPermissionKind extends Test{
    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{

            insertPermissionKind(perm1);
            insertPermissionKind(perm2);

            statement = conn.prepareStatement("SELECT count(*) FROM rodzaje_uprawnien");

            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 2){
                throw(new Exception("Nie udało się dodać rodzjów uprawnień!"));
            }

//            if(insertPermissionKind(perm1)){
//                throw(new Exception("Zduplikowano rodzaj uprawnienia!"));
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
