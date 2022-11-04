// Uma classe simples para representar um aluno
class Aluno {
    // Atributos da classe (variáveis para conter informação)
    public String nome;
    public int numero;
    public static int contador = 0;
    
    
    // Construtor "padrão"
    Aluno() {
        nome   = "indefinido";
        numero = -1;
    }
    
    // Método para escrever o conteúdo de uma instância de um aluno
    void escreve() {
        System.out.println("[" + numero + "] " + nome);
    }
    
    
    
    Aluno(String nome, int numero) {
	this.nome = nome;
	this.numero = numero;
    }
    
    int ano() {
	return numero / 100000;
    }
    
    
}

// Classe principal contendo o main para testar a classe Aluno
public class TestAluno {
    public static void main(String[] args) {
        Aluno a = new Aluno("a", 10);
	Aluno b = new Aluno("a", 20);
	System.out.println("----------------a ---------------------");
        a.escreve();
	System.out.println("----------------b ---------------------");
	b.escreve();
	b.nome = "b";
	
	System.out.println("----------------a (N) ---------------------");
        a.escreve();
	System.out.println("----------------b (N)---------------------");
	b.escreve();
	
	
	
	// Aluno b = a;
	// b.nome = "aaa";
	// System.out.println("----------------a ---------------------");
	// a.escreve();
	// System.out.println("----------------b ---------------------");
	// b.escreve();
	// Aluno b = new Aluno();
	// b.escreve();
	// System.out.println(a);
	// Aluno c = new Aluno();
	// Aluno d = c;
	// c.nome = "modificado";
	// c.escreve();
	// d.escreve();
	// Aluno e = new Aluno();
	// Aluno f = new Aluno("Manuel", 201506234);
	// e.escreve();
	// f.escreve();
	
	
	// Aluno g = new Aluno("Ana", 201408762);
	// Aluno h = new Aluno("Bruno", 201508145);
	// System.out.println(g.ano() + " " + h.ano());
    }
}
