import java.util.*;

public class Routes extends Timetable{
	public static void main(String[] args){
		Scanner stdin = new Scanner(System.in);
		Base_dados.load();
		String start, day;
        String end;
        System.out.print("Cidade Origem: ");
        start = stdin.next();
        while (!enc.containsKey(start)) {
            System.out.println("A cidade introduzida nao existe na Base de Dados");
            System.out.print("\nInsere novamente");
            start = stdin.next();
        }
        System.out.print("Cidade Destino: ");
        end = stdin.next();
        while (!enc.containsKey(end)) {
            System.out.println("A cidade introduzida nao existe na Base de Dados");
            System.out.print("\nInsere novamente");
            end = stdin.next();
        }

        System.out.println("Inserir dia da viagem");
        day = stdin.next();
        LinkedList<String> week= new LinkedList<String>();
        for (String d : Base_dados.allDays.split(",")) {
            week.add(d);
        }
        while (!week.contains(day) && !day.equals("any")) {
            System.out.print("\nInsere um dia valido (mo,tu,we,th,fr,sa,su and any)");
            day = stdin.next();
        }
        System.out.println("\n\t\t\t\tRoute of Flights:"); //Print dos resultados
        if (day.equals("any")) {
            Timetable.any = true;
            for (String d : Base_dados.allDays.split(",")) {
                if (bfs(enc.get(start), enc.get(end), d)) {
                    System.out.println("_______________________________________________________________________________\n");
                }
                last.clear();
                Arrays.fill(vis, false);
            }
        } else {
            bfs(enc.get(start), enc.get(end), day);
        }
    }

}

class Route {

    String start, end, depTime, arrTime, flightNum, day;

    Route(String orig, String dest, String depTime, String arrTime, String flightNum, String day) {
        start = orig;
        end = dest;
        this.depTime = depTime;
        this.arrTime = arrTime;
        this.flightNum = flightNum;
        this.day = day;
    }

    public void print() {
        System.out.println("\t\t\tDE: " + start + "\t\tPARA: " + end);
        System.out.print("Partida: " + depTime + "\tChegada: " + arrTime);
        System.out.println("\tVoo N. " + flightNum + "\tday: " + day);
    }
}

class Flight {

    String start, end;
    LinkedList<String> depTime = new LinkedList<String>();
    LinkedList<String> arrTime = new LinkedList<String>();
    LinkedList<String> flightNum = new LinkedList<String>();
    LinkedList<String> dias = new LinkedList<String>();

    Flight(String orig, String dest, LinkedList<String> depTime, LinkedList<String> arrTime, LinkedList<String> flightNum, LinkedList<String> days) {
        start = orig;
        end = dest;
        this.depTime = depTime;
        this.arrTime = arrTime;
        this.flightNum = flightNum;
        days = days;
    }
}
