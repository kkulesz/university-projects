package AccessApp.Tests;

import java.sql.Connection;
import java.sql.PreparedStatement;

public class Test {
    protected static Connection conn;
    protected static boolean connect(){
        try {
            conn = ConnectionEstablisher.establish();
            conn.setAutoCommit(true);
        }catch(Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    protected static boolean disconnect() {
        try {
            ConnectionEstablisher.disconnect(conn);
        }catch(Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }


    //dzial
    protected static boolean insertDepartment(String dep){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO dzialy(nazwa) VALUES (?)");
            statement.setString(1, dep);

            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    //rozdaj uprawnienia
    protected static boolean insertPermissionKind(String per){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO rodzaje_uprawnien(nazwa, liczba_uprawnien) VALUES (?,?)");
            statement.setString(1, per);
            statement.setInt(2, 0);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            //e.printStackTrace();
            return false;
        }
        return true;
    }

    //stanowisko
    protected static boolean insertPosition(String pos, int depId){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO stanowiska(nazwa, dzial_id) VALUES (?,?)");
            statement.setString(1, pos);
            statement.setInt(2, depId);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            //e.printStackTrace();
            return false;
        }
        return true;
    }

    //uprawnienia stanowiska
    protected static boolean insertPositionPermission(int permId, int posId, String pos){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO uprawnienia_stanowisk" +
                    "(rodzaj_uprawnienia_id, stanowisko_id, rodzaj_uprawnienia_nazwa) VALUES (?, ?, ?)");
            statement.setInt(1, permId);
            statement.setInt(2, posId);
            statement.setString(3, pos);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    //pracownik
    protected static boolean insertEmployee(int id, String name, String surname){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO pracownicy(id, imie, nazwisko) VALUES (?, ?, ?)");
            statement.setInt(1, id);
            statement.setString(2, name);
            statement.setString(3, surname);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    //konto pracownika
    protected static boolean insertEmployeeAcc(int id, int empId, String login, String pass, int posId, String name, String surname, String posName){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO konta_pracownikow" +
                    "(ID_konta, Pracownik_ID, Login, Haslo, Stanowisko_ID, Imie, Nazwisko, Stanowisko_nazwa) VALUES " +
                    "(?, ?, ?, ?, ?, ?, ?, ?)");
            statement.setInt(1, id);
            statement.setInt(2, empId);
            statement.setString(3, login);
            statement.setString(4, pass);
            statement.setInt(5, posId);
            statement.setString(6, name);
            statement.setString(7, surname);
            statement.setString(8, posName);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            //e.printStackTrace();
            return false;
        }
        return true;
    }

    protected static boolean insertEmployeePermission(int empAccId, int permId, boolean auto, int posId, String pos){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO Uprawnienia_pracownikow" +
                    "(Konto_pracownika_ID_konta, Rodzaj_uprawnienia_ID, Nadane_automatycznie, Stanowisko_ID, Rodzaj_uprawnienia_nazwa) VALUES " +
                    "(?, ?, ?, ?, ?)");
            statement.setInt(1, empAccId);
            statement.setInt(2, permId);
            statement.setBoolean(3, auto);
            statement.setInt(4, posId);
            statement.setString(5, pos);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    protected static boolean insertActivity(String name, int permId){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("INSERT INTO czynnosci" +
                    "(nazwa_czynnosci, rodzaj_uprawnienia_id) VALUES " +
                    "(?, ?)");
            statement.setString(1, name);
            statement.setInt(2, permId);

            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    protected static boolean insertActivityPerformenceHistory(int actId, int permId, int accId){
        PreparedStatement statement = null;
        //String date = "";
        String status = "dokończono";

        try{
            statement = conn.prepareStatement("INSERT INTO historie_wykonania_czynnosci" +
                    "(data, status_wykonania, czynnosc_numer, rodzaj_uprawnienia, konto_pracownika_ID_konta) VALUES " +
                    "(TO_CHAR(SYSDATE, 'DD-MON-YYYY'), ?, ?, ?, ?)");
            //statement.setString(1, date);
            statement.setString(1, status);
            statement.setInt(2, actId);
            statement.setInt(3, permId);
            statement.setInt(4, accId);


            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    protected static boolean deletePositionPermission(int permId, int posId){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("DELETE FROM uprawnienia_stanowisk " +
                    "WHERE rodzaj_uprawnienia_id=? AND stanowisko_id=?");
            statement.setInt(1, permId);
            statement.setInt(2, posId);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    protected static boolean deleteEmployeePermission(int permId, int accId){
        PreparedStatement statement = null;
        try{
            statement = conn.prepareStatement("DELETE FROM Uprawnienia_pracownikow " +
                    "WHERE Konto_pracownika_ID_konta=? AND Rodzaj_uprawnienia_ID=?");
            statement.setInt(1, accId);
            statement.setInt(2, permId);
            statement.executeQuery();
            statement.close();
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }







    static String dep1 = "Dev";
    static int dep1Id = 1;

    ////////////////////////////////////
    static String perm1 = "uje",
            perm2 = "essa";
    static int perm1Id = 1,
            perm2Id = 2;
    ////////////////////////////////////
    static String pos1 = "boss",
            pos2 = "nie_boss",
            pos3 = "na_pewno_nie_boss";
    static int pos1Id = 1,
            pos2Id = 2,
            pos3Id = 3;
    ////////////////////////////////////
    static String name1 = "Kuba",
            name2 = "Igor",
            name3 = "Bartek",
            name4 = "Konrad";
    static String sur1 = "Gie",
            sur2 = "Ka",
            sur3 = "Be",
            sur4 = "Ku";
    static int emp1Id = 1,
            emp2Id = 2,
            emp3Id = 3,
            emp4Id = 4;
    /////////////////////////////////////
    static String log1 = "log1",
            log2 = "log2",
            log3 = "log3",
            log4 = "log4";

    static String pas1 = "pas1",
            pas2 = "pas2",
            pas3 = "pas3",
            pas4 = "pas4";

    static int acc1Id = 1,
            acc2Id = 2,
            acc3Id = 3,
            acc4Id = 4;
    //////////////////////////////////////
    static String act1 = "kodzenie po nocach",
            act2= "księgowanie";
    static int act1Id = 1,
                act2Id = 2;


}
