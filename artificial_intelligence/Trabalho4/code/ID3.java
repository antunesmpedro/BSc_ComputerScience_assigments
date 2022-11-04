import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;


class DecisionTree {
	Node root = new Node();
	List<List<String>> data;
	int nodeCount=0;
	int numAttributes=0;
	List<String> attributesNotUsed = new ArrayList<String>();

	public DecisionTree(List<List<String>> data) {
		//get data, count attributes
		this.data = data;
		List<String> line = data.get(0);

		for(int i=1; i<line.size()-1; i++){
			numAttributes++;
			String crl = line.get(i);
			attributesNotUsed.add(crl);
		}
		//System.out.println(attributesNotUsed +" " +  numAttributes);
	}

	public boolean generateTree() {
		root.parentNode = null;
		root.depth = -1; 
		root.data = data;
		root.entropy = calculateEntropy(root.data);
		//System.out.println(root.entropy);
		root.threshold = null;
		root.atribute = null;
		root.attributes = this.attributesNotUsed;
		nodeCount++;

		Queue<Node> queue = new LinkedList<Node>();
		queue.add(root);

		while(!queue.isEmpty()) {
			Node temp = queue.poll();
			if(temp.isLeaf())
				//temp.threshold = getMainClass(temp.data);
			continue;
			else {
				String bestAttribute = findBestAttribute(temp);
				//System.out.println(bestAttribute);
				temp.childrenNodes = splitData(temp,bestAttribute);

				for(Node node : temp.childrenNodes) {
					//split data adds: threeshold, attributeUsed, data & atributes
					node.parentNode = temp;
					node.depth = temp.depth++;
					node.entropy = calculateEntropy(temp.data);
					queue.add(node);

					//System.out.println( "Atrib Used:" + node.atribute + "       Atrib Not Used:" + node.attributes.toString() );
					//ystem.out.println(node.data);
					//System.out.println(node.depth + "  " + node.atribute + " thre:"  + node.threshold + "  "  + node.entropy);
				}
			}
		}
		return true;
	}

	/*
	String getMainClass(List<List<String>> data) {
		HashMap<String , Integer> count = new HashMap<String,Integer>();
		for(List<String> line : data) {
			String help = line.get(line.size());
			count.put(help, count.get(help)+1);
		}
		int max=-1;
		return help;
	}
*/
	
	Node[] splitData(Node node, String bestAttribute) {
		List<String> line = new ArrayList<String>();
		line = node.data.get(0);
		int coll = line.indexOf(bestAttribute);
		List<String> atribNames = getDifferentAtributeValues(node.data,coll);
		atribNames.remove(0);
		Node[] splitted = new Node[atribNames.size()];
		int i=0;

		while(!atribNames.isEmpty()) {
			Node temp = new Node();
			temp.atribute = bestAttribute;
			temp.threshold = atribNames.get(0);
			temp.attributes = node.attributes;
			temp.attributes.remove(temp.atribute);
			List<List<String>> dataTemp = new ArrayList<>(); 			
			dataTemp.add(line);
			for(List<String> temporary : node.data) {
				if(temporary.contains(temp.threshold)) {
					dataTemp.add(temporary);
				}
			}
			temp.data = dataTemp;
			splitted[i] = temp;
			i++;
			//System.out.println(temp.threshold);
			atribNames.remove(0);
		}
		return splitted;
	}

	String findBestAttribute(Node temp) {
		double bestGain = -20;
		String bestAttribute = "crl";
		List<String> att = temp.attributes;
		double gain = 1;
		for(String attribute : att) {
			gain = gain(temp.entropy, attribute, temp.data);
			if (gain > bestGain) {
				bestAttribute = attribute;
				bestGain = gain;
			}
		}
		//System.out.println(bestAttribute);
		return bestAttribute;
	}

	double gain(double oldEntropy, String atrib, List<List<String>> data) {
		double entropy = 0;

		List<String> line = new ArrayList<String>();
		line = data.get(0);
		//System.out.println(line);
		int coll = line.indexOf(atrib);
		int[] counts = countOccOfAttribute(data,coll);
		int countSummary=0;
		for(int i=1; i<counts.length; i++)
			countSummary += counts[i];

		//System.out.println(Arrays.toString(counts));
		List<String> valuesAtributes = getDifferentAtributeValues(data,coll);
		//System.out.println(valuesAtributes);

		for(int i=1; i<counts.length; i++) {
			List<List<String>> dataTemp = new ArrayList<>();
			for(List<String> line2: data) {
				if(line2.get(coll).equals(valuesAtributes.get(i)))
					dataTemp.add(line2);
			}
			//System.out.println(calculateEntropy(dataTemp));
			entropy = entropy + (((counts[i]/countSummary) * calculateEntropy(dataTemp)));
		}
		//System.out.println(oldEntropy-entropy);
		return (oldEntropy-entropy);
	}

	List<String> getDifferentAtributeValues(List<List<String>> data, int collumn) {   
		List<String> atributes= new ArrayList<String>();

		String valuesLasts;
		for(List<String> line: data) {
			valuesLasts = line.get(collumn);
			if(!atributes.contains(valuesLasts))
				atributes.add(valuesLasts);
		}
		return atributes;
	}


	int[] countOccOfAttribute(List<List<String>> data, int collumn) {   
		Map<String, Integer> counter = new HashMap<String,Integer>();

		String valuesLasts;
		int i=0;
		for(List<String> line: data) {
			valuesLasts = line.get(collumn);
			counter.put(valuesLasts,0);
			i++;
		}
		for(List<String> line: data) {
			valuesLasts = line.get(collumn);
			int opc = counter.get(valuesLasts);
			counter.put(valuesLasts, opc+1);
		}
		int[] cout = new int[counter.size()];
		i=0;
		for(Integer value : counter.values()) {
			cout[i] = value;
			i++;
		}
		return cout;
	}

	int[] countDiferentClasses(List<List<String>> data) {   
		Map<String, Integer> counter = new HashMap<String,Integer>();
		String valuesLasts;
		int i=0;
		for(List<String> line: data) {
			valuesLasts = line.get(line.size()-1);
			counter.put(valuesLasts,0);
			i++;
		}
		for(List<String> line: data) {
			valuesLasts = line.get(line.size()-1);
			int opc = counter.get(valuesLasts);
			counter.put(valuesLasts, opc+1);
		}
		int[] cout = new int[counter.size()];
		i=0;
		for(Integer value : counter.values()) {
			cout[i] = value;
			i++;
		}
		return cout;
	}

	double calculateEntropy(List<List<String>> data) { 

		int[] newOccurrences = countDiferentClasses(data);
		int[] occurrences = Arrays.copyOfRange(newOccurrences, 1, newOccurrences.length);
		//stem.out.println(Arrays.toString(newOccurrences)  );
		double entropy;
		double totalOccurrences = 0;
		int counter = 0;
		for (int i = 1; i < occurrences.length; i ++) {
			if ((double)occurrences[i] == 0)
				counter++;
			totalOccurrences += (double)occurrences[i];
		}
		if (counter == occurrences.length - 1)
			return 0;
		if (totalOccurrences == 0)
			return 0;
		entropy = 0;
		for (int i = 0; i < occurrences.length; i++) {
			if (occurrences[i] != 0)
				entropy += (-1) * (occurrences[i]/totalOccurrences) * (Math.log10(occurrences[i]/totalOccurrences) / Math.log10(2)); 
		}
		return entropy;
	}

	/*
	 * Question the tree
	 */
	public String question(String line) {
		String answer = new String(); 
		return answer;
	}

	public void print() {
		// System.out.println("ROOT");

		List<Node> nodes = new ArrayList<Node>();
		nodes.add(root);

		while(!nodes.isEmpty()) {
			Node temp = nodes.get(0);
			System.out.println();
			for(int i=-2; i<temp.depth; i++)
				System.out.print("--");	
			System.out.print(temp.depth + ": Atribute: " + temp.atribute + "    Label: "  + temp.threshold + "   Entropy:"  + String.format( "%.2f",temp.entropy));
			// Node[] childrenNodes;
			nodes.remove(0);
			if(temp.childrenNodes != null)
				for(int i=0; i< temp.childrenNodes.length; i++) {
					nodes.add(temp.childrenNodes[i]);
				}

		}
	}
}

class Node {
	Node[] childrenNodes;
	Node parentNode;
	int depth; 
	String atribute;
	String threshold;
	double entropy;
	List<List<String>> data; 	
	List<String> attributes;

	public Node() {
	}

	public boolean isLeaf() {
		if (entropy == 0) return true;
		else if(attributes.isEmpty()) return true;
		return false;
	}
}

public class ID3  {

	static public List<List<String>> readFile(String path) {
		// this gives you a 2-dimensional array of strings
		List<List<String>> lines = new ArrayList<>();

		File file= new File(path);
		Scanner inputStream;

		try {
			inputStream = new Scanner(file);
			while(inputStream.hasNext()) {
				String line= inputStream.next();
				String[] values = line.split(",");
				// this adds the currently parsed line to the 2-dimensional string array
				lines.add(Arrays.asList(values));
			}
			inputStream.close();
			return lines;
		}
		catch (FileNotFoundException e) {
			return null;
		}
	}

	static public void printMatrix(	List<List<String>> lines) {
		for(List<String> line: lines) {
			for (String value: line) {
				System.out.print( " " + value);
			}
			System.out.println();
		}
	}

	public static void main(String[] args) {
		List<List<String>> matrix = new ArrayList<>();
		matrix = readFile("./iris.csv");
		if(matrix == null) {
			System.out.println("Unable to read file");
			System.exit(0);
		}
		else {
			printMatrix(matrix);
			DecisionTree tree = new DecisionTree(matrix);
			if(tree.generateTree() == false) {
				System.out.println("\nFailed to generate tree");
				System.exit(0);
			}
			else {
				tree.print();
			}
		}
	}
}