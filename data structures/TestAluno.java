// Uma classe simples para representar um aluno
class Aluno {
    public static int contador = 0;
    // Atributos da classe (variáveis para conter informação)
    public String nome;
    private int numero;

    // Construtor "padrão"
    Aluno() {
	contador++;
        nome   = "indefinido";
        numero = -1;
    }

    Aluno(String n, int mec) {
	contador++;
	nome = n;
	numero = mec;
    }
    
    int ano() {
	return numero / 100000;
    }

    // Método para escrever o conteúdo de uma instância de um aluno
    void escreve() {
        System.out.println("[" + numero + "] " + nome);
    }
}

// Classe principal contendo o main para testar a classe Aluno
public class TestAluno {
    public static void main(String[] args) {
	System.out.println("contador = " + Aluno.contador);
        Aluno a = new Aluno();
        a.escreve();
	System.out.println(a.nome);
	Aluno b = new Aluno();
	b.escreve();
	System.out.println(a);
	
	Aluno c = new Aluno();  // cria-se um aluno c
        Aluno d = c;            // cria-se um aluno d que aponte para o c
        c.nome = "modificado";  // foi criado o aluno c com o construtor vazio e depois modifica-se o c.nome
        c.escreve();
        d.escreve();
	
	Aluno e = new Aluno();
	Aluno f = new Aluno("Manuel", 201506234);
	e.escreve();
	f.escreve();
	
	Aluno g = new Aluno("Ana", 201408762);
	Aluno h = new Aluno("Bruno", 201508145);
	System.out.println(g.ano() + " " + h.ano());
	System.out.println("contador = " + Aluno.contador);
    }   
}
