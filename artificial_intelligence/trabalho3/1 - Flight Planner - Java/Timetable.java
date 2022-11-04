import java.util.*;

public class Timetable extends Base_dados {

    public static HashMap<Integer, Integer> last = new HashMap<Integer, Integer>();
    public static HashMap<String, Integer> enc = new HashMap<String, Integer>();
    public static HashMap<Integer, String> unc = new HashMap<Integer, String>();
    public static boolean adj[][] = new boolean[15][15], vis[] = new boolean[15], any = false;

    public static boolean bfs(int orig, int dest, String day) {
        LinkedList<Integer> queue = new LinkedList<Integer>();
        queue.addLast(orig);
        vis[orig] = true;

        while (!queue.isEmpty()) {
            int city = queue.removeFirst();
            if (city == dest) {
                return verifica(orig, dest, day);
            }

            for (int i = 0; i < 5; i++) {
                if (adj[city][i] && !vis[i]) {
                    queue.addLast(i);
                    vis[i] = true;
                    last.put(i, city);
                }
            }
        }
        return false;
    }

    public static boolean verifica(int orig, int dest, String day) {
        LinkedList<String> path = encCaminho(orig, dest);
        LinkedList<String> matchingDays = encDias(path);
        LinkedList<LinkedList<Route>> matchingFlights = findFlights(path, matchingDays);
        LinkedList <Route> possibleRoute = possibleRoute(matchingFlights, path, day);

        if (possibleRoute.isEmpty()) {
            last.clear();
            Arrays.fill(vis, false);
            vis[enc.get(path.get(path.size() - 1))] = true;
            bfs(orig, dest, day);
        } else {
            for (Route r : possibleRoute) {
                r.print();
            }
            return true;
        }
        return false;
    }

    public static LinkedList<String> encCaminho(int orig, int dest) {
        LinkedList<String> path = new LinkedList<>();
        path.addFirst(unc.get(dest));
        while (orig != dest) {
            if (last.get(dest) != null) {
                path.addFirst(unc.get(last.get(dest)));
                dest = last.get(dest);
            }
        }
        return path;
    }

    public static LinkedList<String> encDias(LinkedList<String> path) {
        LinkedList<String> matchingDays = new LinkedList<>();
        for(String day : allDays.split(",")) {
            matchingDays.add(day);
        }

        String city1 = path.get(0);
        for (int i = 1; i < path.size(); i++) {
            String city2 = path.get(i);
            for (Flight f : flights) {
                if (f.start.equals(city1) && f.end.equals(city2)) {
                    for (String weekDay : allDays.split(",")) {
                        boolean one = false;
                        for (String days : f.dias) {
                            for (String day : days.split(",")) {
                                if (day.equals(weekDay)) {
                                    one = true;
                                }
                            }
                        }
                        if (!one) {
                            matchingDays.remove(weekDay);
                        }
                    }
                    break;
                }
            }
            city1 = city2;
        }
        return matchingDays;
    }

    public static LinkedList<LinkedList<Route>> findFlights(LinkedList<String> path, LinkedList<String> matchingDays) {
        LinkedList<LinkedList<Route>> matchingFlights = new LinkedList<LinkedList<Route>>();

        String city1 = path.get(0);
        for (int i = 1; i < path.size(); i++) {
            String city2 = path.get(i);
            for (String day : matchingDays) {
                matchingFlights.add(encFlightsDia(city1, city2, day));
            }
            city1 = city2;
        }
        return matchingFlights;
    }

    public static LinkedList<Route> encFlightsDia(String orig, String dest, String day) {
        LinkedList<Route> route = new LinkedList<Route>();

        for (Flight f : flights) {
            if (f.start.equals(orig) && f.end.equals(dest)) {
                for (int i = 0; i < f.dias.size(); i++) {
                    for (String weekDay : f.dias.get(i).split(",")) {
                        if (weekDay.equals(day)) {
                            route.add(new Route(f.start, f.end, f.depTime.get(i), f.arrTime.get(i), f.flightNum.get(i), weekDay));
                        }
                    }
                }
                break;
            }
        }
        return route;
    }

    public static LinkedList<Route> possibleRoute(LinkedList<LinkedList<Route>> matchingFlights, LinkedList<String> path, String day) {
        LinkedList<Route> possibleRoute = new LinkedList<Route>();

        String city1 = path.get(0), city2 = path.get(1);
        for (int i = 2; i < path.size(); i++) {
            String city3 = path.get(i);

            for (LinkedList<Route> routes1 : matchingFlights) {
                for (LinkedList<Route> routes2 : matchingFlights) {
                    for (Route route1 : routes1) {
                        for (Route route2 : routes2) {
                            if (route1.start.equals(city1) && route1.end.equals(city2)) {
                                if (route2.start.equals(city2) && route2.end.equals(city3)) {
                                    if (route1.day.equals(day) && route2.day.equals(day)) {
                                        if (transferTime(route1.arrTime, route2.depTime)) {
                                            if (!possibleRoute.contains(route1)) {
                                                possibleRoute.add(route1);
                                            }
                                            if (!possibleRoute.contains(route2)) {
                                                possibleRoute.add(route2);
                                            }
                                            if (possibleRoute.size() == path.size() - 1) {
                                                return possibleRoute;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            city1 = city2;
            city2 = city3;
        }
        if (path.size() == 2) {
            LinkedList<Route> flightsInDay = encFlightsDia(path.get(0), path.get(1), day);
            if (flightsInDay.isEmpty()) {
                LinkedList<String> availableDays = encDias(path);

                if (availableDays.isEmpty()) {
                    System.out.println("Nao e possivel chegar ao end com essa cidade de start");
                } else if (!any) {
                    System.out.println("Nao foi possivel encontrar uma rota entre essas duas cidades nesse dia");
                    System.out.print("Available Days: ");
                    System.out.println(availableDays);
                }
            }
            return flightsInDay;
        }
        return possibleRoute;
    }

    public static boolean transferTime(String arrTime, String depTime) {
        String arr[] = arrTime.split(":"), dep[] = depTime.split(":");
        int arrHour = Integer.parseInt(arr[0]), arrMin = Integer.parseInt(arr[1]);
        int depHour = Integer.parseInt(dep[0]), depMin = Integer.parseInt(dep[1]);
        if (arrHour < depHour) {
            return ((depHour - arrHour) * 60 + (depMin - arrMin)) >= 40;
        }
        return ((depHour + 24 - arrHour) * 60 + (depMin - arrMin)) >= 40;
    }
}
