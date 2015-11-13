require_relative 'daniel.rb'

def count(m, s)
	bitmap = Array.new(m)
	i = 0
	# while i < m do
	# 	bitmap[i] = 0
	# 	i += 1
	# end
	for i in 0..m do
		bitmap[i] = 0
	end
	s.each do |value|
		address = m_hash(value, m)
		bitmap[address] = 1
	end
	zeros = 0.0
	bitmap.each do |one_or_zero|
		if one_or_zero == 0 then
			zeros += 1.0
		end
	end
	# puts "zeros: #{zeros}"
	# puts "m: #{m}"
	lamb = (zeros / m)
	# puts "lambda: #{lamb}"
	cardinality = (-1 * m) * Math.log(lamb)
end

def m_hash(value, size)
	value.hash % size
end

def main
	f = lambda do |x|
		# Math::E ** x
		Math::E ** x
	end
	amnt = 7000000
	distribution = Distribution.new(30000, f)
	set = distribution.count amnt
	#puts set.inspect
	puts count(amnt, set)
end

main