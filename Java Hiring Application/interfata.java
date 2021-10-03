package TemaPOO;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import java.awt.*;
import java.awt.event.*;

class Interfata extends JFrame implements ActionListener {

    JLabel title, name,password;
    JTextField name_field;
    JPasswordField password_field;
    JButton submit;
    JButton admin;

    Interfata() {
        setTitle("Company Search:");
        setVisible(true);
        setSize(500, 500);
        setLayout(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        title = new JLabel("Company Search:");
        title.setForeground(Color.black);
        title.setFont(new Font("Company Search", Font.BOLD, 15));
        name = new JLabel("Name :");
        name_field = new JTextField();
        password = new JLabel("Password : ");
        password_field = new JPasswordField();
        submit = new JButton("Submit");
        admin = new JButton("Admin Page");
        title.setBounds(190, 100, 200, 30);
        name.setBounds(100, 150, 200, 30);
        name_field.setBounds(170, 150, 200, 30);
        password.setBounds(70,200,200,30);
        password_field.setBounds(170,200,200,30);
        submit.setBounds(200, 260, 100, 30);
        admin.setBounds(10, 430, 130, 30);
        add(title);
        add(name);
        add(name_field);
        add(password);
        add(password_field);
        add(submit);
        add(admin);
        submit.addActionListener(this);
        admin.addActionListener(this);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    }

    public void actionPerformed(ActionEvent e) {
        Application app = Application.getInstance();
        if (e.getSource() == admin) {
            JOptionPane.showMessageDialog(this, "Welcome in Admin Page!");
            JFrame admin_page = new JFrame();
            admin_page.setMinimumSize(new Dimension(200, 200));
            admin_page.setLayout(new GridLayout(1, 2));
            DefaultMutableTreeNode companies = new DefaultMutableTreeNode("Company");
            for (int i = 0; i < app.companies.size(); i++) {
                DefaultMutableTreeNode add_companies = new DefaultMutableTreeNode(app.companies.get(i).nume);
                for (int j = 0; j < app.companies.get(i).departaments.size(); j++) {
                    DefaultMutableTreeNode add_departaments = new DefaultMutableTreeNode(app.companies.get(i).departaments.get(j));
                    for (int k = 0; k < app.companies.get(i).departaments.get(j).list_of_employees.size(); k++) {
                        DefaultMutableTreeNode add_employees = new DefaultMutableTreeNode(app.companies.get(i).departaments.get(j).list_of_employees.get(k).res.info.getName());
                        add_departaments.add(add_employees);
                    }
                    DefaultMutableTreeNode jobbs = new DefaultMutableTreeNode("Jobs");
                    for (int k = 0; k < app.companies.get(i).departaments.get(j).list_of_jobs.size(); k++) {
                        DefaultMutableTreeNode add_jobs = new DefaultMutableTreeNode(app.companies.get(i).departaments.get(j).list_of_jobs.get(k).name_job);
                        jobbs.add(add_jobs);
                        if (app.companies.get(i).departaments.get(j).list_of_jobs.get(k).departamanet_job.equals(app.companies.get(i).departaments.get(j).name_departament)) {
                            add_departaments.add(jobbs);
                        }
                    }
                    add_companies.add(add_departaments);
                }
                companies.add(add_companies);
            }

            JTree tree = new JTree(companies);
            int vertical = ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED;
            int horizontal = ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
            JScrollPane scrollPane = new JScrollPane(tree, vertical, horizontal);
            admin_page.add(scrollPane);
            admin_page.setSize(1000, 600);
            admin_page.setVisible(true);
            JPanel panel = new JPanel();
            panel.setLayout(new GridBagLayout());
            GridBagConstraints gridBagConstraints = new GridBagConstraints();
            JTextField name_field = new JTextField(25);
            JLabel name_label = new JLabel("Name : ");
            JTextField salary_field = new JTextField(25);
            JLabel salary_label = new JLabel("Salary : ");
            JTextField email_field = new JTextField(25);
            JLabel email_label = new JLabel("Email : ");
            JTextField phone_field = new JTextField(25);
            JLabel phone_label = new JLabel("Phone : ");
            JTextField birthday_field = new JTextField(25);
            JLabel birthday_label = new JLabel("Birthday : ");
            JTextField sex_field = new JTextField(25);
            JLabel sex_label = new JLabel("Genre : ");
            JTextField language_field = new JTextField(25);
            JLabel language_label = new JLabel("Languages list : ");
            JTextField level_field = new JTextField(25);
            JLabel level_label = new JLabel("Language Level : ");
            JTextField total_field = new JTextField(25);
            JLabel total_label = new JLabel("TotalSalaryBudget : ");
            gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
            panel.add(name_label, gridBagConstraints);
            panel.add(name_field, gridBagConstraints);
            panel.add(salary_label, gridBagConstraints);
            panel.add(salary_field, gridBagConstraints);
            panel.add(email_label, gridBagConstraints);
            panel.add(email_field, gridBagConstraints);
            panel.add(phone_label, gridBagConstraints);
            panel.add(phone_field, gridBagConstraints);
            panel.add(birthday_label, gridBagConstraints);
            panel.add(birthday_field, gridBagConstraints);
            panel.add(sex_label, gridBagConstraints);
            panel.add(sex_field, gridBagConstraints);
            panel.add(language_label, gridBagConstraints);
            panel.add(language_field, gridBagConstraints);
            panel.add(level_label, gridBagConstraints);
            panel.add(level_field, gridBagConstraints);
            gridBagConstraints.gridwidth = GridBagConstraints.BASELINE;
            panel.add(total_label, gridBagConstraints);
            panel.add(total_field, gridBagConstraints);
            admin_page.add(panel);
            tree.addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    int test = tree.getRowForLocation(e.getX(), e.getY());
                    if (e.getClickCount() == 2) {
                        String text = tree.getPathForRow(test).getLastPathComponent().toString();
                        for (Company c : app.companies) {
                            if (tree.getPathForRow(test).getPathComponent(1).toString().equals(c.nume)) {
                                for (Departament d : c.departaments) {
                                    if (text.equals(d.name_departament)) {
                                        total_field.setText(String.valueOf(d.getTotalSalaryBudget()));
                                    }
                                }
                            }
                        }
                        for (Company c : app.companies) {
                            for (Departament d : c.departaments) {
                                for (Employee em : d.list_of_employees) {
                                    if (text.equals(em.res.info.getName())) {
                                        name_field.setText(em.res.info.getName());
                                        salary_field.setText(String.valueOf(em.salary));
                                        email_field.setText(em.res.info.getEmail());
                                        phone_field.setText(em.res.info.getPhone());
                                        language_field.setText(String.valueOf(em.res.info.getLanguages_list()));
                                        level_field.setText(String.valueOf(em.res.info.getLevel_of_language()));
                                        sex_field.setText(em.res.info.getSex());
                                        birthday_field.setText(em.res.info.getDay_of_birthday());

                                    }
                                }
                            }
                        }
                    }
                }
            });
        } else if (e.getSource() == submit) {
            String userText;
            userText = name_field.getText();
            for (User u : app.users) {
                if (userText.equalsIgnoreCase(u.res.info.getName()) && password_field.getText().equals("user")) {
                    JOptionPane.showMessageDialog(this, "Welcome\nYou are User!");
                    JFrame profile_page = new JFrame("Profile page");
                    JTabbedPane tp = new JTabbedPane(JTabbedPane.LEFT, JTabbedPane.WRAP_TAB_LAYOUT);
                    String[][] information_data = new String[1][7];
                    String[] information_column = {"Name", "Email", "Phone", "Genre", "Birthday",
                            "Languages list", "Languages level"};
                    information_data[0][0] = u.res.info.getName();
                    information_data[0][1] = u.res.info.getEmail();
                    information_data[0][2] = u.res.info.getPhone();
                    information_data[0][3] = u.res.info.getSex();
                    information_data[0][4] = u.res.info.getDay_of_birthday();
                    information_data[0][5] = String.valueOf(u.res.info.getLanguages_list());
                    information_data[0][6] = String.valueOf(u.res.info.getLevel_of_language());
                    JTable information_table = new JTable(information_data, information_column);
                    JScrollPane information = new JScrollPane(information_table);
                    tp.addTab("Information", information);
                    String[][] education_data = new String[u.res.educ.size()][5];
                    String[] education_column = {"Name of institution", "Level", "Graduation average", "Start date",
                            "End date"};
                    for (int i = 0; i < u.res.educ.size(); i++) {
                        education_data[i][0] = u.res.educ.get(i).name_of_the_institution;
                        education_data[i][1] = u.res.educ.get(i).level_of_education;
                        education_data[i][2] = String.valueOf(u.res.educ.get(i).end_media);
                        education_data[i][3] = u.res.educ.get(i).start_date_education;
                        education_data[i][4] = u.res.educ.get(i).end_date_education;
                    }
                    JTable education_table = new JTable(education_data, education_column);
                    JScrollPane education = new JScrollPane(education_table);
                    String[][] experience_data = new String[u.res.exp.size()][4];
                    String[] experience_column = {"Company", "Position", "Start date",
                            "End date"};
                    for (int i = 0; i < u.res.exp.size(); i++) {
                        experience_data[i][0] = u.res.exp.get(i).company;
                        experience_data[i][1] = u.res.exp.get(i).position;
                        experience_data[i][2] = u.res.exp.get(i).start_date_experience;
                        experience_data[i][3] = u.res.exp.get(i).end_date_experience;
                    }
                    JTable experience_table = new JTable(experience_data, experience_column);
                    JScrollPane experience = new JScrollPane(experience_table);
                    JTextArea textArea = new JTextArea();
                    for (int i = 0; i < u.notification.size(); i++) {
                        textArea.append(u.notification.get(i));
                    }
                    tp.addTab("Educations", education);
                    tp.addTab("Experiences", experience);
                    tp.addTab("Notifications", textArea);
                    profile_page.getContentPane().add(tp);
                    profile_page.setSize(600, 600);
                    profile_page.setVisible(true);
                    break;
                }
            }
            for (Company c : app.companies) {
                for (Departament d : c.departaments) {
                    for (Employee employee : d.list_of_employees) {
                        if (userText.equalsIgnoreCase(employee.res.info.getName()) && password_field.getText().equals("employee")) {
                            JOptionPane.showMessageDialog(this, "Welcome\nYou are Employee!");
                            JFrame profile_page = new JFrame("Profile page");
                            JTabbedPane tp = new JTabbedPane(JTabbedPane.LEFT, JTabbedPane.WRAP_TAB_LAYOUT);
                            String[][] information_data = new String[1][7];
                            String[] information_column = {"Name", "Email", "Phone", "Genre", "Birthday",
                                    "Languages list", "Language level"};
                            information_data[0][0] = employee.res.info.getName();
                            information_data[0][1] = employee.res.info.getEmail();
                            information_data[0][2] = employee.res.info.getPhone();
                            information_data[0][3] = employee.res.info.getSex();
                            information_data[0][4] = employee.res.info.getDay_of_birthday();
                            information_data[0][5] = String.valueOf(employee.res.info.getLanguages_list());
                            information_data[0][6] = String.valueOf(employee.res.info.getLevel_of_language());
                            JTable information_table = new JTable(information_data, information_column);
                            JScrollPane information = new JScrollPane(information_table);
                            tp.addTab("Information", information);
                            String[][] education_data = new String[employee.res.educ.size()][5];
                            String[] education_column = {"Name of institution", "Level", "Graduation average", "Start date",
                                    "End date"};
                            for (int i = 0; i < employee.res.educ.size(); i++) {
                                education_data[i][0] = employee.res.educ.get(i).name_of_the_institution;
                                education_data[i][1] = employee.res.educ.get(i).level_of_education;
                                education_data[i][2] = String.valueOf(employee.res.educ.get(i).end_media);
                                education_data[i][3] = employee.res.educ.get(i).start_date_education;
                                education_data[i][4] = employee.res.educ.get(i).end_date_education;
                            }
                            JTable education_table = new JTable(education_data, education_column);
                            JScrollPane education = new JScrollPane(education_table);
                            String[][] experience_data = new String[employee.res.exp.size()][5];
                            String[] experience_column = {"Company", "Position", "Departament" ,"Start date",
                                    "End date"};
                            for (int i = 0; i < employee.res.exp.size(); i++) {
                                experience_data[i][0] = employee.res.exp.get(i).company;
                                experience_data[i][1] = employee.res.exp.get(i).position;
                                experience_data[i][2] = employee.res.exp.get(i).departament;
                                experience_data[i][3] = employee.res.exp.get(i).start_date_experience;
                                experience_data[i][4] = employee.res.exp.get(i).end_date_experience;
                            }
                            JTable experience_table = new JTable(experience_data, experience_column);
                            JScrollPane experience = new JScrollPane(experience_table);
                            tp.addTab("Educations", education);
                            tp.addTab("Experiences", experience);


                            JPanel search = new JPanel();
                            search.setLayout(new GridBagLayout());
                            JPanel main_search = new JPanel();
                            main_search.setLayout(new GridLayout(1,2));
                            JPanel information_search = new JPanel();
                            information_search.setLayout(new GridBagLayout());
                            int vertical_search = ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED;
                            int horizontal_search = ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
                            JLabel name_search = new JLabel("Name : ");
                            JButton search_button = new JButton("Search");
                            JTextField search_text = new JTextField(30);
                            GridBagConstraints gridBagConstraints = new GridBagConstraints();
                            gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
                            search.add(name_search,gridBagConstraints);
                            search.add(search_text,gridBagConstraints);
                            search.add(search_button,gridBagConstraints);
                            JTextField name_field = new JTextField(25);
                            JLabel name_user = new JLabel("Name User : ");
                            JTextField email_field = new JTextField(25);
                            JLabel email_user = new JLabel("Name Email : ");
                            information_search.add(name_user,gridBagConstraints);
                            information_search.add(name_field,gridBagConstraints);
                            information_search.add(email_user,gridBagConstraints);
                            information_search.add(email_field,gridBagConstraints);
                            JLabel phone_user = new JLabel("Phone User : ");
                            JTextField phone_field = new JTextField(25);
                            information_search.add(phone_user,gridBagConstraints);
                            information_search.add(phone_field,gridBagConstraints);
                            JLabel sex_user = new JLabel("Genre : ");
                            JTextField sex_field = new JTextField(25);
                            information_search.add(sex_user,gridBagConstraints);
                            information_search.add(sex_field,gridBagConstraints);
                            JTextField birthday_field = new JTextField(25);
                            JLabel birthday_user = new JLabel("Birthday date :  ");
                            JTextField languages_field = new JTextField(25);
                            JLabel languages_user = new JLabel("Languages list: ");
                            JTextField list_field = new JTextField(25);
                            JLabel list_user = new JLabel("Languages level : ");
                            JTextField interested_field = new JTextField(25);
                            JLabel interested_user = new JLabel("Interested Company : ");
                            information_search.add(birthday_user,gridBagConstraints);
                            information_search.add(birthday_field,gridBagConstraints);
                            information_search.add(languages_user,gridBagConstraints);
                            information_search.add(languages_field,gridBagConstraints);
                            information_search.add(list_user,gridBagConstraints);
                            information_search.add(list_field,gridBagConstraints);
                            information_search.add(interested_user,gridBagConstraints);
                            information_search.add(interested_field,gridBagConstraints);
                            JButton educations = new JButton("Education");
                            JButton experiences = new JButton("Experience");
                            gridBagConstraints.gridwidth = GridBagConstraints.EAST;
                            information_search.add(educations,gridBagConstraints);
                            gridBagConstraints.gridwidth = GridBagConstraints.WEST;
                            information_search.add(experiences,gridBagConstraints);

                            JScrollPane scrollPane_search = new JScrollPane(search, vertical_search, horizontal_search);
                            JScrollPane scrollPane_information = new JScrollPane(information_search, vertical_search, horizontal_search);
                            search_button.addActionListener(e1 -> {
                                for(User u : app.users) {
                                    if(u.res.info.getName().equalsIgnoreCase(search_text.getText())) {
                                        name_field.setText(u.res.info.getName());
                                        email_field.setText(u.res.info.getEmail());
                                        birthday_field.setText(u.res.info.getDay_of_birthday());
                                        sex_field.setText(u.res.info.getSex());
                                        languages_field.setText(String.valueOf(u.res.info.getLanguages_list()));
                                        list_field.setText(String.valueOf(u.res.info.getLanguages_list()));
                                        phone_field.setText(u.res.info.getPhone());
                                        interested_field.setText(String.valueOf(u.interested_companies));
                                        educations.addActionListener(e2 -> {
                                            JFrame education_page = new JFrame("Educations Page");
                                            String[][] education_data_search = new String[u.res.educ.size()][5];
                                            String[] education_column_search = {"Name of institution", "Level", "Graduation average", "Start date",
                                                    "End date"};
                                            for (int i = 0; i < u.res.educ.size(); i++) {
                                                education_data_search[i][0] = u.res.educ.get(i).name_of_the_institution;
                                                education_data_search[i][1] = u.res.educ.get(i).level_of_education;
                                                education_data_search[i][2] = String.valueOf(u.res.educ.get(i).end_media);
                                                education_data_search[i][3] = u.res.educ.get(i).start_date_education;
                                                education_data_search[i][4] = u.res.educ.get(i).end_date_education;
                                            }
                                            JTable education_table_search = new JTable(education_data_search, education_column_search);
                                            JScrollPane education_pane = new JScrollPane(education_table_search);
                                            education_page.add(education_pane);
                                            education_page.setSize(300, 300);
                                            education_page.setVisible(true);
                                        });
                                        experiences.addActionListener(e3 -> {
                                            JFrame experience_page = new JFrame("Educations Page");
                                            String[][] experience_data_search = new String[u.res.exp.size()][4];
                                            String[] experience_column_search = {"Company", "Position", "Start date",
                                                    "End date"};
                                            for (int i = 0; i < u.res.exp.size(); i++) {
                                                experience_data_search[i][0] = u.res.exp.get(i).company;
                                                experience_data_search[i][1] = u.res.exp.get(i).position;
                                                experience_data_search[i][2] = u.res.exp.get(i).start_date_experience;
                                                experience_data_search[i][3] = u.res.exp.get(i).end_date_experience;
                                            }
                                            JTable experience_table_search = new JTable(experience_data_search, experience_column_search);
                                            JScrollPane experience_pane = new JScrollPane(experience_table_search);
                                            experience_page.add(experience_pane);
                                            experience_page.setSize(300, 300);
                                            experience_page.setVisible(true);
                                        });
                                    }
                                }
                            });
                            main_search.add(scrollPane_search);
                            main_search.add(scrollPane_information);
                            tp.add(main_search,"Search user");
                            profile_page.getContentPane().add(tp);
                            profile_page.setSize(600, 600);
                            profile_page.setVisible(true);
                            break;
                        }
                    }
                }
            }
            for (Company c : app.companies) {
                if (userText.equalsIgnoreCase(c.manager.res.info.getName()) && password_field.getText().equals("manager")) {
                    JOptionPane.showMessageDialog(this, "Welcome\nYou are Manager!");
                    JFrame manager_page = new JFrame("Manager Page");
                    JPanel main = new JPanel();

                    int vertical = ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED;
                    int horizontal = ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
                    JScrollPane scrollPane = new JScrollPane(main, vertical, horizontal);
                    for (Company com : app.companies) {
                        if (com.manager.res.info.getName().equals(c.manager.res.info.getName())) {
                            main.setLayout(new GridLayout(com.manager.employment_requests.size(), 1));
                            for (int i = 0; i < com.manager.employment_requests.size(); i++) {
                                Request request = com.manager.employment_requests.get(i);
                                User u = (User) com.manager.employment_requests.get(i).getValue1();
                                Job j = (Job) com.manager.employment_requests.get(i).getKey();
                                Recruiter r = (Recruiter) com.manager.employment_requests.get(i).getValue2();
                                double score_user = (double) com.manager.employment_requests.get(i).getScore();
                                JPanel panel = new JPanel();
                                panel.setLayout(new GridBagLayout());
                                GridBagConstraints gridBagConstraints = new GridBagConstraints();
                                gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
                                JLabel name_user = new JLabel("Name user : ");
                                JTextField name_user_field = new JTextField(25);
                                panel.add(name_user, gridBagConstraints);
                                panel.add(name_user_field, gridBagConstraints);

                                JLabel name_job = new JLabel("Name job : ");
                                JTextField name_job_field = new JTextField(25);
                                panel.add(name_job, gridBagConstraints);
                                panel.add(name_job_field, gridBagConstraints);

                                JLabel name_company = new JLabel("Name company : ");
                                JTextField name_company_field = new JTextField(25);
                                panel.add(name_company, gridBagConstraints);
                                panel.add(name_company_field, gridBagConstraints);

                                JLabel name_recruiter = new JLabel("Name recruiter : ");
                                JTextField name_recruiter_field = new JTextField(25);
                                panel.add(name_recruiter, gridBagConstraints);
                                panel.add(name_recruiter_field, gridBagConstraints);

                                JLabel score = new JLabel(" Score : ");
                                JTextField score_field = new JTextField(25);
                                panel.add(score, gridBagConstraints);
                                panel.add(score_field, gridBagConstraints);

                                JLabel text_label = new JLabel("Answer to this request:");
                                JButton accept = new JButton("Accept");
                                JButton decline = new JButton("Decline");
                                panel.add(text_label, gridBagConstraints);
                                gridBagConstraints.gridwidth = GridBagConstraints.SOUTHWEST;
                                panel.add(accept, gridBagConstraints);
                                gridBagConstraints.gridwidth = GridBagConstraints.SOUTHEAST;
                                panel.add(decline, gridBagConstraints);

                                name_user_field.setText(u.res.info.getName());
                                name_job_field.setText(j.name_job);
                                name_company_field.setText(j.name_company_for_job);
                                name_recruiter_field.setText(r.res.info.getName());
                                score_field.setText(String.valueOf(score_user));
                                int vertical_panel = ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED;
                                int horizontal_panel = ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
                                JScrollPane scrollPane_panel = new JScrollPane(panel, vertical_panel, horizontal_panel);


                                main.add(scrollPane_panel);
                                accept.addActionListener(e1 -> {
                                    for (int k = 0; k < app.users.size(); k++) {
                                        if (app.users.get(k).equals(u)) {
                                            for (Departament d : com.departaments) {
                                                for (int q = 0; q < d.list_of_jobs.size(); q++) {
                                                    if (d.list_of_jobs.get(q).equals(j)) {
                                                        if(d.name_departament.equals(d.list_of_jobs.get(q).departamanet_job))
                                                            d.list_of_employees.add(u.convert());
                                                        com.manager.employment_requests.remove(request);
                                                        app.users.remove(u);
                                                        main.remove(scrollPane_panel);
                                                        j.flag = false;
                                                        d.list_of_jobs.remove(j);
                                                        break;
                                                    }
                                                    break;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                    JOptionPane.showMessageDialog(this, "Congratulations ! You have hired on  " + u.res.info.getName());
                                });
                                decline.addActionListener(e1 -> {
                                    com.manager.employment_requests.remove(request);
                                    u.notification.add("You were rejected " + j.name_job + " by manager " +
                                            com.manager.res.info.getName() + "\n");
                                    main.remove(scrollPane_panel);
                                });
                            }
                        }
                    }

                    JTabbedPane tp = new JTabbedPane(JTabbedPane.LEFT, JTabbedPane.WRAP_TAB_LAYOUT);
                    JPanel search = new JPanel();
                    search.setLayout(new GridBagLayout());
                    JPanel main_search = new JPanel();
                    main_search.setLayout(new GridLayout(1,2));
                    JPanel information = new JPanel();
                    information.setLayout(new GridBagLayout());
                    int vertical_search = ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED;
                    int horizontal_search = ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
                    JLabel name_search = new JLabel("Name : ");
                    JButton search_button = new JButton("Search");
                    JTextField search_text = new JTextField(30);
                    GridBagConstraints gridBagConstraints = new GridBagConstraints();
                    gridBagConstraints.gridwidth = GridBagConstraints.REMAINDER;
                    search.add(name_search,gridBagConstraints);
                    search.add(search_text,gridBagConstraints);
                    search.add(search_button,gridBagConstraints);
                    JTextField name_field = new JTextField(25);
                    JLabel name_user = new JLabel("Name User : ");
                    JTextField email_field = new JTextField(25);
                    JLabel email_user = new JLabel("Name Email : ");
                    information.add(name_user,gridBagConstraints);
                    information.add(name_field,gridBagConstraints);
                    information.add(email_user,gridBagConstraints);
                    information.add(email_field,gridBagConstraints);
                    JLabel phone_user = new JLabel("Phone User : ");
                    JTextField phone_field = new JTextField(25);
                    information.add(phone_user,gridBagConstraints);
                    information.add(phone_field,gridBagConstraints);
                    JLabel sex_user = new JLabel("Genre : ");
                    JTextField sex_field = new JTextField(25);
                    information.add(sex_user,gridBagConstraints);
                    information.add(sex_field,gridBagConstraints);
                    JTextField birthday_field = new JTextField(25);
                    JLabel birthday_user = new JLabel("Birthday date :  ");
                    JTextField languages_field = new JTextField(25);
                    JLabel languages_user = new JLabel("Languages : ");
                    JTextField list_field = new JTextField(25);
                    JLabel list_user = new JLabel("Level of languages : ");

                    JTextField interested_field = new JTextField(25);
                    JLabel interested_user = new JLabel("Interested Company : ");
                    information.add(birthday_user,gridBagConstraints);
                    information.add(birthday_field,gridBagConstraints);
                    information.add(languages_user,gridBagConstraints);
                    information.add(languages_field,gridBagConstraints);
                    information.add(list_user,gridBagConstraints);
                    information.add(list_field,gridBagConstraints);
                    information.add(interested_user,gridBagConstraints);
                    information.add(interested_field,gridBagConstraints);
                    JButton educations = new JButton("Education");
                    JButton experiences = new JButton("Experience");
                    gridBagConstraints.gridwidth = GridBagConstraints.EAST;
                    information.add(educations,gridBagConstraints);
                    gridBagConstraints.gridwidth = GridBagConstraints.WEST;
                    information.add(experiences,gridBagConstraints);

                    JScrollPane scrollPane_search = new JScrollPane(search, vertical_search, horizontal_search);
                    JScrollPane scrollPane_information = new JScrollPane(information, vertical_search, horizontal_search);
                    search_button.addActionListener(e1 -> {
                        for(User u : app.users) {
                            if(u.res.info.getName().equalsIgnoreCase(search_text.getText())) {
                                name_field.setText(u.res.info.getName());
                                email_field.setText(u.res.info.getEmail());
                                birthday_field.setText(u.res.info.getDay_of_birthday());
                                sex_field.setText(u.res.info.getSex());
                                languages_field.setText(String.valueOf(u.res.info.getLanguages_list()));
                                list_field.setText(String.valueOf(u.res.info.getLanguages_list()));
                                phone_field.setText(u.res.info.getPhone());
                                interested_field.setText(String.valueOf(u.interested_companies));
                                educations.addActionListener(e2 -> {
                                    JFrame education_page = new JFrame("Educations Page");
                                    String[][] education_data = new String[u.res.educ.size()][5];
                                    String[] education_column = {"Name of institution", "Level", "Graduation average", "Start date",
                                            "End date"};
                                    for (int i = 0; i < u.res.educ.size(); i++) {
                                        education_data[i][0] = u.res.educ.get(i).name_of_the_institution;
                                        education_data[i][1] = u.res.educ.get(i).level_of_education;
                                        education_data[i][2] = String.valueOf(u.res.educ.get(i).end_media);
                                        education_data[i][3] = u.res.educ.get(i).start_date_education;
                                        education_data[i][4] = u.res.educ.get(i).end_date_education;
                                    }
                                    JTable education_table = new JTable(education_data, education_column);
                                    JScrollPane education_pane = new JScrollPane(education_table);
                                    education_page.add(education_pane);
                                    education_page.setSize(300, 300);
                                    education_page.setVisible(true);
                                });
                                experiences.addActionListener(e3 -> {
                                    JFrame experience_page = new JFrame("Educations Page");
                                    String[][] experience_data = new String[u.res.exp.size()][4];
                                    String[] experience_column = {"Company", "Position", "Start date",
                                            "End date"};
                                    for (int i = 0; i < u.res.exp.size(); i++) {
                                        experience_data[i][0] = u.res.exp.get(i).company;
                                        experience_data[i][1] = u.res.exp.get(i).position;
                                        experience_data[i][2] = u.res.exp.get(i).start_date_experience;
                                        experience_data[i][3] = u.res.exp.get(i).end_date_experience;
                                    }
                                    JTable experience_table = new JTable(experience_data, experience_column);
                                    JScrollPane experience_pane = new JScrollPane(experience_table);
                                    experience_page.add(experience_pane);
                                    experience_page.setSize(300, 300);
                                    experience_page.setVisible(true);
                                });
                            }
                        }
                    });
                    main_search.add(scrollPane_search);
                    main_search.add(scrollPane_information);
                    tp.add(scrollPane,"Requests");
                    tp.add(main_search,"Search User");
                    manager_page.getContentPane().add(tp);
                    manager_page.setSize(1000, 600);
                    manager_page.setVisible(true);

                }else if(password_field.getText().equals("")) {
                    JOptionPane.showMessageDialog(this, "Enter a password !");
                    break;
                }else if(!password_field.getText().equals("user") && !password_field.getText().equals("manager") && !password_field.getText().equals("employee")) {
                    JOptionPane.showMessageDialog(this, "The user does not exist or the password is wrong!");
                    break;
                }
            }
        }
    }
}


