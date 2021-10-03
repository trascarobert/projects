package TemaPOO;
import java.util.*;

abstract public class Consumer {
    Resume res;
    ArrayList<Consumer> friends_list;
    public Consumer() {
        res = new Resume();
        friends_list = new ArrayList<>();
    }

    public void add(Education education) {
        res.educ.add(education);
    }

    public void add(Experience experience) {
        res.exp.add(experience);
    }
    public void add(Consumer consumer){
        friends_list.add(consumer);
    }
    public void remove(Consumer consumer) {
        friends_list.remove(consumer);
    }

    public int getDegreeInFriendship(Consumer consumer){
       HashMap<Consumer,Integer> map = new HashMap<>();
       LinkedList<Consumer> q = new LinkedList<>();
       q.add(this);
       map.put(this,0);
       while(!q.isEmpty()) {
           Consumer curr = q.poll();
           if(curr.equals(consumer))
               return map.get(curr);
           for(Consumer c : curr.friends_list) {
                if(!map.containsKey(c)) {
                    map.put(c,map.get(curr) + 1);
                    q.add(c);
                }
           }
       }
       return -1;
    }


    public Integer getGraduationYear() {
        for(int i = 0 ; i < res.educ.size() ; i++) {
            if(res.educ.get(i).level_of_education.equals("college"))
                return res.educ.get(i).getYear();
        }
        return null;
    }
    public Double meanGPA() {
        int count = 0;
        double media = 0;
        for(int i = 0 ; i < res.educ.size() ; i++) {
            count++;
            media += res.educ.get(i).getEnd_media();
        }
        return media/count;

    }
    static class Resume {
        Information info;
        ArrayList<Education> educ;
        ArrayList<Experience> exp;
        public Resume(){
            educ = new ArrayList<>();
            exp = new ArrayList<>();
        }
        public Resume(Information i) {
            info = i;
        }

        public Resume(ResumeBuilder builder, ArrayList<Experience> exp)throws ResumeIncompleteException{
            this.info = builder.info;
            this.educ = builder.educ;
            this.exp = exp;
            if(info == null || educ.size() == 0)
                throw new ResumeIncompleteException();
        }

        public String toString() {
            return info + "\n" + educ + "\n" + exp;
        }
        static class ResumeBuilder{
            Information info;
            ArrayList<Education> educ;
            ArrayList<Experience> exp;
            public ResumeBuilder(Information info , ArrayList<Education> educ) {
                this.info = info;
                this.educ = educ;
            }
            public ArrayList<Experience> setExperience(ArrayList<Experience> exp) {
                this.exp = exp;
                return this.exp;
            }
            public ResumeBuilder build() {
                return new ResumeBuilder(this.info,this.educ);
            }
        }
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Consumer)) return false;
        Consumer consumer = (Consumer) o;
        return Objects.equals(res, consumer.res) &&
                Objects.equals(friends_list, consumer.friends_list);
    }

}