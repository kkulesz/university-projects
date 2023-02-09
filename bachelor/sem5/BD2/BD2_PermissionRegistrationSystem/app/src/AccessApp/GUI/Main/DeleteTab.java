package AccessApp.GUI.Main;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;

import static AccessApp.GUI.tools.SwingConsole.run;

public class DeleteTab extends JPanel
{

    private String[] permissionList = {"Zarzadzanie dokumentami finansowymi","Zarządzanie rachunkiem firmowym","Dostęp do systemu X",
            "Dostęp do systemu Y","Dostęp do systemu X z pełnym zakresem","Dostęp do systemu Y z pełnym zakresem",
            "Prowadzenie negocjacji z klientem","Dostęp do tajemnicy X","Dostęp do tajemnicy Y",
            "Zarządzanie rekturacją","Zarządzanie zasobami ludzkimi","Zarządzanie aktywami firmy"};

    //podawanie ID pracownika i sprawdzenie czy istnieje
//    private JLabel enterEmployeeId = new JLabel("Wpisz ID pracownika:");
//    private JTextField employeeIDChecker = new JTextField(20);
    private JLabel chooseEmployee = new JLabel("Wybierz pracownika:");
    private JLabel chooseError = new JLabel("");
    private JLabel removeText = new JLabel("USUWANIE UPRAWNIEŃ");


    private JLabel choosePermission = new JLabel("Wybierz uprawnienie:");
    private JComboBox permissionListBox = new JComboBox(permissionList);

    private JButton refreshEmployees = new JButton("Aktualizuj listę pracowników");
    private JButton addButton = new JButton("Usuń uprawnienie pracownikowi");
    private JButton getButton = new JButton("Pobierz listę uprawnień");
    private JButton employeePermissionsButton = new JButton("Wypisz uprawnienia pracownika");



    private JCheckBox onlySelected = new JCheckBox("Tylko wybrane uprawnienie");

    private JTextArea textArea = new JTextArea(16,40);
    private JScrollPane textAreaWrap = new JScrollPane(textArea);// = new JScrollPane();

    String[] employeeList = {"   "};
    private JComboBox employeeComboBox = new JComboBox(employeeList);

    private HashSet<String> permissions;

    private Connection conn;



    public void getPermissions()
    {
        try
        {
            StringBuffer sql = new StringBuffer("");
            sql.append("SELECT NAZWA, liczba_uprawnien FROM RODZAJE_UPRAWNIEN ");
            if(onlySelected.isSelected()) {
                sql.append("WHERE ID = ");
                sql.append(Arrays.asList(permissionList).indexOf((String) permissionListBox.getSelectedItem())+1);
            }
            sql.append("ORDER BY id");
            PreparedStatement ps = conn.prepareStatement(sql.toString());

            ResultSet rs = ps.executeQuery();

            if(rs==null)
            {
                System.out.println("BLAD");
            }

            StringBuffer sb = new StringBuffer("");

            while (rs.next())
            {
                sb.append(rs.getString(1));
                sb.append(": ");
                sb.append(rs.getInt(2));
                sb.append("\n");
            }

            textArea.setText(sb.toString());

        }
        catch (SQLException throwables)
        {
            System.out.println("BLAD SQL");
            throwables.printStackTrace();
        }
    }


    private String[] getEmployees()
    {
        ArrayList<String> result = new ArrayList<String>();
        try {
            StringBuilder sql = new StringBuilder("");
            sql.append("SELECT DISTINCT kp.imie AS imie,kp.nazwisko AS nazwisko ");
            sql.append("FROM KONTA_PRACOWNIKOW kp ");
            sql.append("ORDER BY NAZWISKO");

            PreparedStatement  statement = conn.prepareStatement(sql.toString());
            ResultSet rs = statement.executeQuery();

            System.out.println(rs);
            if(rs == null){
                result.add("błąd");
                return result.toArray(new String[0]);
            }

            while (rs.next())
            {
                result.add(rs.getString("nazwisko") + " " + rs.getString("imie"));
            }

            rs.close();
            statement.close();

        }
        catch (SQLException throwables)
        {
            throwables.printStackTrace();
        }
        return result.toArray(new String[0]);
    }

    private Boolean removePermission()
    {
        String name,surname;
        if (employeeComboBox.getItemCount()<=1)
        {
            chooseError.setForeground(Color.RED);
            chooseError.setText("Nie wybrano żadnego pracownika!");
            return false;
        }
        else
        {
            chooseError.setText("");
        }
        if(permissionListBox.getItemCount()<1)
        {
            chooseError.setForeground(Color.RED);
            chooseError.setText("Nie wybrano żadnego uprawnienia!");
            return false;
        }
        else
        {
            chooseError.setText("");
        }

        String tmp = (String)employeeComboBox.getSelectedItem();
        String arr[] = tmp.split(" ");
        surname = arr[0];
        name = arr[1];

        try
        {
            CallableStatement cs = conn.prepareCall("{call usun_uprawnienie_pracownika(?, ?, ?)}");
            cs.setString(1,name);
            cs.setString(2,surname);
            cs.setString(3,(String)permissionListBox.getSelectedItem());

            cs.executeQuery();

        }
        catch (SQLException throwables)
        {
            throwables.printStackTrace();
            return false;
        }
        return true;
    }

    private void updatePermissionsForEmployee()
    {
        try
        {
            StringBuilder sql = new StringBuilder("");

            sql.append("SELECT RU.NAZWA \n");
            sql.append("FROM RODZAJE_UPRAWNIEN RU\n");
            sql.append("JOIN UPRAWNIENIA_PRACOWNIKOW UP ON RU.ID = UP.RODZAJ_UPRAWNIENIA_ID\n");
            sql.append("JOIN KONTA_PRACOWNIKOW KP ON KP.ID_KONTA = UP.KONTO_PRACOWNIKA_ID_KONTA\n");
            sql.append("WHERE KP.IMIE=? AND KP.NAZWISKO=?\n");
            sql.append("ORDER BY 1");

            PreparedStatement statement = conn.prepareStatement(sql.toString());

            String tmp = (String)employeeComboBox.getSelectedItem();
            String arr[] = tmp.split(" ");
            String name,surname;
            surname = arr[0];
            name = arr[1];

            statement.setString(1,name);
            statement.setString(2,surname);

            ResultSet rs = statement.executeQuery();

            ArrayList<String> permArray = new ArrayList<String>();
            while (rs.next())
            {
//                System.out.println(rs.getString(1));
                permArray.add(rs.getString(1));
            }
            statement.close();
            rs.close();
            HashSet<String> employeePermisions = new HashSet<String>(permArray);

            ArrayList<String> temp = new ArrayList<String>(employeePermisions);

            permissionListBox.setModel(new DefaultComboBoxModel<String>(temp.toArray(new String[0])));

        }
        catch (SQLException throwables)
        {
            throwables.printStackTrace();
        }
    }

    private void getEmployeePermisions()
    {
        try
        {
            StringBuilder sql = new StringBuilder("");

            sql.append("SELECT RU.NAZWA \n");
            sql.append("FROM RODZAJE_UPRAWNIEN RU\n");
            sql.append("JOIN UPRAWNIENIA_PRACOWNIKOW UP ON RU.ID = UP.RODZAJ_UPRAWNIENIA_ID\n");
            sql.append("JOIN KONTA_PRACOWNIKOW KP ON KP.ID_KONTA = UP.KONTO_PRACOWNIKA_ID_KONTA\n");
            sql.append("WHERE KP.IMIE=? AND KP.NAZWISKO=?\n");
            sql.append("ORDER BY 1");

            PreparedStatement statement = conn.prepareStatement(sql.toString());

            if(employeeComboBox.getItemCount()<2)
            {
                return;
            }
            String tmp = (String)employeeComboBox.getSelectedItem();
            String arr[] = tmp.split(" ");
            String name,surname;
            surname = arr[0];
            name = arr[1];

            statement.setString(1,name);
            statement.setString(2,surname);

            ResultSet rs = statement.executeQuery();

            StringBuilder stringBuilder = new StringBuilder("");
            stringBuilder.append("Uprawnienia pracownika ");
            stringBuilder.append(name + " " + surname + ":\n");


            ArrayList<String> permArray = new ArrayList<String>();
            while (rs.next())
            {
                stringBuilder.append("\t" +rs.getString(1) + "\n");
            }
            statement.close();
            rs.close();
            textArea.setText(stringBuilder.toString());


        }
        catch (SQLException throwables)
        {
            throwables.printStackTrace();
        }
    }


    public DeleteTab(Connection con)
    {
        conn=con;


        setLayout(null);

//        removeText.setBounds();
        chooseEmployee.setBounds(40,40,200,30);
        employeeComboBox.setBounds(40,80,280,40);
        refreshEmployees.setBounds(40,130,200,40);
        employeePermissionsButton.setBounds(350,80,250,40);

        choosePermission.setBounds(40,180,300,30);
        permissionListBox.setBounds(40,220,300,30);


        addButton.setBounds(40,270,250,50);
        chooseError.setBounds(40,320, 250,30);
        getButton.setBounds(220,540,250,50);


        textAreaWrap.setBounds(640,30,580,600);


        add(chooseEmployee);
        add(choosePermission);
        add(permissionListBox);
        add(employeeComboBox);
        add(employeePermissionsButton);
        add(refreshEmployees);

        add(addButton);


        add(getButton);
        add(chooseError);
        add(textAreaWrap);

        permissions = new HashSet<String>(Arrays.asList(permissionList));



        refreshEmployees.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                String[] employees = getEmployees();

                employeeComboBox.setModel(new DefaultComboBoxModel<String>(employees));
                updatePermissionsForEmployee();
            }
        });

        employeePermissionsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                getEmployeePermisions();
            }
        });

        getButton.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                getPermissions();
            }
        });
        addButton.addActionListener(new ActionListener()
        {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                if(removePermission())
                    updatePermissionsForEmployee();

            }
        });

        onlySelected.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(onlySelected.isSelected())
                {
                    getButton.setText("Pobierz informacje o uprawnieniu");
                }
                else
                {
                    getButton.setText("Pobierz listę uprawnień");
                }
            }
        });

        employeeComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e)
            {
                updatePermissionsForEmployee();
            }
        });
    }

}