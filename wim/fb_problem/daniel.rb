require "pp"
class Distribution
    attr_accessor :x_min
    attr_accessor :x_max
    attr_accessor :counts
    attr_accessor :distribution
    attr_accessor :types

    def initialize(types, f, x_min = 1, x_max = 100)
        self.x_min        = x_min
        self.x_max        = x_max
        self.counts       = Array.new(types)
        self.distribution = Array.new(types + 1)
        self.types        = types

        # Sum distribution for normalization
        m = (x_max - x_min).fdiv(types)
        sum_of_distribution = 0;

        self.distribution[0] = f.call(x_min)
        sum_of_distribution += self.distribution[0]

        (1...types).each do |c|
            self.distribution[c] = f.call(x_min + m * c)
            sum_of_distribution += self.distribution[c]
            self.distribution[c] += self.distribution[c-1]
        end

        (0...types).each do |c|
            self.distribution[c] = self.distribution[c].fdiv(sum_of_distribution)
            puts self.distribution[c]
        end

        # Normalize distribution and
        # Manipulate such that c*(n) = c(n) + c(n-1) + ... + c(1) + c(0)
    end   

    def count(n)
        res = Array.new(n)
        (0...n).each do |i|
            r = rand()
            res[i] = self.distribution.find_index { |x| x >= r }
        end
        res
    end

    def bucket_count(n)
        res = Array.new(n)
        n.times do
            r = rand()
            res[self.distribution.find_index { |x| x >= r }] += 1
        end
        res
    end
end

f = lambda do |x|
  x ** 2
end

distribution = Distribution.new(1000, f, 1, 100)
p distribution.count(100000)