def count(m, s)
	bitmap = Array.new(m)
	for i in 0..m do
		bitmap[i] = 0
	end
	s.each do |value|
		address = m_hash(value)
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