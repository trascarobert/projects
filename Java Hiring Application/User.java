package TemaPOO;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class User extends Consumer{
    List<String> companies = new ArrayList<>();
    ArrayList<String> interested_companies;
    ArrayList<String> notification = new ArrayList<>();
    public User(Resume r , ArrayList<String> interested_companies) {
        super.res = r;
        this.interested_companies = interested_companies;
    }
    public void update(String notification) {
        System.out.println(notification);
    }
    public User() {
        companies = new ArrayList<>();
    }

    public Employee convert() {
        return new Employee(res);
    }
    public int calculateExperienceYear() {
        int start_year = 0;
        int end_year = 0;
        for(Experience e : super.res.exp) {
            start_year += e.getYearStart();
            end_year += e.getYearEnd();
        }
        int year = end_year - start_year;
        return year + 1;
    }
    public Double getTotalScore() {
        int number_of_year;
        int start_year = 0;
        int end_year = 0;
        for(Experience e : super.res.exp) {
            start_year += e.getYearStart();
            end_year += e.getYearEnd();
        }
        number_of_year = end_year - start_year;
        double total = 0;
        int count = 0;
        for(Education e : super.res.educ) {
            total += e.getEnd_media();
            count++;
        }
        double media_academica = total / count;
        return (number_of_year * 1.5 ) + media_academica;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof User)) return false;
        if (!super.equals(o)) return false;
        User user = (User) o;
        return Objects.equals(companies, user.companies) &&
                Objects.equals(interested_companies, user.interested_companies);
    }

    public int hashCode() {
        return Objects.hash(companies, interested_companies);
    }

    public String toString() {
        return "User{\n" + "name : " + res.info.getName() + "\n"
                + "email : " + res.info.getEmail() + "\n" + "phone : " + res.info.getPhone() +
                "\n" + "date_of_birth : " + res.info.getDay_of_birthday() + "\n" + "genre : " +
                res.info.getSex() + "\n" + "languages : " + res.info.getLanguages_list() + "\n" +
                "languages_level : " + res.info.getLevel_of_language() + "\n" + "interested_companies : " + interested_companies + "\n"
                + "Education{\n" + res.educ + "\n" + "Experience{\n" + res.exp + "\n";
    }


}
