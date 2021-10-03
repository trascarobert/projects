package TemaPOO;

import java.util.Objects;

public class Constraint {
    Object lower_limit;
    Object upper_limit;
    public Constraint(Object lower_limit,Object upper_limit) {
        this.lower_limit = lower_limit;
        this.upper_limit = upper_limit;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Constraint)) return false;
        Constraint that = (Constraint) o;
        return Objects.equals(lower_limit, that.lower_limit) &&
                Objects.equals(upper_limit, that.upper_limit);
    }

    public int hashCode() {
        return Objects.hash(lower_limit, upper_limit);
    }

    public String toString() {
        return "Constraint{" +
                "limita_inferioara=" + lower_limit +
                ", limita_superioara=" + upper_limit +
                '}';
    }
}
