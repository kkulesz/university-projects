package AccessApp.Tests;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TestInsertEmployeeAcc extends Test{
    static boolean run(){
        connect();
        boolean success = true;

        insertEmployeeAcc(acc1Id, emp1Id, log1, pas1,pos1Id, name1, sur1, pos1);
        insertEmployeeAcc(acc2Id, emp2Id, log2, pas2,pos2Id, name2, sur2, pos2);
        insertEmployeeAcc(acc3Id, emp3Id, log3, pas3,pos3Id, name3, sur3, pos3);
        insertEmployeeAcc(acc4Id, emp4Id, log4, pas4,pos3Id, name4, sur4, pos3);//the same position as emp3


        PreparedStatement statement = null;
        ResultSet rs = null;
        try{
            statement = conn.prepareStatement("SELECT count(*) FROM konta_pracownikow");

            rs = statement.executeQuery();
            rs.next();
            if (rs.getInt(1) != 4){
                throw(new Exception("Dodawanie konta pracownika"));
            }

            if(insertEmployeeAcc(acc4Id+1, emp4Id, "sada", pas4,pos3Id, name4, sur4, pos3)){
                throw(new Exception("Dodawanie konta do tego samego pracownika!"));
            }
            if(insertEmployeeAcc(acc4Id+1, emp4Id+1, log4, pas4,pos3Id, name4, sur4, pos3)){
                throw(new Exception("Dodawanie konta o takim samym loginie!"));
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
