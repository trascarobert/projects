package TemaPOO;

import java.util.ArrayList;
import java.util.Objects;

public class Job {
    String name_job;
    String name_company_for_job;
    String departamanet_job;
    boolean flag;
    Constraint year_of_graduation;
    Constraint number_of_year_experience;
    Constraint license_media;
    ArrayList<User> candidates;
    int number_of_seats;
    double salary;

    public Job(String name_job, String name_company_for_job, String departamanet_job, boolean flag , Constraint year_of_graduation,
               Constraint number_of_year_experience, Constraint license_media, int number_of_seats, double salary) {
        this.name_job = name_job;
        this.departamanet_job = departamanet_job;
        this.name_company_for_job = name_company_for_job;
        this.flag = flag;
        this.year_of_graduation = year_of_graduation;
        this.number_of_year_experience = number_of_year_experience;
        this.license_media = license_media;
        this.candidates = new ArrayList<>();
        this.number_of_seats = number_of_seats;
        this.salary = salary;
    }


    public void apply(User user){
        Application ap = Application.getInstance();
        for(Company c : ap.companies) {
            if(c.nume.equals(this.name_company_for_job)) {
                if(flag) {
                    Recruiter recruiter = c.getRecruiter(user);
                    recruiter.evalute(this, user);
                }
            }
        }
    }


    public boolean meetsRequirments(User user) {
        int year = user.getGraduationYear();
        int exp_year = user.calculateExperienceYear();
        double meanGPA = user.meanGPA();
        if(year_of_graduation.lower_limit.equals(null))
            year_of_graduation.lower_limit = -1;
        if(year_of_graduation.upper_limit.equals(null))
            year_of_graduation.lower_limit = -1;
        if(number_of_year_experience.lower_limit.equals(null))
            number_of_year_experience.lower_limit = -1;
        if(number_of_year_experience.upper_limit.equals(null))
            number_of_year_experience.upper_limit = -1;
        if(license_media.lower_limit.equals(null))
            license_media.lower_limit = -1;
        if(license_media.upper_limit.equals(null))
            license_media.upper_limit = -1;
        if(year < (int) year_of_graduation.lower_limit && year > (int) year_of_graduation.upper_limit)
            return false;
        if(exp_year < (int) number_of_year_experience.lower_limit && exp_year >(int) year_of_graduation.upper_limit)
            return false;
        if(meanGPA < (int) license_media.lower_limit && meanGPA > (int) license_media.upper_limit)
            return false;
        return true;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Job)) return false;
        Job job = (Job) o;
        return flag == job.flag &&
                number_of_seats == job.number_of_seats &&
                Double.compare(job.salary, salary) == 0 &&
                Objects.equals(name_job, job.name_job) &&
                Objects.equals(name_company_for_job, job.name_company_for_job) &&
                Objects.equals(year_of_graduation, job.year_of_graduation) &&
                Objects.equals(number_of_year_experience, job.number_of_year_experience) &&
                Objects.equals(license_media, job.license_media) &&
                Objects.equals(candidates, job.candidates);
    }

    public int hashCode() {
        return Objects.hash(name_job, name_company_for_job, flag, year_of_graduation, number_of_year_experience, license_media, candidates, number_of_seats, salary);
    }

    public String toString() {
        return "Job{" +
                "nume_job='" + name_job + '\'' +
                ", numele_companieiJ='" + name_company_for_job + '\'' +
                ", flag=" + flag +
                ", anul_absolvirii=" + year_of_graduation +
                ", numarul_de_ani_exp=" + number_of_year_experience +
                ", media_academica=" + license_media +
                ", candidati=" + candidates +
                ", nr_locuri=" + number_of_seats +
                ", salary=" + salary +
                '}';
    }
}
