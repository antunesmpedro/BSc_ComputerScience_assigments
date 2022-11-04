// Uma classe muito simples

// O ficheiro tem de ter o mesmo nome da classe + a extensão '.java'

public class Echo {
    public static void main(String[] args) {
	int i;
	for(i = 0; i < args.length - 1; i++){
	    System.out.print(args[i] + " ");
	}
	System.out.println(args[i]);
    }
}
