package TemaPOO;

import java.util.ArrayList;
import java.util.Objects;

public class Information {
    private String name;
    private String email;
    private String phone;
    private String day_of_birthday;
    private String sex;
    private ArrayList<String> languages_list;
    private ArrayList<String> level_of_language;
    public Information(String name, String email, String phone, String day_of_birthday, String sex, ArrayList<String> languages_list, ArrayList<String> level_of_language) {
        this.name = name;
        this.email = email;
        this.phone = phone;
        this.day_of_birthday = day_of_birthday;
        this.sex = sex;
        this.languages_list = languages_list;
        this.level_of_language = level_of_language;
    }


    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getEmail() {
        return email;
    }

    public void setDay_of_birthday(String day_of_birthday) {
        this.day_of_birthday = day_of_birthday;
    }

    public String getDay_of_birthday() {
        return day_of_birthday;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public String getPhone() {
        return phone;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public String getSex() {
        return sex;
    }

    public void setLevel_of_language(ArrayList<String> level_of_language) {
        this.level_of_language = level_of_language;
    }

    public void setLanguages_list(ArrayList<String> languages_list) {
        this.languages_list = languages_list;
    }

    public ArrayList<String> getLanguages_list() {
        return languages_list;
    }

    public ArrayList<String> getLevel_of_language() {
        return level_of_language;
    }

    public String toString() {
        return "\nInformation{" +
                "nume='" + name + '\'' +
                ", email='" + email + '\'' +
                ", telefon='" + phone + '\'' +
                ", data_de_nastere='" + day_of_birthday + '\'' +
                ", sex='" + sex + '\'' +
                ", lista_de_limbi=" + languages_list +
                ", nivel_limba=" + level_of_language +
                '}';
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Information)) return false;
        Information that = (Information) o;
        return Objects.equals(name, that.name) &&
                Objects.equals(email, that.email) &&
                Objects.equals(phone, that.phone) &&
                Objects.equals(day_of_birthday, that.day_of_birthday) &&
                Objects.equals(sex, that.sex) &&
                Objects.equals(languages_list, that.languages_list) &&
                Objects.equals(level_of_language, that.level_of_language);
    }

    public int hashCode() {
        return Objects.hash(name, email, phone, day_of_birthday, sex, languages_list, level_of_language);
    }
}
