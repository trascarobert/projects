package TemaPOO;

import java.util.Objects;

public class Recruiter extends Employee {
    double rating;
    public Recruiter() {
        this.rating = 5;
    }

    public Recruiter(Resume res, double salary){
        this.rating = 5;
        super.res = res;
        super.salary = salary;
    }
    public int evalute(Job job , User user) {

        double evalute_job = this.rating * user.getTotalScore();
        Application ap = Application.getInstance();
        if(job.meetsRequirments(user)) {
            Company c = ap.getCompany(job.name_company_for_job);
            c.manager.employment_requests.add(new Request(job, user, this, evalute_job));

            rating += 0.1;
        }else {
            for(Company c : ap.companies){
                if(c.nume.equals(job.name_company_for_job))
                    user.notification.add(c.notifyObserver("You have rejected for this job " + job.name_job
                    + " from company " + job.name_company_for_job + " because you do not meet the conditions!\n"));
            }
            rating += 0.1;
        }
        return (int)evalute_job;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Recruiter)) return false;
        if (!super.equals(o)) return false;
        Recruiter recruiter = (Recruiter) o;
        return Double.compare(recruiter.rating, rating) == 0;
    }

    public int hashCode() {
        return Objects.hash(super.hashCode(), rating);
    }
}
