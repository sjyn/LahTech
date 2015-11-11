#!/usr/bin/ruby
require 'twitter'
require 'hyperll'
require_relative 'const.rb'

module TwitterProblem
	def TwitterProblem.routine
		tags = 0
		
		client = Twitter::REST::Client.new do |config|
		  config.consumer_key        = Constants.oh_one
		  config.consumer_secret     = Constants.oh_two
		  config.access_token        = Constants.oh_three
		  config.access_token_secret = Constants.oh_four
		end

		while true do
			begin
				File.open('twitter_data.txt','a') do |f|
					client.search("#", result_type: 'recent', lang: 'en').take(2000).each do |tweet|
						twt = tweet.text
						array = twt.split(' ')
						array.each do |val|
							if val[0] == "#" and val.length > 1 then
								f.puts val
								tags += 1
							end
						end
					end
				end
				str = "Gathered Sample at #{Time.now.inspect}\n\tCurrent total number of tags: #{tags}"
				File.open('tw_log.txt','a') do |file|
					file.puts str
					puts str
				end
				Thread.new {
					calculate
				}
				sleep 120
			rescue Twitter::Error::TooManyRequests
				str = "Request Limit Reached at #{Time.now.inspect}. Sleeping for 16 minutes..."
				File.open('tw_log.txt','a') do |file|
					file.puts str
					puts str
				end
				sleep 960
				str = "Waking up at #{Time.now.inspect}."
				File.open('tw_log.txt','a') do |file|
					file.puts str
					puts str
				end
				retry
			end
		end
	end

	def calculate
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

	def TwitterProblem.parseLogForMathematica
		File.open('mathematica_data.txt','w') do |m_file|
			m_file.puts "{"
			File.open('tw_log.txt','r') do |file|
				file.each_line do |line|
					if line.include? 'total' then
						m_file.print "{ #{line.scan(/\d+/).first}, "
					elsif line.include? 'Unique' then
						m_file.puts " #{line.scan(/\d+/).first} }, "
					end
				end
			end
			m_file.puts "}"
		end
	end
end
TwitterProblem.parseLogForMathematica
# TwitterProblem.routine