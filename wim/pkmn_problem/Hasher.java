import java.util.*;
import java.io.*;

public class Hasher {
	static Pokemon[] pkmn = new Pokemon[6000];
	static int[] hvs = new int[721];

	private static void readInPokemon(String filename){
		try {
			Scanner in = new Scanner(new File(filename));
			Scanner lineReader;
			List<Pokemon> tmp = new ArrayList<>();
			while(in.hasNextLine()){
				lineReader = new Scanner(in.nextLine()).useDelimiter(",");
				lineReader.next();
				Pokemon adder = new Pokemon(lineReader.next(), lineReader.nextInt());
				tmp.add(adder);
			}
			for(int i = 0; i < 6000; i++){
				Pokemon p = tmp.get((int)(Math.random() * 712));
				// System.out.println("Pokemon: " + p + " Hash Value: " + p.getHashValue());
				pkmn[i] = p;
			}
		} catch(Exception ex){
			ex.printStackTrace();
		}
	}

	public static void main(String[] args){
		for(int i = 0; i < 712; i++){
			hvs[i] = -1;
		}
		readInPokemon("pokemon_list.txt");
		int collisions = 0;
		for(Pokemon pm : pkmn){
			int hv = pm.getHashValue();
			if(hvs[hv] == 0){
				System.out.println("Collision! HashValue: " + hv);
				collisions++;
			}
			hvs[pm.getHashValue()] = 0;
		}
		int unique = 0;
		for(int i : hvs){
			if (i == 0){
				unique++;
			}
		}
		System.out.println("Total # of collisions: " + collisions);
		System.out.println("The total is " + unique);
	}

	private static class Pokemon{
		private String name;
		private int type;

		public Pokemon(String n, int t){
			name = n;
			type = t;
		}

		public int getHashValue(){
			char[] array = name.toCharArray();
			int total = 0;
			for(char c : array){
				total += (int)c;
			}
			total += type;
			total %= 721;
			return total;
		}

		public String toString(){
			return name;
		}
	}
}