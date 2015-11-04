require 'twitter'
require_relative 'const.rb'
client = Twitter::REST::Client.new do |config|
  config.consumer_key        = Constants.oh_one
  config.consumer_secret     = Constants.oh_two
  config.access_token        = Constants.oh_three
  config.access_token_secret = Constants.oh_four
end

while true do
	open('twitter_data.txt','a') do |f|
		client.search("#", result_type: 'recent', lang: 'en').take(1000).each do |tweet|
			f.puts tweet.text
		end
	end
	str = "Gathered Sample at #{Time.now.inspect}"
	open('tw_log.txt','a') do |file|
		file.puts str
		puts str
	end
	sleep 120
end
