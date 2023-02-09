package AccessApp.Tests;

public class RunTests {
    public static void main(String[] args){
        TestInsertEmployee.run();//4 emp
        TestInsertDepartment.run();//1dep
        TestInsertPosition.run();//3 pos
        TestInsertEmployeeAcc.run();//4 acc
        TestInsertPermissionKind.run();//2 perm
        TestInsertActivity.run();//2 activities, demanding 1st&2nd permission


        TestInsertPositionPermission.run();// emp3&4 now have 1st permission sine there are on 3rd_pos
        TestInsertEmployeePermission.run();// emp2 now have 2nd permission

        TestLogActivities.run();//there should be 1 record
        TestLogGrantingPermissions.run();//there should be 3 records
        TestLogRemovingPermissions.run();//now 6 records

        //TestChangingName
        //TestChaningNumberOfPermissions



    }
}
