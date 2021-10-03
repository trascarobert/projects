package TemaPOO;

public class Management extends Departament {
    public Management(String name_departament) {
        super(name_departament);
    }

    public double getTotalSalaryBudget() {
        double total = 0;
            for(Employee e : list_of_employees) {
                if(name_departament.equals("Management")) {
                    total += e.salary;
                }
            }
        return total + ((total * 16) / 100);
    }

    public boolean equals(Object o) {
        return super.equals(o);
    }
    public int hashCode() {
        return super.hashCode();
    }
}
