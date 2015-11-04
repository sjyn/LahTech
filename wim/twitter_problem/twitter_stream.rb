require 'twitter'
client = Twitter::REST::Client.new do |config|
  config.consumer_key        = "JtwwG40EW2O6CKBNp1qeD57IH"
  config.consumer_secret     = "NUSZ0jPyeWwTKPAlUDYLnoeatyDCsPp5waIJsYnQM6LJ5oDjDJ"
  config.access_token        = "3494713935-hoqlE0ocEarpGUbSosIEi3YJvHqrJH3j60x7Z74"
  config.access_token_secret = "fKTi6UiCESwluB9UbBOsdcBVjHHPfUOxr6PbSWy4UCUi8"
end

while true do
	open('twitter_data.txt','a') do |f|
		client.search("#", result_type: 'recent', lang: 'en').take(1000).each do |tweet|
			f.puts tweet.text
		end
	end
	str = "Gathered Sample at " + Time.now.inspect
	open('tw_log.txt','a') do |file|
		file.puts str
		puts str
	end
	sleep 1200
end
