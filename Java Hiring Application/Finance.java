package TemaPOO;

public class Finance extends Departament {
    public Finance(String name_departament) {
        super(name_departament);
    }

    public double getTotalSalaryBudget() {
        double salary1 = 0;
        double salary2 = 0;
        double total = 0;
        double experience = 0;

            for(Employee e : list_of_employees) {
                if(name_departament.equals("Finance")) {
                    for(Experience ex : e.res.exp)
                        experience = ex.getYearEnd() - ex.getYearStart();
                    if(experience > 1)
                        salary1 += (e.salary * 16) / 100;
                    else
                        salary2 += (e.salary * 10) / 100;
                }
            }
        total = salary1 + salary2;
        return total;
    }

    public boolean equals(Object o) {
        return super.equals(o);
    }

    public int hashCode() {
        return super.hashCode();
    }
}
