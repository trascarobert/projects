package TemaPOO;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;

public class Experience implements Comparable{
    String position;
    String company;
    String departament;
    Date data3;
    Date data4;
    SimpleDateFormat simpledate1 = new SimpleDateFormat("dd.MM.yyyy");
    String start_date_experience;
    String end_date_experience;
    public Experience(String position, String company, String departament, String start_date_experience, String end_date_experience) throws InvalidDatesException{
        this.position = position;
        this.company = company;
        this.departament = departament;
        this.data3 = new Date(start_date_experience);
        this.start_date_experience = this.simpledate1.format(this.data3);
        if(end_date_experience == null)
            this.data4 = new Date(0,0,0);
        else {
            this.data4 = new Date(end_date_experience);
            this.end_date_experience = this.simpledate1.format(this.data4);
        }

        if(end_date_experience != null && data3.after(data4))
            throw new InvalidDatesException();


    }
    public Experience(String position, String company, String start_date_experience, String end_date_experience) throws InvalidDatesException{
        this.position = position;
        this.company = company;
        this.data3 = new Date(start_date_experience);
        this.start_date_experience = this.simpledate1.format(this.data3);
        if(end_date_experience == null)
            this.data4 = new Date(0,0,0);
        else {
            this.data4 = new Date(end_date_experience);
            this.end_date_experience = this.simpledate1.format(this.data4);
        }

        if(end_date_experience != null && data3.after(data4))
            throw new InvalidDatesException();


    }

    public int compareTo(Object o) {
        Experience ex = (Experience)o;
        if(this.end_date_experience == null) {
            if (this.company.compareTo(ex.company) > 0)
                return 1;
            else
                return -1;
        }

        if(this.end_date_experience.compareTo(ex.end_date_experience) > 0 )
            return -1;
        else if(this.end_date_experience.compareTo(ex.end_date_experience) == 0) {
            if (this.company.compareTo(ex.company) > 0)
                return 1;
            else
                return -1;
        }else{
            return 1;
        }
    }

    public int getYearEnd() {
        int year = 0;
        if(this.data4 != null)
            year = 1900 + data4.getYear();
        else if(this.data4.getYear() == 0)
            return 0;
        return year;
    }
    public int getYearStart() {
        int year = 0;
        if(this.data3 != null)
            year = 1900 +data3.getYear();
        else
            return 0;
        return year;
    }

    
    public String toString() {
        if(this.departament != null)
            return "\ncompany : " + company + "\n" + "position : " + position + "\n" +
                "departament : "  + departament + "\n" + "start_date : " + start_date_experience + "\n"
                + "end_date : " + end_date_experience + "\n";
        else
            return "\ncompany : " + company + "\n" + "position : " + position + "\n" +
                 "start_date : " + start_date_experience + "\n"
                + "end_date : " + end_date_experience + "\n";
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Experience)) return false;
        Experience that = (Experience) o;
        return Objects.equals(position, that.position) &&
                Objects.equals(company, that.company) &&
                Objects.equals(departament, that.departament) &&
                Objects.equals(data3, that.data3) &&
                Objects.equals(data4, that.data4) &&
                Objects.equals(simpledate1, that.simpledate1) &&
                Objects.equals(start_date_experience, that.start_date_experience) &&
                Objects.equals(end_date_experience, that.end_date_experience);
    }

    public int hashCode() {
        return Objects.hash(position, company, departament, data3, data4, simpledate1, start_date_experience, end_date_experience);
    }
}

