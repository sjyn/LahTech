require 'hyperll'

module Worker
	def Worker.calculate(len)
		mhll = Hyperll::HyperLogLog.new(10)
		File.open("twitter_data.txt","r") do |file|
			file.each_line do |line|
				mhll.offer line
			end
		end
		str = "\tUnique Elements: #{mhll.cardinality}"
		File.open("tw_log.txt",'a') do |file|
			file.puts str
			puts str
		end
	end
end