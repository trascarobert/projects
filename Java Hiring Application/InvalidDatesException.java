package TemaPOO;

public class InvalidDatesException extends Exception{
    public InvalidDatesException() {
        super("Datele introduse sunt gresite din punct de vedere cronologic.");
    }
}
