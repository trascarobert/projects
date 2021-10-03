package TemaPOO;


import org.json.JSONArray;
import org.json.JSONObject;


import javax.swing.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.regex.Pattern;

class Test {
    public static void main(String args[]) throws InvalidDatesException, ResumeIncompleteException{
        try{
            Application app = Application.getInstance();
            ArrayList<Employee> employees = new ArrayList<>();
            ArrayList<Recruiter> recruiters = new ArrayList<>();
            ArrayList<Manager> managers = new ArrayList<>();

            ArrayList<Education> educations;
            ArrayList<Experience> experiences;
            ArrayList<String> languages;
            ArrayList<String> languages_level;
            ArrayList<String> interested_companies;

            String text = new String(Files.readAllBytes(Path.of("/home/robert/Desktop/consumers.json")));
            String text_jobs = new String(Files.readAllBytes(Path.of("/home/robert/Desktop/jobs.json")));
            JSONObject obj = new JSONObject(text);
            JSONObject obj_jobs = new JSONObject(text_jobs);
            JSONArray employeess = obj.getJSONArray("employees");
            JSONArray users = obj.getJSONArray("users");
            JSONArray recruiterss = obj.getJSONArray("recruiters");
            JSONArray managerss = obj.getJSONArray("managers");
            JSONArray jobs = obj_jobs.getJSONArray("jobs");

            /*
            Citirea din consumers.json a angajatilor.
            Angajati ii adaug intr-un ArrayList de tip employee , iar apoi pe fiecare in compania
            din care fac parte .
             */
            for(int i = 0 ; i < employeess.length() ; i++) {
                JSONArray educ = employeess.getJSONObject(i).getJSONArray("education");
                JSONArray exp = employeess.getJSONObject(i).getJSONArray("experience");
                JSONArray languages_array = employeess.getJSONObject(i).getJSONArray("languages");
                JSONArray languages_list_array = employeess.getJSONObject(i).getJSONArray("languages_level");
                educations = new ArrayList<>();
                experiences = new ArrayList<>();
                languages = new ArrayList<>();
                languages_level = new ArrayList<>();
                for(int j = 0 ; j < educ.length() ; j++) {
                     if(educ.getJSONObject(j).get("end_date").equals(null))
                        educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                educ.getJSONObject(j).getString("level"),
                                educ.getJSONObject(j).getDouble("grade"),
                                educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),null));
                     else {
                         educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                 educ.getJSONObject(j).getString("level"),
                                 educ.getJSONObject(j).getDouble("grade"),
                                 educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                 educ.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                     }
                }
                for(int j = 0 ; j < exp.length() ; j++) {
                    if(exp.getJSONObject(j).get("end_date").equals(null))
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("department"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),null));
                    else {
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("department"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                exp.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                    }
                }
                for(int j = 0; j < languages_array.length() ; j++)
                    languages.add(languages_array.getString(j));
                for(int j = 0; j < languages_list_array.length() ; j++)
                    languages_level.add(languages_list_array.getString(j));
                Collections.sort(educations);
                Collections.sort(experiences);
                Consumer.Resume res1 = new Consumer.Resume(new Consumer.Resume.ResumeBuilder(new Information(employeess.getJSONObject(i).getString("name"),
                        employeess.getJSONObject(i).getString("email"),employeess.getJSONObject(i).getString("phone"),
                        employeess.getJSONObject(i).getString("date_of_birth"),employeess.getJSONObject(i).getString("genre"),
                        languages,languages_level),educations).build(),experiences);
                employees.add(new Employee(res1,employeess.getJSONObject(i).getDouble("salary")));
            }


             /*
            Citirea din consumers.json a userilor
             */
            for(int i = 0 ; i < users.length() ; i++) {
                languages = new ArrayList<>();
                languages_level = new ArrayList<>();
                JSONArray languages_array = users.getJSONObject(i).getJSONArray("languages");
                JSONArray languages_list_array = users.getJSONObject(i).getJSONArray("languages_level");
                JSONArray interested = users.getJSONObject(i).getJSONArray("interested_companies");
                JSONArray educ = users.getJSONObject(i).getJSONArray("education");
                JSONArray exp = users.getJSONObject(i).getJSONArray("experience");
                educations = new ArrayList<>();
                experiences = new ArrayList<>();
                interested_companies = new ArrayList<>();
                for(int j = 0; j < languages_array.length() ; j++)
                    languages.add(languages_array.getString(j));
                for(int j = 0; j < languages_list_array.length() ; j++)
                    languages_level.add(languages_list_array.getString(j));
                for(int j = 0 ; j < interested.length() ; j++)
                    interested_companies.add(interested.getString(j));
                for(int j = 0 ; j < educ.length() ; j++) {
                    if(educ.getJSONObject(j).get("end_date").equals(null))
                        educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                educ.getJSONObject(j).getString("level"),educ.getJSONObject(j).getDouble("grade"),
                                educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                null));
                    else {
                        educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                educ.getJSONObject(j).getString("level"),educ.getJSONObject(j).getDouble("grade"),
                                educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                educ.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                    }
                }
                for(int j = 0 ; j < exp.length() ; j++) {
                    if(exp.getJSONObject(j).get("end_date").equals(null))
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                null));
                    else {
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                exp.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                    }
                }
                Collections.sort(educations);
                Collections.sort(experiences);
                Consumer.Resume res = new Consumer.Resume(new Consumer.Resume.ResumeBuilder(new Information(users.getJSONObject(i).getString("name"),
                        users.getJSONObject(i).getString("email"),users.getJSONObject(i).getString("phone"),
                        users.getJSONObject(i).getString("date_of_birth"),users.getJSONObject(i).getString("genre"),
                        languages,languages_level),educations).build(),experiences);
                app.users.add(new User(res,interested_companies));
            }

             /*
            Citirea din consumers.json a recruiterilor.
            Angajati ii adaug intr-un ArrayList de tip recruiter , iar apoi pe fiecare in compania
            din care fac parte .
             */
            for(int i = 0 ; i < recruiterss.length() ; i++) {
                languages = new ArrayList<>();
                languages_level = new ArrayList<>();
                JSONArray languages_array = recruiterss.getJSONObject(i).getJSONArray("languages");
                JSONArray languages_list_array = recruiterss.getJSONObject(i).getJSONArray("languages_level");
                JSONArray educ = recruiterss.getJSONObject(i).getJSONArray("education");
                JSONArray exp = recruiterss.getJSONObject(i).getJSONArray("experience");
                educations = new ArrayList<>();
                experiences = new ArrayList<>();
                for(int j = 0; j < languages_array.length() ; j++)
                    languages.add(languages_array.getString(j));
                for(int j = 0; j < languages_list_array.length() ; j++)
                    languages_level.add(languages_list_array.getString(j));
                for(int j = 0 ; j < educ.length() ; j++) {
                    if(educ.getJSONObject(j).get("end_date").equals(null))
                        educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                educ.getJSONObject(j).getString("level"),educ.getJSONObject(j).getDouble("grade"),
                                educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                null));
                    else {
                        educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                educ.getJSONObject(j).getString("level"),educ.getJSONObject(j).getDouble("grade"),
                                educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                educ.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                    }
                }
                for(int j = 0 ; j < exp.length() ; j++) {
                    if(exp.getJSONObject(j).get("end_date").equals(null))
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                null));
                    else {
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                exp.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                    }
                }
                Collections.sort(educations);
                Collections.sort(experiences);
                Consumer.Resume res = new Consumer.Resume(new Consumer.Resume.ResumeBuilder(new Information(recruiterss.getJSONObject(i).getString("name"),
                        recruiterss.getJSONObject(i).getString("email"),recruiterss.getJSONObject(i).getString("phone"),
                        recruiterss.getJSONObject(i).getString("date_of_birth"),recruiterss.getJSONObject(i).getString("genre"),
                        languages,languages_level),educations).build(),experiences);
                recruiters.add(new Recruiter(res,recruiterss.getJSONObject(i).getDouble("salary")));
            }

             /*
            Citirea din consumers.json a managerilor.
            Angajati ii adaug intr-un ArrayList de tip manager , iar apoi pe fiecare in compania
            din care fac parte .
             */

            for(int i = 0 ; i < managerss.length() ; i++) {
                languages = new ArrayList<>();
                languages_level = new ArrayList<>();
                JSONArray languages_array = managerss.getJSONObject(i).getJSONArray("languages");
                JSONArray languages_list_array = managerss.getJSONObject(i).getJSONArray("languages_level");
                JSONArray educ = managerss.getJSONObject(i).getJSONArray("education");
                JSONArray exp = managerss.getJSONObject(i).getJSONArray("experience");
                educations = new ArrayList<>();
                experiences = new ArrayList<>();
                for(int j = 0; j < languages_array.length() ; j++)
                    languages.add(languages_array.getString(j));
                for(int j = 0; j < languages_list_array.length() ; j++)
                    languages_level.add(languages_list_array.getString(j));
                for(int j = 0 ; j < educ.length() ; j++) {
                    if(educ.getJSONObject(j).get("end_date").equals(null))
                        educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                educ.getJSONObject(j).getString("level"),educ.getJSONObject(j).getDouble("grade"),
                                educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                null));
                    else {
                        educations.add(new Education(educ.getJSONObject(j).getString("name"),
                                educ.getJSONObject(j).getString("level"),educ.getJSONObject(j).getDouble("grade"),
                                educ.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                educ.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                    }
                }
                for(int j = 0 ; j < exp.length() ; j++) {
                    if(exp.getJSONObject(j).get("end_date").equals(null))
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                null));
                    else {
                        experiences.add(new Experience(exp.getJSONObject(j).getString("position"),exp.getJSONObject(j).getString("company"),
                                exp.getJSONObject(j).getString("start_date").replaceAll(Pattern.quote("."),"/"),
                                exp.getJSONObject(j).getString("end_date").replaceAll(Pattern.quote("."),"/")));
                    }
                }
                Collections.sort(educations);
                Collections.sort(experiences);
                Consumer.Resume res = new Consumer.Resume(new Consumer.Resume.ResumeBuilder(new Information(managerss.getJSONObject(i).getString("name"),
                        managerss.getJSONObject(i).getString("email"),managerss.getJSONObject(i).getString("phone"),
                        managerss.getJSONObject(i).getString("date_of_birth"),managerss.getJSONObject(i).getString("genre"),
                        languages,languages_level),educations).build(),experiences);
                managers.add(new Manager(res,managerss.getJSONObject(i).getDouble("salary")));
            }

            /*
            Citirea job-urilor dintr-un fisier de tip json(jobs.json)
             */
            ArrayList<Job> jobs_list = new ArrayList<>();
            for(int i = 0 ; i < jobs.length() ; i++) {
                if(jobs.getJSONObject(i).get("average_max").equals(null) && jobs.getJSONObject(i).get("experience_max").equals(null))
                    jobs_list.add(new Job(jobs.getJSONObject(i).getString("name_job"),jobs.getJSONObject(i).getString("name_company"),jobs.getJSONObject(i).getString("departament"),
                        true,new Constraint(jobs.getJSONObject(i).getInt("graduation_year_min"),jobs.getJSONObject(i).getInt("graduation_year_max")),
                        new Constraint(jobs.getJSONObject(i).getInt("experience_min"),jobs.getJSONObject(i).get("experience_max")),
                        new Constraint(jobs.getJSONObject(i).getInt("average_min"),jobs.getJSONObject(i).get("average_max")),
                        jobs.getJSONObject(i).getInt("locuri"),jobs.getJSONObject(i).getDouble("salary")));
                else if (jobs.getJSONObject(i).get("average_max").equals(null) && jobs.getJSONObject(i).get("graduation_year_min").equals(null))
                    jobs_list.add(new Job(jobs.getJSONObject(i).getString("name_job"),jobs.getJSONObject(i).getString("name_company"),jobs.getJSONObject(i).getString("departament"),
                            true,new Constraint(jobs.getJSONObject(i).get("graduation_year_min"),jobs.getJSONObject(i).get("graduation_year_max")),
                            new Constraint(jobs.getJSONObject(i).getInt("experience_min"),jobs.getJSONObject(i).getInt("experience_max")),
                            new Constraint(jobs.getJSONObject(i).getInt("average_min"),jobs.getJSONObject(i).get("average_max")),
                            jobs.getJSONObject(i).getInt("locuri"),jobs.getJSONObject(i).getDouble("salary")));
                else if (jobs.getJSONObject(i).get("average_max").equals(null))
                    jobs_list.add(new Job(jobs.getJSONObject(i).getString("name_job"),jobs.getJSONObject(i).getString("name_company"),jobs.getJSONObject(i).getString("departament"),
                            true,new Constraint(jobs.getJSONObject(i).getInt("graduation_year_min"),jobs.getJSONObject(i).getInt("graduation_year_max")),
                            new Constraint(jobs.getJSONObject(i).getInt("experience_min"),jobs.getJSONObject(i).getInt("experience_max")),
                            new Constraint(jobs.getJSONObject(i).getInt("average_min"),jobs.getJSONObject(i).get("average_max")),
                            jobs.getJSONObject(i).getInt("locuri"),jobs.getJSONObject(i).getDouble("salary")));
            }
            System.out.println("-----------------------------");

            /* CELE DOUA COMPANII CU CELE 4 DEPARTAMENTE */

            DepartamentFactory departamentFactory = new DepartamentFactory();

            app.add(new Company("Google"));
            app.add(new Company("Amazon"));
            for(Company c : app.companies) {
                c.departaments.add(departamentFactory.factory("Finance","Finance"));
                c.departaments.add(departamentFactory.factory("IT","IT"));
                c.departaments.add(departamentFactory.factory("Management","Management"));
                c.departaments.add(departamentFactory.factory("Marketing","Marketing"));
            }
           /*
           INTRODUCERE ANGAJATI IN COMPANIA DIN CARE FAC PARTE  SI PE FIECARE IN DEPARTAMENTUL DIN CARE FACE PARTE
           INTRODUCERE MANAGERI IN COMPANIA DIN CARE FAC PARTE
           INTRODUCERE RECRUTEIRI IN COMPANIA DIN CARE FAC PARTE SI IN DEPARTAMENTUL DIN CARE FAC PARTE
            */
            for(Company c : app.companies) {
                if(c.nume.equals("Google")) {
                    for(int j = 0 ; j < employees.size() ; j++) {
                        for (int i = 0; i < employees.get(j).res.exp.size(); i++) {
                            if (employees.get(j).res.exp.get(i).company.equals("Google") && employees.get(j).res.exp.get(i).end_date_experience == null) {
                                for (Departament d : c.departaments) {
                                    if (d.name_departament.equals(employees.get(j).res.exp.get(i).departament)) {
                                        c.add(employees.get(j), d);
                                    }
                                }
                            }
                        }
                    }
                } else if(c.nume.equals("Amazon")) {
                    for(int j = 0 ; j < employees.size() ; j++) {
                        for (int i = 0; i < employees.get(j).res.exp.size(); i++) {
                            if (employees.get(j).res.exp.get(i).company.equals("Amazon") && employees.get(j).res.exp.get(i).end_date_experience == null) {
                                for (Departament d : c.departaments) {
                                    if (d.name_departament.equals(employees.get(j).res.exp.get(i).departament)) {
                                        c.add(employees.get(j), d);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            for(Company c : app.companies) {
                if(c.nume.equals("Google")) {
                    for (int j = 0; j < recruiters.size(); j++) {
                        for (int i = 0; i < recruiters.get(j).res.exp.size(); i++) {
                            if (recruiters.get(j).res.exp.get(i).company.equals("Google") && recruiters.get(j).res.exp.get(i).end_date_experience == null) {
                                for (Departament d : c.departaments) {
                                    c.add(recruiters.get(j));
                                    if(d.name_departament.equals("IT")) {
                                        c.add(recruiters.get(j),d);
                                    }
                                }
                            }
                        }
                    }
                }
                else if(c.nume.equals("Amazon")) {
                    for(int j = 0 ; j < recruiters.size() ; j++) {
                        for (int i = 0; i < recruiters.get(j).res.exp.size(); i++) {
                            if (recruiters.get(j).res.exp.get(i).company.equals("Amazon") && recruiters.get(j).res.exp.get(i).end_date_experience == null) {
                                for (Departament d : c.departaments) {
                                    c.add(recruiters.get(j));
                                    if(d.name_departament.equals("IT")) {
                                        c.add(recruiters.get(j),d);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for(Company c : app.companies) {
                if (c.nume.equals("Google")) {
                    for (int j = 0; j < managers.size(); j++) {
                        for (int i = 0; i < managers.get(j).res.exp.size(); i++) {
                            if (managers.get(j).res.exp.get(i).company.equals("Google") && managers.get(j).res.exp.get(i).end_date_experience == null) {
                                c.manager = managers.get(j);
                            }
                        }
                    }
                }else if(c.nume.equals("Amazon")) {
                    for(int j = 0 ; j < managers.size() ; j++) {
                        for (int i = 0; i < managers.get(j).res.exp.size(); i++) {
                            if (managers.get(j).res.exp.get(i).company.equals("Amazon") && managers.get(j).res.exp.get(i).end_date_experience == null) {
                                c.manager = managers.get(j);
                            }
                        }
                    }
                }
            }
            /*
            AFISAREA FIECAREI COMPANII CU DEPARTAMENTELE SI ANGAJATI DIN FIECARE DEPARTAMENT
            SI TOTALSALARY PE FIECARE DEPARTAMENT
             */
            for(Company c : app.companies) {
                System.out.println("----------------");
                if(c.nume.equals("Google")) {
                    System.out.println("Google Company");
                    System.out.println("----------------");
                    System.out.println("Manager : " + c.manager.res.info.getName());
                    System.out.println("Lista Angajati : ");
                    for(Departament d: c.departaments) {
                        for(Employee e : d.list_of_employees) {
                            System.out.println(e.res.info.getName() + "\t\tDepartament : " + d.name_departament);
                        }
                    }
                    for(Departament d : c.departaments)
                        System.out.println(d.name_departament + " TotalSalaryBudget : " + d.getTotalSalaryBudget());
                }else if(c.nume.equals("Amazon")) {
                    System.out.println("Amazon Company");
                    System.out.println("----------------");
                    System.out.println("Manager : " + c.manager.res.info.getName());
                    System.out.println("Lista Angajati : ");
                    for(Departament d: c.departaments) {
                        for(Employee e : d.list_of_employees) {
                            System.out.println(e.res.info.getName() + "\t\tDepartament : " + d.name_departament);
                        }
                    }
                    for(Departament d : c.departaments)
                        System.out.println(d.name_departament + " TotalSalaryBudget : " + d.getTotalSalaryBudget());
                }
            }

            for(User u : app.users) {
                for(int i = 0 ; i < u.interested_companies.size() ; i++) {
                    for(Company c : app.companies) {
                        if(c.nume.equals(u.interested_companies.get(i))) {
                            c.addObserver(u);
                        }
                    }
                }
            }
            System.out.println();
            /* ADAUGARE JOBURI IN FIECARE COMPANIE*/
            for(Company c : app.companies) {
                if(c.nume.equals("Google")) {
                    for (Departament d : c.departaments) {
                        for (int i = 0; i < jobs_list.size(); i++) {
                            if(jobs_list.get(i).name_company_for_job.equals("Google")) {
                                d.add(jobs_list.get(i));
                            }
                        }
                    }
                }else if(c.nume.equals("Amazon")) {
                    for (Departament d : c.departaments) {
                        for (int i = 0; i < jobs_list.size(); i++) {
                            if(jobs_list.get(i).name_company_for_job.equals("Amazon"))
                                d.add(jobs_list.get(i));
                        }
                    }
                }
            }
                for(Company c : app.companies) {
                    for(User u : c.users) {
                        for (Departament d : c.departaments) {
                            for (Job j : d.list_of_jobs) {
                                u.notification.add(c.notifyObserver("Company " + c.nume + " added the job " +
                                        j.name_job + "\n"));
                            }
                            break;
                        }
                    }
                }
            System.out.println("----------------");
                /*
                AFISARE USERI SI FIECARE JOB DISPONIBIL DIN FIECARE COMPANIE
                 */
            System.out.println("Users : ");
            for(User u : app.users) {
                System.out.println(u.res.info.getName());
            }

            System.out.println("----------------");
            System.out.println("Joburi disponibile : ");
            for(Company c : app.companies) {
                if(c.nume.equals("Google")){
                    for(Departament d : c.departaments) {
                        for(Job j : d.list_of_jobs)
                            System.out.println("Nume job : " + j.name_job + "\t\tCompanie : " + j.name_company_for_job);
                        break;
                    }
                }else if(c.nume.equals("Amazon")) {
                    for (Departament d : c.departaments) {
                        for (Job j : d.list_of_jobs)
                            System.out.println("Nume job : " + j.name_job + "\t\tCompanie : " + j.name_company_for_job);
                        break;
                    }
                }
            }
            System.out.println("----------------");

            /*
            CREARE RETEA SOCIALA
             */
            app.users.get(0).add(app.users.get(1));
            app.users.get(0).add(employees.get(2));
            app.users.get(1).add(app.users.get(0));
            app.users.get(1).add(employees.get(6));
            app.users.get(1).add(recruiters.get(0));
            app.users.get(2).add(app.users.get(3));
            app.users.get(2).add(employees.get(2));
            app.users.get(3).add(app.users.get(2));
            app.users.get(3).add(employees.get(9));
            employees.get(1).add(employees.get(9));
            employees.get(1).add(recruiters.get(2));
            employees.get(2).add(app.users.get(0));
            employees.get(2).add(app.users.get(2));
            employees.get(2).add(employees.get(5));
            employees.get(2).add(recruiters.get(1));
            employees.get(5).add(employees.get(2));
            employees.get(5).add(recruiters.get(3));
            employees.get(9).add(app.users.get(3));
            employees.get(9).add(employees.get(1));
            employees.get(6).add(app.users.get(1));


            /* FIECARE USER APLICA LA JOBURILE DE CARE ESTE INTERESAT*/
            for(User u : app.users) {
                for(Job j : jobs_list) {
                    for(int i = 0 ; i < u.interested_companies.size() ; i++) {
                        if(u.interested_companies.get(i).equals(j.name_company_for_job))
                            j.apply(u);
                    }
                }
            }
            /* MANAGERI PROCESEAZA CERERILE SI ACCEPTA NOI ANGAJATI */
            /*
            for(Company c : app.companies) {
                if(c.nume.equals("Amazon")) {
                    for(Departament d : c.departaments) {
                       for(int i = 0 ; i < d.list_of_jobs.size() ; i++) {
                           c.manager.process(d.list_of_jobs.get(i));
                       }
                    }
                }
            }
            for(Company c : app.companies) {
                if(c.nume.equals("Google")) {
                    for(Departament d : c.departaments) {
                        for(int i = 0 ; i < d.list_of_jobs.size() ; i++) {
                            c.manager.process(d.list_of_jobs.get(i));

                        }
                    }
                }
            }
            for(Company c : app.companies) {
                System.out.println("----------------");
                if(c.nume.equals("Google")) {
                    System.out.println("Google Company");
                    System.out.println("----------------");
                    System.out.println("Manager : " + c.manager.res.info.getName());
                    System.out.println("Lista Angajati dupa angajare: ");
                    for(Departament d: c.departaments) {
                        for(Employee e : d.list_of_employees) {
                            System.out.println(e.res.info.getName() + "\t\tDepartament : " + d.name_departament);
                        }
                    }
                }else if(c.nume.equals("Amazon")) {
                    System.out.println("Amazon Company");
                    System.out.println("----------------");
                    System.out.println("Manager : " + c.manager.res.info.getName());
                    System.out.println("Lista Angajati dupa angajare : ");
                    for(Departament d: c.departaments) {
                        for(Employee e : d.list_of_employees) {
                            System.out.println(e.res.info.getName() + "\t\tDepartament : " + d.name_departament);
                        }
                    }
                }
            }
             */
            /* INTERFATA GRAFICA */
            Interfata aplicatie = new Interfata();
            aplicatie.setTitle("Login Form");
            aplicatie.setVisible(true);
            aplicatie.setBounds(10,10,370,600);
            aplicatie.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            aplicatie.setResizable(false);
        }catch (Exception ex) {
            ex.printStackTrace();
        }



    }
}