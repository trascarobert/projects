package TemaPOO;

public class Marketing extends Departament {
    public Marketing(String name_departament) {
        super(name_departament);
    }

    public double getTotalSalaryBudget() {
        double big_salary = 0;
        double small_salary = 0;
        double half_salary = 0;
        double total = 0;
            for(Employee e : list_of_employees) {
                if(name_departament.equals("Marketing")) {
                    if(e.salary > 5000)
                        big_salary += (e.salary * 10) / 100;
                    if(e.salary < 3000)
                        small_salary += e.salary;
                    if(e.salary > 3000 && e.salary < 5000)
                        half_salary += (e.salary * 16) / 100;
                }
            }
        total = big_salary + small_salary + half_salary;
        return total;
    }

    public int hashCode() {
        return super.hashCode();
    }

    public boolean equals(Object o) {
        return super.equals(o);
    }
}
