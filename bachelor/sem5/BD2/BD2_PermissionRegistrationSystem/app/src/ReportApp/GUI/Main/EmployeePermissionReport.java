package ReportApp.GUI.Main;

import ReportApp.Database.DatabaseHandler;
import ReportApp.GUI.tools.Actions;
import ReportApp.GUI.tools.Departments;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EmployeePermissionReport extends JPanel
{
    private JCheckBox
            groupCheckBox = new JCheckBox("grupuj działy");
    private JCheckBox
            permissionTypeCheckBox = new JCheckBox("policz tylko zaznaczony rodzaj uprawnien");
    private JCheckBox
            departmentCheckBox = new JCheckBox("policz tylko w zaznaczonym dziale");
    String[] permissionTypeList = {"Zarzadzanie dokumentami finansowymi","Zarządzanie rachunkiem firmowym", "Dostęp do systemu X",
            "Dostęp do systemu Y","Dostęp do systemu X z pełnym zakresem","Dostęp do systemu Y z pełnym zakresem","Prowadzenie negocjacji z klientem",
            "Dostęp do tajemnicy X","Dostęp do tajemnicy Y","Zarządzanie rekturacją",
            "Zarządzanie zasobami ludzkimi","Zarządzanie aktywami firmy",
    };
    String[] departmentList = {"IT","Finansowy","Zarzadzanie","Marketing"};
    private JComboBox permissionTypeComboBox = new JComboBox(permissionTypeList);
    private JComboBox departmentComboBox = new JComboBox(departmentList);

    private JButton generateButton = new JButton("Wygeneruj Raport");
    private DatabaseHandler database = new DatabaseHandler();
    private JTextArea textArea = new JTextArea(16,40);
    private JScrollPane textAreaWrap = new JScrollPane(textArea);



    public  EmployeePermissionReport()
    {
        setLayout(null);

        groupCheckBox.setBounds(40,30,300,40);
        permissionTypeCheckBox.setBounds(40,80,300,40);
        departmentCheckBox.setBounds(40,180,300,40);

        departmentComboBox.setBounds(80,230,100,40);
        permissionTypeComboBox.setBounds(80,130,280,40);

        generateButton.setBounds(220,540,200,50);
        textAreaWrap.setBounds(640,30,580,600);


        add(groupCheckBox);
        add(permissionTypeCheckBox);
        add(departmentCheckBox);
        add(permissionTypeComboBox);
        add(departmentComboBox);
        add(generateButton);
        add(textAreaWrap);

        textArea.setLineWrap(true);

        generateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                String text = database.generateEmployeePermissionReport(groupCheckBox.isSelected(),
                        permissionTypeCheckBox.isSelected(),
                        departmentCheckBox.isSelected(),
                        (String)permissionTypeComboBox.getSelectedItem(),
                        (String)departmentComboBox.getSelectedItem());

                textArea.setText(text);
//                textArea.insert(text,0);
            }
        });

    }

}