package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestLogRemovingPermissions extends Test {
    static boolean run(){
        connect();
        boolean success = true;



        PreparedStatement statement = null;
        ResultSet rs = null;
        try{
            deleteEmployeePermission(perm2Id, acc2Id);
            statement = conn.prepareStatement("SELECT count(*) FROM historie_nadania_uprawnien");
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 4){
                throw(new Exception("Nie zapisano usunięcia uprawnienia pracownika!"));
            }

            deletePositionPermission(perm1Id, pos3Id);
            statement = conn.prepareStatement("SELECT count(*) FROM historie_nadania_uprawnien");
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 6){
                throw(new Exception("Nie zapisano usunięcia uprawnienia stanowiska!"));
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
