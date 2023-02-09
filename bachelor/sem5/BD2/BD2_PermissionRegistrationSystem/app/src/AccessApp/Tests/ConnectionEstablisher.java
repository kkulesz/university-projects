package AccessApp.Tests;

import java.sql.*;

public class ConnectionEstablisher
{
    private static String url = "jdbc:oracle:thin:@localhost:1521:xe";
    private static String nickname = "c##bd_acc";
    private static String password = "haslo";

    public static Connection establish() throws SQLException {
        return DriverManager.getConnection(url, nickname, password);
    }

    public static void disconnect(Connection conn) throws SQLException {
        conn.close();
    }

}
