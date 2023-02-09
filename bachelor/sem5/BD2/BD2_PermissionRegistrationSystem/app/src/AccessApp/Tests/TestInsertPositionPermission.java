package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestInsertPositionPermission extends Test{
    static boolean run() {
        connect();
        boolean success = true;


        PreparedStatement statement = null;
        ResultSet rs = null;
        try {

            insertPositionPermission(perm1Id, pos3Id, pos3);

            statement = conn.prepareStatement("SELECT count(*) FROM uprawnienia_stanowisk WHERE rodzaj_uprawnienia_ID=?");
            statement.setInt(1, perm1Id);
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 1) {
                throw (new Exception("Nie udało się nadać uprawnienia stanowisku!"));
            }


            statement = conn.prepareStatement("SELECT count(*) FROM uprawnienia_pracownikow WHERE rodzaj_uprawnienia_ID=?");
            statement.setInt(1, perm1Id);
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 2) {
                throw (new Exception("Nie udało się nadać uprawnienia pracownikom na stanowisku(trigger zawiódł)!"));
            }

            statement.close();
        } catch (Exception e) {
            e.printStackTrace();
            success = false;
        } finally {
            disconnect();

        }
        return success;
    }
}
