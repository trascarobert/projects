package TemaPOO;


import java.util.ArrayList;
import java.util.Objects;

abstract public class Departament {
    String name_departament;
    ArrayList<Employee> list_of_employees;
    ArrayList<Job> list_of_jobs;


    public Departament(String name_departament) {
        this.name_departament = name_departament;
        this.list_of_employees = new ArrayList<>();
        this.list_of_jobs = new ArrayList<>();
    }


    public abstract double getTotalSalaryBudget();


    public ArrayList<Job> getJobs(){
        return list_of_jobs;
    }
    public void add(Employee employee) {
        list_of_employees.add(employee);
    }
    public void remove(Employee employee) {
        list_of_employees.remove(employee);
    }
    public void add(Job job) {
        list_of_jobs.add(job);
    }
    public ArrayList<Employee> getEmployees() {
        return list_of_employees;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Departament)) return false;
        Departament that = (Departament) o;
        return Objects.equals(list_of_employees, that.list_of_employees) &&
                Objects.equals(list_of_jobs, that.list_of_jobs);
    }

    public int hashCode() {
        return Objects.hash(list_of_employees, list_of_jobs);
    }

    public String toString() {
        return name_departament;
    }
}

class DepartamentFactory {
    public Departament factory(String type,String nameDepartament) {
        if(type.equalsIgnoreCase("IT")) {
            return new IT(nameDepartament);
        }else if(type.equalsIgnoreCase("Finance")) {
            return new Finance(nameDepartament);
        }else if(type.equalsIgnoreCase("Marketing")) {
            return new Marketing(nameDepartament);
        }else if(type.equalsIgnoreCase("Management")) {
            return new Management(nameDepartament);
        }
        return null;
    }
}