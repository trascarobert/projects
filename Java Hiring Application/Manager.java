package TemaPOO;

import java.util.ArrayList;
import java.util.Objects;

public class Manager extends Employee {
    ArrayList<Request> employment_requests;
    public Manager() {
        employment_requests = new ArrayList<>();
    }


    public Manager(Resume res,double salary) {
        employment_requests = new ArrayList<>();
        super.res = res;
        super.salary = salary;
    }
    public void process(Job job) {
        Application app = Application.getInstance();
        int nr = job.number_of_seats;
        int i = employment_requests.size() - 1;
        while(i >= 0 && nr != 0) {
            Request request = employment_requests.get(i);
            User u = (User)employment_requests.get(i).getValue1();
            Job job_from_request = (Job)employment_requests.get(i).getKey();
            if(job_from_request.equals(job) && job.flag != false) {
                for (Company c : app.companies) {
                    for (Departament d : c.departaments) {
                        if (d.list_of_jobs.contains(job) && d.name_departament.equals(job.departamanet_job) && app.users.contains(u)) {
                            d.list_of_employees.add(u.convert());
                            app.users.remove(u);
                            c.removeObserver(u);
                            c.manager.employment_requests.remove(request);
                            nr--;
                            break;
                        }
                    }
                }
                if(nr == 0) {
                    job.flag = false;
                    for(Company c : app.companies) {
                        if(c.nume.equals(job.name_company_for_job))
                            c.notifyAllObservers("The job " + job.name_job + " from company " + job.name_company_for_job + " was closed!");
                    }
                    break;
                }
            }
            i--;
        }
    }


    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Manager)) return false;
        if (!super.equals(o)) return false;
        Manager manager = (Manager) o;
        return Objects.equals(employment_requests, manager.employment_requests);
    }
    public int hashCode() {
        return Objects.hash(super.hashCode(), employment_requests);
    }
}
