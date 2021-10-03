package TemaPOO;

import java.util.ArrayList;
import java.util.Objects;

public class Employee extends Consumer {
    double salary;
    public Employee() {
        this.salary = 0;
    }
    public Employee(double salary) {
        this.salary = salary;
    }
    public Employee(Resume r , ArrayList<Consumer> c) {
        super.res = r;
        super.friends_list = c;
    }
    public Employee(Resume r,double salary){
        this.salary = salary;
        super.res = r;
    }
    public Employee(Resume r, double salary,ArrayList<Education> educ, ArrayList<Experience> exp) {
        res = r;
        this.salary = salary;
        res.educ = educ;
        res.exp = exp;
    }
    public Employee(Resume r) {
        super.res = r;
    }

    public String toString() {
        return "Employee{\n" + "name : " + res.info.getName() + "\n"
                + "email : " + res.info.getEmail() + "\n" + "phone : " + res.info.getPhone() +
                "\n" + "date_of_birth : " + res.info.getDay_of_birthday() + "\n" + "genre : " +
                res.info.getSex() + "\n" + "languages : " + res.info.getLanguages_list() + "\n" +
                "languages_level : " + res.info.getLevel_of_language() + "\n" + "salary : " + salary + "\n"
                + "Education{\n" + res.educ + "\n" + "Experience{\n" + res.exp + "\n";
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Employee)) return false;
        if (!super.equals(o)) return false;
        Employee employee = (Employee) o;
        return Double.compare(employee.salary, salary) == 0;
    }

    public int hashCode() {
        return Objects.hash(super.hashCode(), salary);
    }
}
