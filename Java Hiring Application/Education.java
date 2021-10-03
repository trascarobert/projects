package TemaPOO;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;

public class Education implements Comparable{
    String name_of_the_institution;
    String level_of_education;
    double end_media;
    Date data1;
    Date data2;
    SimpleDateFormat simpledate = new SimpleDateFormat("MM.dd.yyyy");
    String start_date_education;
    String end_date_education;

    public Education(String name_of_the_institution, String level_of_education , double end_media, String start_date_education, String end_date_education) throws InvalidDatesException {
            this.name_of_the_institution = name_of_the_institution;
            this.level_of_education = level_of_education;
            this.end_media = end_media;
            data1 = new Date(start_date_education);
            this.start_date_education = this.simpledate.format(this.data1);
            if (end_date_education == null)
                data2 = new Date(0, 0, 0);
            else {
                data2 = new Date(end_date_education);
                this.end_date_education = this.simpledate.format(this.data2);
            }
            if(end_date_education != null && data1.after(data2))
                throw new InvalidDatesException();
        }

    public int compareTo(Object o) {
        Education e = (Education)o;

        if(this.end_date_education == null) {
            if (this.start_date_education.compareTo(e.start_date_education) > 0)
                return 1;
            else
                return -1;
        }
        if(this.end_date_education.compareTo(e.end_date_education) > 0) {
            return -1;
        }else if(this.end_date_education.compareTo(e.end_date_education) == 0) {
            if(this.end_media > e.end_media)
                return -1;
            else
                return 1;
        }else
            return 1;
    }

    public String toString() {
        return "\nlevel : " + level_of_education + "\n" + "name : " + name_of_the_institution + "\n"
                + "start_date : " + start_date_education + "\n" + "end_date : " + end_date_education + "\n"
                + "grade : " + end_media + "\n";
    }
    public int getYear() {
        int year = 0;
        if(data2.getYear() != -1)
            year = 1900 + data2.getYear();
        else
            return 0;
        return year;
    }

    public double getEnd_media() {
        return end_media;
    }


    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Education)) return false;
        Education education = (Education) o;
        return Double.compare(education.end_media, end_media) == 0 &&
                Objects.equals(name_of_the_institution, education.name_of_the_institution) &&
                Objects.equals(level_of_education, education.level_of_education) &&
                Objects.equals(data1, education.data1) &&
                Objects.equals(data2, education.data2) &&
                Objects.equals(simpledate, education.simpledate) &&
                Objects.equals(start_date_education, education.start_date_education) &&
                Objects.equals(end_date_education, education.end_date_education);
    }

    public int hashCode() {
        return Objects.hash(name_of_the_institution, level_of_education, end_media, data1, data2, simpledate, start_date_education, end_date_education);
    }
}


