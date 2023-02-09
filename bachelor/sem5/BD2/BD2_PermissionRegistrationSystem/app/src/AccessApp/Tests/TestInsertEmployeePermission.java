package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestInsertEmployeePermission extends Test{
    static boolean run() {
        connect();
        boolean success = true;


        PreparedStatement statement = null;
        ResultSet rs = null;
        try {

            insertEmployeePermission(acc2Id, perm2Id, false, pos1Id, pos1);

            statement = conn.prepareStatement("SELECT count(*) FROM uprawnienia_pracownikow WHERE rodzaj_uprawnienia_ID=?");
            statement.setInt(1, perm2Id);
            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 1) {
                throw (new Exception("Nie udało się nadać uprawnienia pracownikowi!"));
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
