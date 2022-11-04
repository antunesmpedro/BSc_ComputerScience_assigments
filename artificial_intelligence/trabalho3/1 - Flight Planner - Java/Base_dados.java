
import java.util.LinkedList;

public class Base_dados {

    public static LinkedList<Flight> flights = new LinkedList<Flight>();
    public static String allDays = "mo,tu,we,th,fr,sa,su";

    public static void load() {
        LinkedList<String> depTime = new LinkedList<String>();
        LinkedList<String> arrTime = new LinkedList<String>();
        LinkedList<String> flightNum = new LinkedList<String>();
        LinkedList<String> days = new LinkedList<String>();

        Timetable.enc.put("london", 0);
        Timetable.unc.put(0, "london");
        Timetable.enc.put("edinburgh", 1);
        Timetable.unc.put(1, "edinburgh");
        Timetable.enc.put("ljubljana", 2);
        Timetable.unc.put(2, "ljubljana");
        Timetable.enc.put("zurich", 3);
        Timetable.unc.put(3, "zurich");
        Timetable.enc.put("milan", 4);
        Timetable.unc.put(4, "milan");

        Timetable.adj[Timetable.enc.get("edinburgh")][Timetable.enc.get("london")] = true;
        depTime.add("9:40");
        arrTime.add("10:50");
        flightNum.add("ba4733");
        days.add(allDays);
        depTime.add("13:40");
        arrTime.add("14:50");
        flightNum.add("ba4773");
        days.add(allDays);
        depTime.add("19:40");
        arrTime.add("20:50");
        flightNum.add("ba4833");
        days.add("mo,tu,we,th,fr,su");
        flights.add(new Flight("edinburgh", "london", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("london")][Timetable.enc.get("edinburgh")] = true;
        depTime.add("9:40");
        arrTime.add("10:50");
        flightNum.add("ba4732");
        days.add(allDays);
        depTime.add("11:40");
        arrTime.add("12:50");
        flightNum.add("ba4752");
        days.add(allDays);
        depTime.add("18:40");
        arrTime.add("19:50");
        flightNum.add("ba4822");
        days.add("mo,tu,we,th,fr");
        flights.add(new Flight("london", "edinburgh", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("london")][Timetable.enc.get("zurich")] = true;
        depTime.add("9:10");
        arrTime.add("11:45");
        flightNum.add("ba614");
        days.add(allDays);
        depTime.add("18:40");
        arrTime.add("19:50");
        flightNum.add("ba4822");
        days.add("mo,tu,we,th,fr,su,sa");
        flights.add(new Flight("london", "zurich", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("london")][Timetable.enc.get("milan")] = true;
        depTime.add("8:30");
        arrTime.add("11:20");
        flightNum.add("ba510");
        days.add(allDays);
        depTime.add("11:00");
        arrTime.add("13:50");
        flightNum.add("az459");
        days.add(allDays);
        flights.add(new Flight("london", "milan", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("london")][Timetable.enc.get("ljubljana")] = true;
        depTime.add("13:20");
        arrTime.add("16:20");
        flightNum.add("ju201");
        days.add("fr");
        depTime.add("14:45");
        arrTime.add("17:20");
        flightNum.add("ju213");
        days.add("su");
        flights.add(new Flight("london", "ljubljana", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("milan")][Timetable.enc.get("london")] = true;
        depTime.add("9:10");
        arrTime.add("10:00");
        flightNum.add("az458");
        days.add(allDays);
        depTime.add("12:20");
        arrTime.add("13:10");
        flightNum.add("ba511");
        days.add(allDays);
        flights.add(new Flight("milan", "london", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("milan")][Timetable.enc.get("zurich")] = true;
        depTime.add("9:25");
        arrTime.add("10:15");
        flightNum.add("sr621");
        days.add(allDays);
        depTime.add("12:45");
        arrTime.add("13:35");
        flightNum.add("sr623");
        days.add(allDays);
        flights.add(new Flight("milan", "zurich", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("zurich")][Timetable.enc.get("ljubljana")] = true;
        depTime.add("13:30");
        arrTime.add("14:40");
        flightNum.add("yu323");
        days.add("tu,th");
        flights.add(new Flight("zurich", "ljubljana", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("zurich")][Timetable.enc.get("london")] = true;
        depTime.add("9:00");
        arrTime.add("9:40");
        flightNum.add("ba613");
        days.add(allDays);
        depTime.add("16:10");
        arrTime.add("16:55");
        flightNum.add("sr806");
        days.add("mo,tu,we,th,fr,su");
        flights.add(new Flight("zurich", "london", depTime, arrTime, flightNum, days));
        depTime = new LinkedList<String>();
        arrTime = new LinkedList<String>();
        flightNum = new LinkedList<String>();
        days = new LinkedList<String>();

        Timetable.adj[Timetable.enc.get("zurich")][Timetable.enc.get("milan")] = true;
        depTime.add("7:55");
        arrTime.add("8:45");
        flightNum.add("sr620");
        days.add(allDays);
        flights.add(new Flight("zurich", "milan", depTime, arrTime, flightNum, days));
    }
}
