package TemaPOO;


import java.util.ArrayList;
import java.util.List;

public class Application {
    ArrayList<Company> companies;
    ArrayList<User> users;
    private static Application ins = null;
    public Application() {
        this.companies = new ArrayList<>();
        this.users = new ArrayList<>();
    }
    public ArrayList<Company> getCompanies() {
        return companies;
    }
    public Company getCompany(String name) {
        for(Company c : companies) {
            if(c.nume.equals(name)) {
                return c;
            }
        }
        return null;
    }
    public static Application getInstance() {
        if(ins == null)
            ins = new Application();
        return ins;
    }
    public void add(Company company) {
        companies.add(company);
    }
    public void add(User user) {
        users.add(user);
    }
    public boolean remove(Company company) {
        if(companies.contains(company)) {
            companies.remove(company);
            return true;
        }else
            return false;
    }
    public boolean remove(User user) {
        if(users.contains(user)) {
            users.remove(user);
            return true;
        }else
            return false;
    }


    public ArrayList<Job> getJobs(List<String> companies){
        ArrayList<Job> job = new ArrayList<>();
        for(Company c : this.companies) {
            for(String s : companies) {
                if(c.nume.equals(s)){
                    job.addAll(c.getJobs());
                }
            }
        }
        return job;
    }

}
