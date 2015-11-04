require 'twitter'
require_relative 'const.rb'

def routine
	tags = 0
	
	client = Twitter::REST::Client.new do |config|
	  config.consumer_key        = Constants.oh_one
	  config.consumer_secret     = Constants.oh_two
	  config.access_token        = Constants.oh_three
	  config.access_token_secret = Constants.oh_four
	end

	while true do
		open('twitter_data.txt','a') do |f|
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
		open('tw_log.txt','a') do |file|
			file.puts str
			puts str
		end
		sleep 60
	end
end

routine
