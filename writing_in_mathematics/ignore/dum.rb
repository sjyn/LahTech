def initialize(log2m, register_set = nil)
    @log2m = log2m
    @count = 2 ** log2m
    @register_set = register_set || RegisterSet.new(@count)

    case log2m
    when 4
        @alphaMM = 0.673 * @count * @count
    when 5
        @alphaMM = 0.697 * @count * @count
    when 6
        @alphaMM = 0.709 * @count * @count
    else
        @alphaMM = (0.7213 / (1 + 1.079 / @count)) * @count * @count
    end
end

def cardinality
    register_sum = 0.0
    zeros = 0.0
    @register_set.each do |value|
        register_sum += 1.0 / (1 << value)
        zeros += 1 if value == 0
    end
    estimate = @alphaMM * (1 / register_sum)
    if estimate <= (5.0 / 2.0) * @count
        (@count * Math.log(@count / zeros)).round
    else
        estimate.round
    end
end