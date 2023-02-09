package ReportApp.Database;

import ReportApp.GUI.tools.Actions;
import ReportApp.GUI.tools.Departments;

import java.sql.*;
import java.util.ArrayList;

public class DatabaseHandler {
    private static String url = "jdbc:oracle:thin:@localhost:1521:xe";
    private static String nickname = "c##bd_acc";
    private static String password = "haslo";

    void add_permission() {

    }

    public static void main(String[] args) {

        try {
            Connection conn;
            conn = DriverManager.getConnection(url, nickname, password);
            String sql = "SELECT * FROM PRACOWNICY WHERE ID = ?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setInt(1, 20);
            ResultSet rs = statement.executeQuery();
            while (rs.next()) {
                int id = rs.getInt(1);
                String imie = rs.getString(2);
                String nazwisko = rs.getString(3);
                int przelozony = rs.getInt(4);
                System.out.println("id: " + id + "\nIMIE: " + imie + "\nnazwisko: " + nazwisko + "\nprzelozony: "
                        + przelozony);
            }

            // conn.close();
            int[][] months = new int[12][6];
            PreparedStatement ps = conn.prepareStatement("SELECT CZYNNOSC_NUMER, COUNT(ID)\n" +
                    "FROM HISTORIE_WYKONANIA_CZYNNOSCI\n" +
                    "WHERE EXTRACT(MONTH FROM DATA)=?\n" +
                    "GROUP BY CZYNNOSC_NUMER\n" +
                    "ORDER BY 1");
//            ps.setInt(1,3);
//            rs = ps.executeQuery();
//            while (rs.next())
//            {
//                System.out.println(rs.getInt(1));
//            }
            for (int i = 1; i <= 12; i++) {
                ps.setInt(1, i);
                rs = ps.executeQuery();
                int j = 0;
                while (rs.next()) {
//                    System.out.println(rs.getInt(1));
                    months[i - 1][j++] = rs.getInt(2);
                }
            }
            for (int i = 1; i <= 12; i++) {
                int max = 0;
                int maxIndex = 1;
                for (int j = 0; j < 6; j++) {
//                    System.out.print(months[i-1][j]+ " ");
                    if (months[i - 1][j] > max) {
                        max = months[i - 1][j];
                        maxIndex = j;
                    }

                }
                System.out.println("Najpopularniejsza w miesiacu " + i + "-tym czynnosc: " + maxIndex);
            }

            conn.close();


        } catch (Exception e) {
            //TODO: handle exception
        }


    }


    public String generateActionCounterReport(Boolean groupDepartments, Boolean onlyAction, Boolean onlyDepartment, String action, String department) {
        String result = "";


        PreparedStatement statement = null;
        Connection conn = null;
        ResultSet rs = null;
        try {
            conn = DriverManager.getConnection(url, nickname, password);
            String statementText = "";

            String whereString = "";
            String groupString = "GROUP BY cz.nazwa_czynnosci ";
            String selectSting = "SELECT cz.nazwa_czynnosci AS nazwa,COUNT(*) AS rowCount ";
            String orderString = "";

            if (groupDepartments) {
                selectSting = "SELECT dz.nazwa AS dzNazwa, cz.nazwa_czynnosci AS nazwa,COUNT(*) AS rowCount ";
                groupString = "GROUP BY dz.nazwa,cz.nazwa_czynnosci ";
                orderString = "ORDER BY dz.nazwa";
            }

            if (onlyAction && onlyDepartment) {
                whereString = "WHERE cz.nazwa_czynnosci = ? AND dz.nazwa = ? ";
            } else if (onlyAction) {
                whereString = "WHERE cz.nazwa_czynnosci = ? ";
            } else if (onlyDepartment) {
                whereString = "WHERE dz.nazwa = ? ";
            }


            statementText = selectSting +
                    "FROM Historie_wykonania_czynnosci h " +
                    "JOIN Czynnosci cz ON h.czynnosc_numer = cz.numer " +
                    "JOIN Konta_pracownikow kp ON h.konto_pracownika_id_konta = kp.id_konta " +
                    "JOIN Stanowiska st ON kp.stanowisko_id = st.id " +
                    "JOIN Dzialy dz ON st.dzial_id = dz.id " +
                    whereString +
                    groupString + orderString;
            System.out.println(statementText);
            statement = conn.prepareStatement(statementText);

            if (onlyAction && onlyDepartment) {
                statement.setString(1, action);
                statement.setString(2, department);
            } else if (onlyAction) {
                statement.setString(1, action);
            } else if (onlyDepartment) {
                statement.setString(1, department);
            }
            statement.executeQuery();

            rs = statement.getResultSet();

            System.out.println(rs);
            if(rs == null){
                result += "błąd";
                return result;
            }

            if(groupDepartments){
                while (rs.next()) {
                    result += rs.getString("dzNazwa");
                    result += ": ";
                    result += rs.getString("nazwa");
                    result += ": ";
                    result += rs.getInt("rowCount");
                    result += "\n";

                }
            }else{
                while (rs.next()) {
                    result += rs.getString("nazwa");
                    result += ": ";
                    result += rs.getInt("rowCount");
                    result += "\n";
                }
            }




            rs.close();
            statement.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return result;
    }

    public String generateEmployeePermissionReport(Boolean groupDepartments, Boolean onlyPermissionType, Boolean onlyDepartment, String permission, String department) {
        String result = "";


        PreparedStatement statement = null;
        Connection conn = null;
        ResultSet rs = null;
        try {
            conn = DriverManager.getConnection(url, nickname, password);
            String statementText = "";

            String whereString = "";
            String groupString = "GROUP BY ru.nazwa ";
            String selectSting = "SELECT ru.nazwa AS nazwa,COUNT(*) AS rowCount ";
            String orderString = "";

            if (groupDepartments) {
                selectSting = "SELECT dz.nazwa AS dzNazwa, ru.nazwa AS nazwa,COUNT(*) AS rowCount ";
                groupString = "GROUP BY dz.nazwa,ru.nazwa ";
                orderString = "ORDER BY dz.nazwa";
            }

            if (onlyPermissionType && onlyDepartment) {
                whereString = "WHERE ru.nazwa = ? AND dz.nazwa = ? ";
            } else if (onlyPermissionType) {
                whereString = "WHERE ru.nazwa = ? ";
            } else if (onlyDepartment) {
                whereString = "WHERE dz.nazwa = ? ";
            }


            statementText = selectSting +
                    "FROM Historie_nadania_uprawnien h " +
                    "JOIN Rodzaje_uprawnien ru ON h.rodzaj_uprawnienia_id = ru.id " +
                    "JOIN Konta_pracownikow kp ON h.id_konta = kp.id_konta " +
                    "JOIN Stanowiska st ON kp.stanowisko_id = st.id " +
                    "JOIN Dzialy dz ON st.dzial_id = dz.id " +
                    whereString +
                    groupString + orderString;
//            System.out.println(statementText);
            statement = conn.prepareStatement(statementText);

            if (onlyPermissionType && onlyDepartment) {
                statement.setString(1, permission);
                statement.setString(2, department);
            } else if (onlyPermissionType) {
                statement.setString(1, permission);
            } else if (onlyDepartment) {
                statement.setString(1, department);
            }
            statement.executeQuery();

            rs = statement.getResultSet();

//            System.out.println(rs);
            if(rs == null){
                result += "błąd";
                return result;
            }

            if(groupDepartments){
                while (rs.next()) {
                    result += rs.getString("dzNazwa");
                    result += ": ";
                    result += rs.getString("nazwa");
                    result += ": ";
                    result += rs.getInt("rowCount");
                    result += "\n";
                }
            }else{
                while (rs.next()) {
                    result += rs.getString("nazwa");
                    result += ": ";
                    result += rs.getInt("rowCount");
                    result += "\n";
                }
            }


            rs.close();
            statement.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return result;
    }

    public String[] getEmployees() {
        ArrayList<String> result = new ArrayList<String>();


        PreparedStatement statement = null;
        Connection conn = null;
        ResultSet rs = null;
        try {
            conn = DriverManager.getConnection(url, nickname, password);
            String statementText = "";

            String selectSting = "SELECT DISTINCT kp.imie AS imie,kp.nazwisko AS nazwisko ";
            String orderString = "ORDER BY nazwisko ";



            statementText = selectSting +
                    "FROM Konta_pracownikow kp " + orderString;
//            System.out.println(statementText);
            statement = conn.prepareStatement(statementText);

            statement.executeQuery();

            rs = statement.getResultSet();

//            System.out.println(rs);
            if(rs == null){
                result.add("błąd");
                return result.toArray(new String[0]);
            }

            while (rs.next()) {
                result.add(rs.getString("nazwisko") + " " + rs.getString("imie"));
            }



            rs.close();
            statement.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return result.toArray(new String[0]);
    }


    public String generateHistoryOfPermission(String surnameAndName) {
        String result = "";

        String surname = surnameAndName.split(" ")[0];
        String name = surnameAndName.split(" ")[1];


        PreparedStatement statement = null;
        Connection conn = null;
        ResultSet rs = null;
        try {
            conn = DriverManager.getConnection(url, nickname, password);
            String statementText = "";

            String whereString = "WHERE kp.imie = ? AND kp.nazwisko = ? ";
            String groupString = "";
            String selectSting = "SELECT h.data AS hDate,h.okreslenie_akcji AS actionType,ru.nazwa AS permissionType ";
            String orderString = "ORDER BY h.data";



            statementText = selectSting +
                    "FROM Historie_nadania_uprawnien h " +
                    "JOIN Rodzaje_uprawnien ru ON h.rodzaj_uprawnienia_id = ru.id " +
                    "JOIN Konta_pracownikow kp ON h.id_konta = kp.id_konta " +
                    whereString +
                    groupString + orderString;
//            System.out.println(statementText);
            statement = conn.prepareStatement(statementText);

            statement.setString(1,name);
            statement.setString(2,surname);

            statement.executeQuery();

            rs = statement.getResultSet();

//            System.out.println(rs);
            if(rs == null){
                result += "błąd";
                return result;
            }

            result += surname + " " + name + "\n";
            while (rs.next()) {
                result += rs.getString("hDate");
                result += ": ";
                result += rs.getString("actionType");
                result += ": ";
                result += rs.getString("permissionType");
                result += "\n";
            }



            rs.close();
            statement.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return result;
    }


    public String generateActionInMonthReport(Boolean groupDepartments, Boolean onlyAction, Boolean onlyDepartment,
                                              Boolean inMonth, Boolean inYear, String action, String department,
                                              String month, String year) {
        String result = "";


        PreparedStatement statement = null;
        Connection conn = null;
        ResultSet rs = null;
        try {
            conn = DriverManager.getConnection(url, nickname, password);
            String statementText = "";

            String whereString = "WHERE ( cz.nazwa_czynnosci = ? OR 1=1 ) ";
            String groupString = "GROUP BY h.data, cz.nazwa_czynnosci ";
            String selectSting = "SELECT h.data AS hData, cz.nazwa_czynnosci AS nazwa,COUNT(*) AS rowCount ";
            String orderString = "ORDER BY h.data ";

            if (groupDepartments) {
                selectSting = "SELECT h.data AS hData, dz.nazwa AS dzNazwa, cz.nazwa_czynnosci AS nazwa,COUNT(*) AS rowCount ";
                groupString = "GROUP BY dz.nazwa, h.data, cz.nazwa_czynnosci ";
                orderString = "ORDER BY h.data,dz.nazwa ";
            }

            int counter =1;
            int monthIndex =1;
            int yearIndex =1;
            int actionIndex =1;
            int departmentIndex =1;
            if (inMonth) {
                whereString += "AND EXTRACT(month FROM h.data) = ? ";
                counter++;
                monthIndex = counter;
            }
            if(inYear){
                whereString += "AND EXTRACT(year FROM h.data) = ? ";
                counter++;
                yearIndex = counter;
            }
            if (onlyAction) {
                whereString += "AND cz.nazwa_czynnosci = ? ";
                counter++;
                actionIndex = counter;
            }
            if (onlyDepartment) {
                whereString += "AND dz.nazwa = ? ";
                counter++;
                departmentIndex = counter;
            }


            statementText = selectSting +
                    "FROM Historie_wykonania_czynnosci h " +
                    "JOIN Czynnosci cz ON h.czynnosc_numer = cz.numer " +
                    "JOIN Konta_pracownikow kp ON h.konto_pracownika_id_konta = kp.id_konta " +
                    "JOIN Stanowiska st ON kp.stanowisko_id = st.id " +
                    "JOIN Dzialy dz ON st.dzial_id = dz.id " +
                    whereString +
                    groupString + orderString;
//            System.out.println(statementText);
            statement = conn.prepareStatement(statementText);


            int monthNumber = 0;
            switch (month){
                case "Styczeń":
                    monthNumber=1;
                    break;
                case "Luty":
                    monthNumber=2;
                    break;
                case "Marzec":
                    monthNumber=3;
                    break;
                case "Kwiecień":
                    monthNumber=4;
                    break;
                case "Maj":
                    monthNumber=5;
                    break;
                case "Czerwiec":
                    monthNumber=6;
                    break;
                case "Lipiec":
                    monthNumber=7;
                    break;
                case "Sierpień":
                    monthNumber=8;
                    break;
                case "Wrzesień":
                    monthNumber=9;
                    break;
                case "Październik":
                    monthNumber=10;
                    break;
                case "Listopad":
                    monthNumber=11;
                    break;
                case "Grudzień":
                    monthNumber=12;
                    break;

            }

            statement.setString(actionIndex, action);
            statement.setString(departmentIndex, department);
            statement.setInt(monthIndex, monthNumber);
            statement.setInt(yearIndex, (int)Integer.parseInt(year));


            statement.executeQuery();

            rs = statement.getResultSet();

//            System.out.println(rs);
            if(rs == null){
                result += "błąd";
                return result;
            }

            if(groupDepartments){
                while (rs.next()) {
                    result += rs.getString("hData");
                    result += ": ";
                    result += rs.getString("dzNazwa");
                    result += ": ";
                    result += rs.getString("nazwa");
                    result += ": ";
                    result += rs.getInt("rowCount");
                    result += "\n";
                }
            }else{
                while (rs.next()) {
                    result += rs.getString("hData");
                    result += ": ";
                    result += rs.getString("nazwa");
                    result += ": ";
                    result += rs.getInt("rowCount");
                    result += "\n";
                }
            }




            rs.close();
            statement.close();
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return result;
    }

    public void printEmployees() {
//        PreparedStatement statement = null;
//        Connection conn = null;
//        ResultSet rs = null;
//        String employees = "";
//        try{
//            conn = DriverManager.getConnection(url);
//            statement = conn.prepareStatement("SELECT * FROM EMPLOYEES");
//            rs = statement.executeQuery();
//            while( rs.next() )
//            {
//                System.out.println(rs.getInt("employee_id") + " " +
//                        rs.getString("employee_name") + " " +
//                        rs.getString("employee_surname"));
//
//            }
//            rs.close();
//            statement.close();
//            conn.close();
//        }catch(Exception e){
//            e.printStackTrace();
//        }
        try {
            Connection connection = DriverManager.getConnection(url, nickname, password);
            String sql = "SELECT * FROM PRACOWNIK";
            Statement statement = connection.createStatement();
            ResultSet rs = statement.executeQuery(sql);
            while (rs.next()) {
                int id = rs.getInt(1);
                String imie = rs.getString(2);
                String nazwisko = rs.getString(3);
                int przelozony = rs.getInt(4);
                System.out.println("id: " + id + "\nIMIE: " + imie + "\nnazwisko: " + nazwisko + "\nprzelozony: "
                        + przelozony);
            }

            connection.close();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {

        }
    }

}
