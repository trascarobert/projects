package TemaPOO;

public class IT extends Departament {
    public IT(String name_departament) {
        super(name_departament);
    }

    public double getTotalSalaryBudget() {
        double total = 0;
            for(Employee e : list_of_employees) {
                if(name_departament.equals("IT")) {
                    total += e.salary;
                }
        }
        return total;
    }

    public int hashCode() {
        return super.hashCode();
    }

    public boolean equals(Object o) {
        return super.equals(o);
    }
}
