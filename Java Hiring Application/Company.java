package TemaPOO;

import java.util.ArrayList;
import java.util.Objects;

public class Company {
    String nume;
    Manager manager;
    ArrayList<Departament> departaments;
    ArrayList<Recruiter> recruiters;
    ArrayList<User> users = new ArrayList<>();
    public Company(String name) {
        this.nume = name;
        this.manager = new Manager();
        this.departaments = new ArrayList<>();
        this.recruiters = new ArrayList<>();
    }

    public void addObserver(User user) {
        users.add(user);
    }
    public void removeObserver(User c) {
        users.remove(c);
    }
    public void notifyAllObservers(String notification) {
        for(User u : users) {
            u.update(notification);
        }

    }
    public String notifyObserver(String notification) {
        return notification;
    }

    public String getNume() {
        return nume;
    }

    public void add(Departament departament) {
        departaments.add(departament);
    }
    public void add(Recruiter recruiter) {
        recruiters.add(recruiter);
    }
    public void add(Employee employee , Departament departament){
            departament.list_of_employees.add(employee);
    }

    public void remove(Departament departament){
        for(Employee e : departament.list_of_employees) {
                departament.list_of_employees.remove(e);
        }
        departaments.remove(departament);

    }

    public void remove(Recruiter recruiter) {

        recruiters.remove(recruiter);
    }
    public boolean contains(Departament departament) {
        if(departaments.contains(departament))
            return true;
        return false;
    }
    public boolean contains(Recruiter recruiter) {
        if(recruiters.contains(recruiter))
            return true;
        return false;
    }

    public void remove(Employee employee) {
        for(Departament d : departaments) {
            d.list_of_employees.remove(employee);
        }
    }

    public void move(Employee employee,Departament newDepartament) {
        for(Departament d : departaments) {
            for(Employee e : d.list_of_employees) {
                if(e.equals(employee)) {
                    d.remove(e);
                }
            }
        }
        for(Departament d : departaments) {
            if(d.equals(newDepartament))
                newDepartament.add(employee);
        }
    }

    public void move(Departament source,Departament destination){
        for(Employee e : source.list_of_employees){
            destination.list_of_employees.add(e);
            source.list_of_employees.remove(e);
        }
        departaments.add(destination);
        departaments.remove(source);
    }

    public Recruiter getRecruiter(User user){
        Recruiter recruiter = new Recruiter();
        int max = 0;
        for(Recruiter rec : recruiters) {
            int x = user.getDegreeInFriendship(rec);
            if(x > max) {
                max = x;
                recruiter = rec;
            }
            if(x == max){
                if(rec.rating > recruiter.rating) {
                    recruiter = rec;
                }
            }

        }
        return recruiter;
    }


    public ArrayList<Job> getJobs(){
        ArrayList<Job> jobs_free = new ArrayList<>();
        for(Departament d : departaments) {
            for(Job j : d.list_of_jobs) {
                if(j.flag == true)
                    jobs_free.add(j);
            }
        }
        return jobs_free;
    }
    public boolean contains(Employee employee) {
        for(Departament d : departaments){
            if(d.list_of_employees.contains(employee))
                return true;
        }
        return false;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Company)) return false;
        Company company = (Company) o;
        return Objects.equals(nume, company.nume) &&
                Objects.equals(manager, company.manager) &&
                Objects.equals(departaments, company.departaments) &&
                Objects.equals(recruiters, company.recruiters);
    }

    public String toString() {
        return "Company{" +
                "nume='" + nume ;
    }

    public int hashCode() {
        return Objects.hash(nume, manager, departaments, recruiters);
    }
}
