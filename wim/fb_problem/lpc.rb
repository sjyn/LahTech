require_relative 'daniel.rb'

def count(m, s)
	bitmap = Array.new(m)
	i = 0
	while i < m do
		bitmap[i] = 0
		i += 1
	end
	s.each do |value|
		address = m_hash(value, m)
		bitmap[address] = 1
	end
	zeros = 0
	bitmap.each do |one_or_zero|
		if one_or_zero == 0 then
			zeros = zeros + 1
		end
	end
	lambda = zeros / m
	cardinality = (-1 * m) * Math.log(lambda)
end

def m_hash(value, size)
	value.hash % size
end

def main
	f = lambda do |x|
		# Math::E ** x
		x + 1
	end
	distribution = Distribution.new(3000, f)
	set = distribution.count 100000
	puts set.inspect
	# puts count(1000000, set)
end

main