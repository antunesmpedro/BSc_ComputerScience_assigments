import java.util.Scanner;


public class Sentenca{
	private static int index; //current

	public static void main(String[] args){
		Scanner in = new Scanner(System.in);

		System.out.println("---Forme uma frase em Portugues---");

		while(in.hasNextLine()){
			System.out.println();

			if(isCorrect(in.nextLine))		
				System.out.println(":)\nFrase formada corretamente..!");
			else
				System.out.println(":(\nFrase formada incorretamente..!");
			
			System.out.println("---Tente outra vez---");
		}
		
		in.close();
	}

	//Teste de predicado
	private static boolean isCorrect(String	phrase){
		String delims = "{[(" ")]}-_,.:;+*";
		String[] words = phrase.split(delims);
			
		if (words[0].endsWith("s")) {
			//Plural 
		    if (noun_phrase_p(words) && verbal_phrase_p(words)) {
			if (words.length > index) {
			    index--;
			    return phrase_c_p(words); 
			}
			return true;
		    }
		}
		else {
			//Singular 
		    if (noun_phrase_s(words) && verbal_phrase_s(words)) {
			if (words.length > index) {
			    index--;
			    return phrase_c_s(words);	
			}
			return true;
		    } 
		}
		return false;
	}


	/*
	*	----SINGULAR----
	*/
	private string boolean noun_phrase_s(String[] words){
		index = 0;

		if(words[0].equals("O")){
			index++;
			return subs_s_m(words);
		}
		if(words[0].equals("A")){
			index++;
			return subs_s_f(words);
		}

		return false;
	}

	private static boolean subst_s_m(String[] words) {
		if (words[index].equals("tempo")   || words[index].equals("cacador")   || 
		    words[index].equals("rio") || words[index].equals("vento") || 
		    words[index].equals("martelo") || words[index].equals("sino"){ 
		    index++;
		    return true;
		}
		return false;
	}

	private static boolean subst_s_f(String[] words) {
		if (words[index].equals("menina")  || words[index].equals("vida")    || 
		    words[index].equals("noticia") || words[index].equals("porta")) {
		    index++;
		    return true;
		}
		return false;
	}

	private static boolean verbal_phrase_s(String[] words) {
		if (words[index].equals("corre") || words[index].equals("correu") ||
	    	words[index].equals("bateu")) {
	    	index++;
	    	return true;
		}
		return false;
    }

    private static boolean phrase_c_s(String[] words) {	
		if (words[index].equals("corre") && words[index+1].equals("para")) {
		    if (words[index+2].equals("o")) {
				index += 3;
				return comp_s_m(words);
		    }	
		    if (words[index+2].equals("a")) {
				index += 3;
				return comp_s_f(words);
		    }
		}
		if (words[index].equals("bateu")) {
		    if (words[index+1].equals("o") || words[index+1].equals("no")) {
				index += 2;
				return comp_s_m(words);
		    }
		    if (words[index+1].equals("a") || words[index+1].equals("na")) {
				index += 2;
				return comp_s_f(words);
		    }
		}
		if (words[index].equals("correu")) {
		    if (words[index+1].equals("com") || words[index+1].equals("para")) { 		
				if (words[index+2].equals("o")) {
				    index += 3;
				    return comp_s_m(words);
				}
				if (words[index+2].equals("os")) {
				    index += 3;
				    return comp_p_m(words);
				}
				if (words[index+2].equals("a") || words[index+2].equals("na")) {
				    index += 3;
				    return comp_s_f(words);
				}
		    }

		    if (words[index+1].equals("pela")) {
				index += 2;
				return comp_s_f(words);
		    }
		}
		return false;
    }

    private static boolean comp_s_m(String[] words) {
		if (words[index].equals("mar")    || words[index].equals("cachorro") ||
		    words[index].equals("tambor") { 
		    index++;
		    return true;
		}
		return false;
    }
	
    private static boolean comp_s_f(String[] words) {
		if (words[index].equals("floresta")  || words[index].equals("mae") ||
		    words[index].equals("cidade")    || words[index].equals("porta")) {
		    index++;
		    return true;
		}
		return false;
    }

    /*
	*	----PLURAL----
	*/

	private string boolean noun_phrase_p(String[] words){
		index = 0;
		
		if(words[0].equals("Os")){
			index++;
			return subs_p_m(words);
		}
		if(words[0].equals("As")){
			index++;
			return subs_p_f(words);
		}

		return false;
	}

	private static boolean subst_p_m(String[] words) {
		if (words[index].equals("cacadores") || words[index].equals("martelos") || 
		    words[index].equals("sinos")     || words[index].equals("tambores")) { 
		    index++;
		    return true;
		}
		return false;
    }
	
    private static boolean subst_p_f(String[] words) {
		if (words[index].equals("meninas")  || words[index].equals("noticias") || 
		    words[index].equals("lagrimas") || words[index].equals("portas")) {
		    index++;
		    return true;
		}
		return false;
    }

    private static boolean verbal_phrase_p(String[] words) {
		if (words[index].equals("corriam")  || words[index].equals("correm")  || 
		    words[index].equals("correram") || words[index].equals("bateram") || 
		    words[index].equals("batem")    || words[index].equals("batiam")) {
		    index++;
		    return true;
		}			
		return false;
    }

    private static boolean phrase_c_p(String[] words) {
		if (words[index].equals("corriam")) { 
		    if (words[index+1].equals("pelo")) {
				index += 2;
				return comp_p_m(words);
		    }	
		    if (words[index+1].equals("pela")) {
				index += 2;
				return comp_p_f(words);
		    }
		}
		if (words[index].equals("correram") && words[index+1].equals("pelo")) {
		    index += 2;
		    return comp_p_m(words);
		}
		return false;
    }
	
    private static boolean comp_p_m(String[] words) {
		if (words[index].equals("rosto") || words[index].equals("lobos")) { 
		    index++;
		    return true;
		}
		return false;
    }
	
    private static boolean comp_p_f(String[] words) {
		if (words[index].equals("cidade")  || words[index].equals("noticias") || 
		    words[index].equals("lagrimas") || words[index].equals("portas")) {
		    index++;
		    return true;
		}
		return false;
    }
}