def main
	array = Array.new
	pkmn_list = Array.new(721)
	hash_table = Array.new(721)
	for i in 0..721 do
		hash_table[i] = -1
	end
	File.open("pokemon_list.txt",'r') do |file|
		file.each_line do |line|
			str_arr = line.split ','
			pkmn_list.push Pokemon.new(str_arr[1],str_arr[2].to_i)
		end
	end
	for i in 0..6000 do
		pokee = pkmn_list.sample
		while pokee == nil do
			pokee = pokee = pkmn_list.sample
		end
		array.push pokee
	end
	array.each do |pokemon|
		hash_table[pokemon.custom_hash] = pokemon.custom_hash
	end
	total = 0
	hash_table.each do |val|
		if val != -1
			total = total + 1
		end
	end
	puts "The total number of unique encounters is #{total}"
end

class Pokemon
	def initialize(name="", type=0)
		@name = name
		@type = type
	end

	def custom_hash
		total = 0
		@name.each_byte do |car|
			total = total + car
		end
		total = total + @type
		total = total % 721
		return total
	end

	def to_s
		@name
	end
end

main